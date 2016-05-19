//HW3 600.120 Spring 2015
//JHED: amehndi1
//Name: Anuj Mehndiratta
//Date: March 9, 2016

#include "hw3methods.h"

int countcourses(char* f) {
	FILE* inFile = fopen(f,"r");
	int counter = 0;
	char c;
	while((c = fgetc(inFile))!=EOF) {
		if(c=='\n') {
			counter++;
		}
	}
	fclose(inFile);
	return counter;
}

void displaycatalog(int numcourses, struct catalog_struct catalog[]){
	for(int i=0; i< numcourses; i++)
    	printf("%s.%d.%d %.1f %s\n", catalog[i].division, catalog[i].department, 
    			catalog[i].coursenumber, catalog[i].credit, catalog[i].title);
}

int updatetitle(char course[], struct catalog_struct catalog[], int numcourses){
	char div[3] = {course[2], course[3], '\0'};
    int digitone = course[5] - '0';
    int digittwo = course[6] - '0';
    int digitthree = course[7] - '0';
    int dep = (digitone * 100) + (digittwo * 10) + digitthree;
    int digitfour = course[9] - '0';
    int digitfive = course[10] - '0';
    int digitsix = course[11] - '0';
    int crsnum = (digitfour * 100) + (digitfive * 10) + digitsix;
	char updatedtitle[33];
	for(int o = 13; o< 50; o++)
		updatedtitle[o-13] = course[o];
	updatedtitle[32] = '\0';
	for(int i = 0; i< numcourses; i++){
        if(catalog[i].division[0] == div[0] && catalog[i].division[1] == div[1]  && 
        		catalog[i].department == dep && catalog[i].coursenumber == crsnum) {
			memset(&catalog[i].title, '\0', sizeof(catalog[i].title));
			for(int j = 0; j<33; j++)
				catalog[i].title[j] = updatedtitle[j];
			printf("Done\n");
			return 1;
		}
	}
	printf("Absent\n");
	return 0;
}

int updatecredit(char course[], struct catalog_struct catalog[], int numcourses){
    char div[3] = {course[2], course[3], '\0'};
    int digitone = course[5] - '0';
    int digittwo = course[6] - '0';
    int digitthree = course[7] - '0';
    int dep = (digitone * 100) + (digittwo * 10) + digitthree;
    int digitfour = course[9] - '0';
    int digitfive = course[10] - '0';
    int digitsix = course[11] - '0';
    int crsnum = (digitfour * 100) + (digitfive * 10) + digitsix;
    int inputlen = 0;
    while(course[inputlen]!='\0')
        inputlen++;
	float c1 = course[13] - '0';
	float c2 = course[15] - '0';
	c2 = c2/10;
	c1 = c1 + c2;
    for(int i = 0; i< numcourses; i++){
        if(catalog[i].division[0] == div[0] && catalog[i].division[1] == div[1]  && 
        		catalog[i].department == dep && catalog[i].coursenumber == crsnum){
			catalog[i].credit = c1;
            printf("Done\n");
            return 1;
        }
    }
	printf("Absent\n");
	return 0;
}

int calculategpa(struct transcript_struct *head){
	float totalcredits = 0;
	float points = 0;
	float numerator = 0;
	struct transcript_struct *cursor = head;
	if (head == NULL) {
		printf("0.0");
		return 0;
	}
	int notdone = 1;
	while(notdone) {
		if(cursor == NULL) {
			break;
		}
		if ((*cursor).grade[0] == 'A'){
			if ((*cursor).grade[1] == '-')
				points = 3.7;
			else
				points = 4.0;
		}
		if ((*cursor).grade[0] == 'B'){
        	if ((*cursor).grade[1] == '-')
                points = 2.7;
            if ((*cursor).grade[1] == '+')
        		points = 3.3;
			else
				points = 3.0;
		}
		if ((*cursor).grade[0] == 'C'){
            if ((*cursor).grade[1] == '-')
                points = 1.7;
            if ((*cursor).grade[1] == '+')
                points = 2.3;
            else
                points = 2.0;
            }
		if ((*cursor).grade[0] == 'D'){
            if ((*cursor).grade[1] == '-')
                  points = 0.0;
            if ((*cursor).grade[1] == '+')
                points = 1.3;
            else
                points = 1.0;
            }
		if ((*cursor).grade[0] == 'F')
			points = 0.0;
		totalcredits = totalcredits + (*cursor).course->credit;
		numerator = numerator + points * (*cursor).course->credit;
		cursor = (*cursor).next;
	}
	printf("%.2f\n\n", (numerator/totalcredits));
	return 1;
}

