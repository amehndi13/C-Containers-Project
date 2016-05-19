//HW3 600.120 Spring 2015
//JHED: amehndi1
//Name: Anuj Mehndiratta
//Date: March 9, 2016

#include "hw3methods.h"

int main(int argc, char *argv[]){
	if(argc < 2) {
		return 0;
	}
	char command;
	struct catalog_struct catalog[countcourses(argv[1])];
	FILE* inFile = fopen(argv[1], "r");
	char coursestring[48] = {'\0'};
	char firstletter;
	char letter;
	int i;
	int courseindex = 0;
	while((firstletter = fgetc(inFile))!=EOF){
		coursestring[0] = firstletter;
		i = 1;
		while((letter = fgetc(inFile))!='\n'){
			coursestring[i] = letter;
			i++;
		}
		struct catalog_struct line;
		line.division[2] = '\0';
		(line).division[0] = coursestring[0];
		(line).division[1] = coursestring[1];
		int d1 = coursestring[3] - '0';
		int d2 = coursestring[4] - '0';
		int d3 = coursestring[5] - '0';
		int dep = (100 * d1) + (10 * d2) + d3;
		(line).department = dep;
		int n1 = coursestring[7] - '0';
    	int n2 = coursestring[8] - '0';
   		int n3 = coursestring[9] - '0';
    	int departmentalnum = (100 * n1) + (10 * n2) + n3;
    	(line).coursenumber = departmentalnum;
		for(int p=15; p<48; p++) {
			(line).title[p-15] = coursestring[p];
		}
		float c1 = coursestring[11] -'0';
		float c2 = coursestring[13] -'0';
		c2 = c2/10;
		c1 = c1 + c2;
		(line).credit = c1;
		line.intranscript = 0;
		struct catalog_struct copy;
		copy = line;
		catalog[courseindex] = copy;
		courseindex++;
		memset(&coursestring, '\0', sizeof(coursestring));
	}
	fclose(inFile);
	int position;
	struct transcript_struct *transcript_head = NULL;
	char user_input[50] = {'\0'};
	do {
		printf("Please enter your command: ");
		memset(user_input, '\0', sizeof(user_input));
		position = 0;
		while((command = getchar())!= '\n') {
			user_input[position] = command;
			position++;
		}
		user_input[0] = tolower(user_input[0]);
		int coursecount = countcourses(argv[1]);
		if(user_input[0] == 'p') {
			displaycatalog(coursecount, catalog);
		} else if(user_input[0] == 'c') {
			searchcoursecatalog(user_input, catalog, coursecount);
		} else if(user_input[0] == 't') {
			updatetitle(user_input, catalog, coursecount);
		} else if(user_input[0] == 'r') {
			updatecredit(user_input, catalog, coursecount);
		} else if(user_input[0] == 'a') {
			addtotranscript(user_input, catalog, &transcript_head, coursecount);
		} else if(user_input[0] == 'd') {
			removefromtranscript(user_input, &transcript_head);
		} else if(user_input[0] == 'i') {
			displaytranscript(transcript_head);
		} else if(user_input[0] == 'o') {
			findcourseintranscript(user_input, catalog, transcript_head, coursecount);
		} else if(user_input[0] == 'g') {
			calculategpa(transcript_head);
		} else if(user_input[0] != 'q') {
			printf("Invalid Input\n");
		}
	} while(user_input[0]!='q');
	if(user_input[0] == 'q') { 
		return 0;
	}
}
