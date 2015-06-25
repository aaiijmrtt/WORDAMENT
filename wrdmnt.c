#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//dictionary of words was taken from http://www.mieliestronk.com/wordlist.html
char *brd; //stores the board of play, rowwise, left to right
//function to match tiles on board to wrd, recursively.
//chck is maintained to store tile positions of found letter,
//and check connectivity of tiles matched at the end of word
int mtch(char *wrd,char *chck) {
	int i,j,t;
	//checking validity of matched tiles on reaching end of word
	if(*wrd=='\0') {
		for(i=1;chck[i]!='\0';++i) {
			if(chck[i+1]!='\0')
				//checking for the connectivity of neighbouring tiles
				switch(chck[i]%4) {
					case 0:	switch(chck[i+1]-chck[i]) {
								case -5:
								case -4:
								case -1:
								case  3:
								case  4:	break;
								default:	return 0;
							}
							break;
					case 1:	switch(chck[i+1]-chck[i]) {
								case -4:
								case -3:
								case  1:
								case  4:
								case  5:	break;
								default:	return 0;
							}
							break;
					case 2:
					case 3:	switch(chck[i+1]-chck[i]) {
								case -5:
								case -4:
								case -3:
								case -1:
								case  1:
								case  3:
								case  4:
								case  5:	break;
								default:	return 0;
							}
							break;
				}
			//checking for the use of the same tile more than once
			for(j=i+1;chck[j]!='\0';++j)
				if(chck[i]==chck[j])
					return 0;
		}
		return 1;
	}
	for(i=0;i<16;++i)
		//matching tile to subsequent letter in word
		if(brd[i]==*wrd) {
			*chck=i+1;
			//matching remaining word to tiles recursively
			if(mtch(wrd+1,chck-1))
				return 1;
		}
	return 0;
}
//function to match all words read from dictionary beginning with chr,
//and print all matches to stdout.
void fnd(char chr) {
	char *strng=(char*)malloc(50*sizeof(char));
	char *flnm=(char*)malloc(16*sizeof(char));
	char *chck=(char*)malloc(17*sizeof(char));
	flnm[0]='r';
	flnm[1]='e';
	flnm[2]='s';
	flnm[3]='o';
	flnm[4]='u';
	flnm[5]='r';
	flnm[6]='c';
	flnm[7]='e';
	flnm[8]='s';
	flnm[9]='/';
	flnm[10]=chr;
	flnm[11]='.';
	flnm[12]='t';
	flnm[13]='x';
	flnm[14]='t';
	flnm[15]='\0';
	//opening the dictionary containing all words beginning with the letter
	FILE *flptr=fopen(flnm,"r");
	int i;
	//reading each word in dictionary
	while(fgets(strng,50,flptr)!=NULL) {
		i=0;
		//counting number of letters in word read from dictionary
		while((strng[i]!='\0')&&(strng[i]!='\n')&&(strng[i]!='\r'))
			++i;
		//skipping words that exceed board of play in length
		if(i>16)
			continue;
		strng[i]='\0';
		//matching word read from dictionary and printing matches
		if(mtch(strng,chck+16)) {
			printf("%s\n",strng);
		}
	}
	//freeing allocated resources
	fclose(flptr);
	free(strng);
	free(flnm);
	free(chck);
}
int main(int argc,char *argv[])	{
	if((argc!=2)||(strlen(argv[1])!=16)) {
		printf("[USAGE] %s [CHAR[16] IN CAPS]\n",argv[0]);
		exit(-1);
	}
	brd=(char*)malloc(16*sizeof(char));
	int i,j;
	//inputing the board of play
	for(i=0;i<16;++i)
		brd[i]=argv[1][i];
	//selecting letter to begin matching words from
	for(i=0;i<16;++i) {
		for(j=0;j<i;++j)
			//words beginning with this letter have been checked earlier
			if(brd[j]==brd[i])
				break;
		//words beginning with this letter have not been checked earlier
		if(j==i)
			fnd(brd[i]);
	}
	return 0;
}
