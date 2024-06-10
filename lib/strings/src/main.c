#include "d_strings.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	string s1, s2, s3;
	int i;
	char c, stop;

	s1 = String(EMPTY_STRING);
	s2 = String(EMPTY_STRING);
	s3 = String(EMPTY_STRING);

	AssignString(s1, "Alex");
	AssignString(s2, "Tevre");

	AssignString(s1, "TSIRLIMPINTIMPI");
	
	Copy(s2, s1);
	AssignString(s2, "Eimai mikros ti thes");
	AssignString(s3, "1234542");
	PrintLnString(s2);

	stop = 0;
	while(stop == 0){
		scanf("%d", &i);
		getchar();
		switch(i){
			case 0:
				c = getchar();
				PushFrontString(s2, c);
				PrintLnString(s2);
				printf("%ld\n", SizeString(s2));
				break;
			case 1:
				c = getchar();
				PushBackString(s2, c);
				PrintLnString(s2);
				printf("%ld\n", SizeString(s2));
				break;
			case 2:
				c = PopFrontString(s2);
				printf("%c\n", c);
				PrintLnString(s2);
				printf("%ld\n", SizeString(s2));
				break;
			case 3:
				PopBackString(s2);
				printf("%c\n", c);
				PrintLnString(s2);
				printf("%ld\n", SizeString(s2));
				break;
			default:
				stop = 1;
		}
		printf("\n\n\n");
	}

	DeleteString(s1);
	DeleteString(s2);
	DeleteString(s3);
	return 0;
}
