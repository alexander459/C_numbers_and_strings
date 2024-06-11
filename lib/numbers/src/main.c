#include <stdio.h>
#include "numbers.h"
#include <stdlib.h>

int main(void){
	number n1, n2, n3;
	int i, stop;

	Number(&n1, NULL);
	Number(&n2, NULL);
	Number(&n3, NULL);

	AssignNumber(n1, "-43.6576");
	AssignNumber(n2, "0.87");
	SubNumber(n3, n1, n2);
	PrintLnNumber(n3);

#ifdef alex
	stop = 0;
	while(stop == 0){
		scanf("%d", &i);
		getchar();
		switch(i){
			case 0:
				ReadNumber(n1);
				ReadNumber(n2);
				AddNumber(n3, n1, n2);
				PrintLnNumber(n3);
				break;
			/*case 1:
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
			case 4:
				c = getchar();
				if(RemoveFromString(s2, c) == 1)
					printf("ok!\n");
				else
					printf("Nope...\n");
				PrintLnString(s2);
				printf("%ld\n", SizeString(s2));
				break;*/
			default:
				stop = 1;
		}
		printf("\n\n\n");
	}
#endif
	DeleteNumber(n1);
	DeleteNumber(n2);
	DeleteNumber(n3);

	return 0;
}
