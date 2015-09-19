#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Address {
    int id;
    int set;
    char* name;
    char* email;
};

struct Database {
    int maxData;
    int maxRows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void closeDatabase(struct Connection *conn)
{
    if (conn) {
        if (conn->db) free(conn->db);
        if (conn->file) fclose(conn->file);
        free(conn);
    }
}

void diem(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void die(const char *message, struct Connection *conn)
{
    closeDatabase(conn);

    diem(message);
}

void loadDatabase(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to load database.", conn);
}

struct Connection *openDatabase(char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error", conn);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error", conn);

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) loadDatabase(conn);
    }

    if (!conn->file) die("Failed to open the file", conn);

    return conn;
}

void writeDatabase(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1) die("Failed to write database.", conn);

    rc = fflush(conn->file);
    if (rc == -1) die("Cannot flush database.", conn);
}

void createDatabase(struct Connection *conn, int maxData, int maxRows)
{
    conn->db->maxRows = maxRows;
    conn->db->maxData = maxData;
    conn->db->rows = malloc(maxRows * sizeof(struct Address *));

    char *empty = malloc(maxData);

    for (int i = 0; i < maxRows; i++) {
        struct Address addr = { .id = i, .set = 0, .name = empty, .email = empty};

        conn->db->rows[i] = addr;
    }
}

int copyString(char *target, const char *source, int maxLength)
{
    char *res = strncpy(target, source, maxLength);

    if (strlen(source) > maxLength) target[maxLength-1] = '\0';

    return !res;
}

void set(struct Connection *conn, int id, const char *name, const char *email)
{
    int maxData = conn->db->maxData;
    struct Address *addr = &conn->db->rows[id];
    
    if (addr->set) die("Already set, delete it first", conn);

    addr->set = 1;

    int fail = copyString(addr->name, name, maxData);
    if (fail) die("Name copy failed", conn);

    fail = copyString(addr->email, email, maxData);
    if (fail) die("Email copy failed", conn);
}

void printAddress(struct Address *addr)
{
    printf("%i %s %s\n", addr->id, addr->name, addr->email);
}

void list(struct Connection *conn)
{
    int maxRows = conn->db->maxRows;
    for (int i = 0; i < maxRows; i++) {
        struct Address *addr = &conn->db->rows[i];

        if (addr->set) printAddress(addr);
    }
}

void get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        printAddress(addr);
    } else {
        die("Id is not set", conn);
    }
}

void delete(struct Connection *conn, int id)
{
    struct Address addr = { .id = id, .set = 0 };

    conn->db->rows[id] = addr;
}

int main(int argc, char *argv[]) {
    if (argc < 3) diem("USAGE: ex17 <dbfile> <action> [action parameters]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = openDatabase(filename, action);

    int id = 0;
    if (argc > 3) id = atoi(argv[3]);

    switch (action) {
        case 'c':
            if (argc < 5) die("Need maxData, maxRows to create", conn);

            int maxData = id;
            int maxRow = atoi(argv[4]);
                
            createDatabase(conn, maxData, maxRow);
            writeDatabase(conn);
            break;

        case 'g':
            if (argc < 4) die("Need an id to get", conn);

            get(conn, id);
            break;

        case 'l':
            list(conn);
            break;

        case 's':
            if (argc < 6) die("Need id, name, email to set", conn);

            set(conn, id, argv[4], argv[5]);
            writeDatabase(conn);
            break;
            
        case 'd':
            if (argc < 4) die("Need an id to delete", conn);

            delete(conn, id);
            writeDatabase(conn);
            break;

        default:
            die("Invalid action, only: c=create, g=get, l=list, s=set, d=delete", conn);
    }

    closeDatabase(conn);

    return 0;
}

