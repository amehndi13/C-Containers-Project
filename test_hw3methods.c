//HW3 600.120 Spring 2015
//JHED: amehndi1
//Name: Anuj Mehndiratta
//Date: March 9, 2016

#include "hw3methods.h"

int fileeq(char lhsName[], char rhsName[]);

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("This test requires two input files.\n");
		return 1;
	}
	int match = fileeq(argv[1], argv[2]);
	if (match) {
		printf("success!");
		return 0;
	} else {
		printf("test failed");
		return 0;
	}
}

/*
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match.
 * TAKEN FROM ASSIGNMENT 2 TESTING HINTS!!
 */
int fileeq(char lhsName[], char rhsName[]) {
    FILE* lhs = fopen(lhsName, "r");
    FILE* rhs = fopen(rhsName, "r");

    // don't compare if we can't open the files
    if (lhs == NULL || rhs == NULL) return 0;

    int match = 1;
    // read until both of the files are done or there is a mismatch
    while (!feof(lhs) || !feof(rhs)) {
        if (feof(lhs) ||                  // lhs done first
            feof(rhs) ||                  // rhs done first
            (fgetc(lhs) != fgetc(rhs))) { // chars don't match
            match = 0;
            break;
        }
    }
    fclose(lhs);
    fclose(rhs);
    return match;
}


