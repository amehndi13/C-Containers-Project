//HW3 600.120 Spring 2015
//JHED: amehndi1
//Name: Anuj Mehndiratta
//Date: March 9, 2016

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct transcript_struct {
    struct catalog_struct *course;
    struct transcript_struct *next;
    int year;
    int semester;
    char grade[3];
};

struct catalog_struct {
    float credit;
    char title[32];
	int intranscript;
    char division[3];
    int department;
    int coursenumber;
};

void displaycatalog(int numcourses,  struct catalog_struct catalog[]);
int countcourses(char* inFile);
int searchcoursecatalog(char course[], struct catalog_struct catalog[], int numcourses);
int updatetitle(char course[], struct catalog_struct catalog[], int numcourses);
int displaytranscript( struct transcript_struct *head);
int removefromtranscript(char course[], struct transcript_struct **head);
int findcourseintranscript(char course[], struct catalog_struct catalog[], struct transcript_struct *head, int numcourses);
int calculategpa(struct transcript_struct *head);
int updatecredit(char course[], struct catalog_struct catalog[], int numcourses);
int addtotranscript(char course[], struct catalog_struct catalog[], struct transcript_struct **head, int numcourses);

