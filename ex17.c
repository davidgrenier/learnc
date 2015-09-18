#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    struct Address rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void printAddress(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void loadDatabase(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to load database.");
}

struct Connection *openDatabase(char* filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die("Memory error");

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
            loadDatabase(conn);
        }
    }

    if (!conn->file) die("Failed to open the file");

    return conn;
}

void closeDatabase(struct Connection *conn)
{
    if (conn) {
        if (conn->file) fclose(conn->file);
        if (conn->db) free(conn->db);
        free(conn);
    }
}

void writeDatabase(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to write database.");

    rc = fflush(conn->file);
    if (rc == -1) die("Cannot flush database");
}

void createDatabase(struct Connection *conn)
{
    for (int i = 0; i < MAX_ROWS; i++) {
        struct Address addr = { .id = i, .set = 0 };
        conn->db->rows[i] = addr;
    }
}

void set(struct Connection *conn, int id, char *name, char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first");

    addr->set = 1;

    char* res = strncpy(addr->name, name, MAX_DATA);
    if (!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res) die("Email copy failed");
}

void get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        printAddress(addr);
    } else {
        die("ID is not set");
    }
}

void delete(struct Connection *conn, int id)
{
    struct Address addr = { .id = id, .set = 0 };
    conn->db->rows[id] = addr;
}

void list(struct Connection *conn)
{
    for (int i = 0; i < MAX_ROWS; i++) {
        struct Address *addr = &conn->db->rows[i];

        if (addr->set) printAddress(addr);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) die("Usage: ex17 <dbfile> <action> [action parameters]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = openDatabase(filename, action);

    int id = 0;
    if (argc > 3) id = atoi(argv[3]);

    switch(action) {
        case 'c':
            createDatabase(conn);
            writeDatabase(conn);
            break;

        case 'g':
            if (argc != 4) die("Need an id to get");
            get(conn, id);
            break;

        case 's':
            if (argc != 6) die("Need id, name, email to set");
            set(conn, id, argv[4], argv[5]);
            writeDatabase(conn);
            break;
            
        case 'd':
            if (argc != 4) die("Need an id to delete");
            delete(conn, id);
            writeDatabase(conn);
            break;

        case 'l':
            list(conn);
            break;
        default:
            die("Invalid action, only c=create, g=get, s=set, d=delete, l=list");
    }

    closeDatabase(conn);

    return 0;
}