int findcourseintranscript(char course[], struct catalog_struct catalog[], struct transcript_struct *head, int numcourses){
    char div[3] = {course[2], course[3], '\0'};
    int digitone = course[5] - '0';
    int digittwo = course[6] - '0';
    int digitthree = course[7] - '0';
    int dep = (digitone * 100) + (digittwo * 10) + digitthree;
    int digitfour = course[9] - '0';
    int digitfive = course[10] - '0';
    int digitsix = course[11] - '0';
    int crsnum = (digitfour * 100) + (digitfive * 10) + digitsix;
	int catalogpos = 0;
	int found = 0;
    for(int i = 0; i< numcourses; i++){
		if(catalog[i].division[0] == div[0] && catalog[i].division[1] == div[1]  && 
				catalog[i].department == dep && catalog[i].coursenumber == crsnum){ 
            found = 1;
            catalogpos = i;
        }
    }
    if (found == 0){
        printf("Invalid Entry\n");
        return 0;
    }
	struct transcript_struct *cursor = head;
	int intrans = 0;
	char sem2[3] = {'f', 's', '\0'};
	while((*cursor).next != NULL){
		if((*cursor).course == &catalog[catalogpos]){
			printf("%d.%c %s\n", (*cursor).year, sem2[(*cursor).semester], (*cursor).grade);
			intrans = 1;
		}
	cursor = (*cursor).next;
	}
	if((*cursor).next == NULL && (*cursor).course == &catalog[catalogpos]){
		printf("%d.%c %s\n", (*cursor).year, sem2[(*cursor).semester], (*cursor).grade);
                intrans = 1;
	}
	if(intrans == 0){
		printf("Absent\n");
		return 0;
	}
	
	return 1;
}

int removefromtranscript(char course[], struct transcript_struct **head){
    char div[3] = {course[2], course[3], '\0'};
    int digitone = course[5] - '0';
    int digittwo = course[6] - '0';
    int digitthree = course[7] - '0';
    int dep = (digitone * 100) + (digittwo * 10) + digitthree;
    int digitfour = course[9] - '0';
    int digitfive = course[10] - '0';
    int digitsix = course[11] - '0';
    int crsnum = (digitfour * 100) + (digitfive * 10) + digitsix;
	int y1 = course[13] - '0';
    int y2 = course[14] - '0';
    int y3 = course[15] - '0';
    int y4 = course[16] - '0';
    int yr = y1*1000 + y2*100 + y3*10 + y4;
    int sem = 0;
    if (course[18] == 's')
        sem = 1;
    if(*head == NULL){//if list is empty
        printf("Transcript was empty.\n ");
        return 1;
    }
    struct transcript_struct *cursor = *head;
    struct transcript_struct *temp = *head;
	while((*cursor).next != NULL){
		if((*cursor).course->division[0] == div[0] && (*cursor).course->division[1] == div[1] && 
				(*cursor).course->department == dep && (*cursor).course->coursenumber == crsnum && 
				(*cursor).year == yr && (*cursor).semester == sem) {
			break;
		}
		temp = cursor;
		cursor = (*cursor).next;
	}
	if((*cursor).course->division[0] == div[0] && (*cursor).course->division[1] == div[1] && 
			(*cursor).course->department == dep && (*cursor).course->coursenumber == crsnum && 
			(*cursor).year == yr && (*cursor).semester == sem) {
		if(temp == cursor ) {
			*head = (*cursor).next;
			free(&(*cursor));
			printf("Done\n");
			return 1;
		}
		(*temp).next = (*cursor).next;
		free(&(*cursor));
		printf("Done\n");
                return 1;
	}
	printf("Absent\n");
	return 0;
}

