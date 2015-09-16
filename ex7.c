#include <stdio.h>

int main(int argc, char *argv[])
{
	int bugs = 100;
	double bug_rate = 1.2;

	printf("You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate);

	long universe_of_defects = 1L * 1024L * 1024L * 1024L;
	printf("The entire universe has %ld bugs.\n", universe_of_defects);

	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", expected_bugs);

	double portion_of_universe = expected_bugs / universe_of_defects;
	printf("That is only a %e portion of the universe.\n", portion_of_universe);

	char care_factor = '\0';
	int care_percentage = bugs * care_factor;
	printf("Which means you should care %d%%.\n", care_percentage);

	//printf("The nul string: %s.\n", care_factor);
	printf("The nul character: %c.\n", care_factor);
	printf("A boolean perhaps: %d.\n", care_factor == 0);
	printf("And here would be false? %d.\n", care_factor == 9);

	return 0;
}