int addtotranscript(char course[], struct catalog_struct catalog[], struct transcript_struct **head, int numcourses){
    char div[3] = {course[2], course[3], '\0'};
    int digitone = course[5] - '0';
    int digittwo = course[6] - '0';
    int digitthree = course[7] - '0';
    int dep = (digitone * 100) + (digittwo * 10) + digitthree;
    int digitfour = course[9] - '0';
    int digitfive = course[10] - '0';
    int digitsix = course[11] - '0';
    int crsnum = (digitfour * 100) + (digitfive * 10) + digitsix;
	int y1 = course[13] - '0';
	int y2 = course[14] - '0';
	int y3 = course[15] - '0';
	int y4 = course[16] - '0';
	int yr = y1*1000 + y2*100 + y3*10 + y4;
	int sem = 0;
	if (course[18] == 's')
		sem = 1;
	char g[3] = {course[20], course[21], '\0'};
	int found = 0;
	int catalogpos;
	for(int i = 0; i< numcourses; i++){
        if( catalog[i].division[0] == div[0] && catalog[i].division[1] == div[1]  && 
        			catalog[i].department == dep && catalog[i].coursenumber == crsnum ) {
			found = 1;
			catalogpos = i;
		}
	}
	if (found == 0) {
		printf("Invalid Entry\n");
		return 0;
	}
	catalog[catalogpos].intranscript = 1;
	struct catalog_struct *crs = &catalog[catalogpos];
	struct transcript_struct *node = malloc(sizeof(struct transcript_struct));
    (*node).course = crs;
	(*node).year = yr;
	(*node).grade[0] = g[0];   
	(*node).grade[1] = g[1];   
	(*node).grade[2] = g[2];
	(*node).semester = sem;
	(*node).next = NULL;
	if(*head == NULL){//if list is empty
		*head = node;
		printf("Done\n");
		return 1;
	}
	struct transcript_struct *cursor = *head;
	struct transcript_struct *temp = *head;
	while((*cursor).next != NULL && (*node).year >= (*cursor).year) {
		if((*node).year == (*cursor).year) {
			while((*cursor).next != NULL && (*node).semester < (*cursor).semester && (*node).year == (*cursor).year) {
				temp = cursor;
				cursor = (*cursor).next;
			}
		break;
		}
		else {
			temp = cursor;
			cursor = (*cursor).next;
		}
	}
	if(temp == cursor && ((*node).year < (*cursor).year || ((*node).year == (*cursor).year && 
			(*node).semester >= (*cursor).semester))) {
		if((*node).year == (*cursor).year && (*node).semester == (*cursor).semester && (*node).course == (*cursor).course) {
			printf("Done\n");
			return 0;
		}
		else {
			*head = node;
			(*node).next = cursor;
			printf("Done\n");
			return 1;
		}
	}
	if((*cursor).year > (*node).year || ((*cursor).year == (*node).year && (*node).semester >= (*cursor).semester)) {
        if((*node).year == (*cursor).year && (*node).semester == (*cursor).semester && (*node).course == (*cursor).course) {
        	printf("Done\n");
            return 0;
        }
		else {
			(*temp).next = node;
			(*node).next = cursor;
			printf("Done\n");
			return 1;
		}
	}
	else {
        (*cursor).next = node;
		printf("Done\n");
		return 1;
	}
	return 0;
}

int displaytranscript( struct transcript_struct *head) {
	if( head == NULL) {
		printf("Transcript is currently empty\n");
		return 0;
	}
	char sem;
	while(head!=NULL) {
		if((*head).semester == 0) { 
			sem = 'f';
		} else {
			sem = 's';
		}
		printf("%c%c.%d.%d %.1f %s %d.%c %s\n", (*head).course->division[0], 
				(*head).course->division[1],  (*head).course->department, (*head).course->coursenumber, 
				(*head).course->credit, (*head).course->title, (*head).year, sem, (*head).grade);
		head = (*head).next;
	}
	
	return 1;
}

int searchcoursecatalog(char course[], struct catalog_struct catalog[], int numcourses) {
	char div[3] = {course[2], course[3], '\0'};
	int digitone = course[5] - '0';
    int digittwo = course[6] - '0';
    int digitthree = course[7] - '0';
    int dep = (digitone * 100) + (digittwo * 10) + digitthree;
    int digitfour = course[9] - '0';
    int digitfive = course[10] - '0';
    int digitsix = course[11] - '0';
    int crsnum = (digitfour * 100) + (digitfive * 10) + digitsix;
	for(int i = 0; i< numcourses; i++){
		if(catalog[i].division[0] == div[0] && catalog[i].division[1] == div[1]  && 
				catalog[i].department == dep && catalog[i].coursenumber == crsnum){
			printf("%.1f %s\n\n", catalog[i].credit, catalog[i].title);
			return 1;
		}
	}
	printf("Absent\n");
	return 0;
}

