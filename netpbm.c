#include <stdio.h>

int empty(){
	char n;
	do { /* function for white characters*/
		n=getchar();
	} while (n == ' ' || n == '\t' || n == '\n');
	return n;
}

void comment() { /* function for comments*/
	do {
	} while (getchar() != '\n');
}

int read_number(char w) { /* function for  width ,max ,height*/
	int n = 0;
	while(w != '\n'  && w!=' ' && w!='\t'){
		if(w>='0' && w<='9' ){
			n=10*n + (w-'0'); /* ASCII must be between 0 -9*/
		}
		else{
			return 0;
		}
		w=getchar();
	} /* end of while */
	return n;
}

int main(void){
	int width=0,height=0,pixel,maxgrey;
	int n,y,w,t,h,max;
	int i,j;
	unsigned int R,G,B;

	if(getchar()!='P'){                /* check if magic number starts from P*/ 
		printf("Input Error\n");
		return 1;
	}

	n=getchar();
	if(n!='2' && n!='3' && n!='5' && n!='6'){
		printf("Input Error\n"); /* check if number after P is '1' or '4'*/
		return 2;
	}

	t=empty(); /* now t==# cause empty returns usefull characters*/
	while (t=='#'){ /* check for comments until getchar finds '\n' after '#' */
		comment(); /* we dont need to store the comments into memory*/
		t = empty();
	}

	width = read_number(t);
	if (width == 0) {
		printf("Input Error\n"); 
		return 3;
	}

	t = empty(); /* ignore white characters  */

	height = read_number(t); /* make the height*/
	if (height == 0) {
		printf("Input Error\n"); 
		return 4;
	}

	if(n=='2' || n=='5'){
		t = empty();
		max = read_number(t);
		if (max == 0) {
			printf("Input Error\n"); 
			return 5;
		}
	} /* read the max of  greyscale */

	n--; /* we must to convert images with magic nubmer n to image with magic number n-1. ex: p5-->p4*/
	printf("P%c\n%d %d\n", n, width, height);
	if(n=='2' || n=='5'){
		printf("255\n");
	}

	if (n == '2') { /* if we want to convert asci ppm to pgm  P3-->P2 */
		for (i = 0; i<height; i++) {
			for (j = 0; j < width; j++) { /* read 3 bytes . One for R  one for G one for B*/
				t = empty(); /* IGNORE WHITE CHARACTERS BETWEEN RGB*/
				R = read_number(t);
				t = empty();
				G = read_number(t);
				t = empty();
				B = read_number(t);
				printf("%d ", (int) (0.299*R+0.587*G+0.114*B)); /* print the conversion. We need to cast for "KATW AKERAIO MEROS"*/
			}
			putchar('\n');
		}
		putchar('\n');
	}
	else if (n == '1') { /* if we want to convert ASCI pgm to pbm P2-->P1*/
		int m = (max+1)/2; 
		for (i = 0; i<height; i++) {
			for (j = 0; j < width; j++) {
				t = empty(); /* ignore white characters*/
				R = read_number(t); /* at this step we need to read 1 byte because pgm format it use 1 byte for each pixel*/
				if (R > m)
					putchar('0'); 
				else
					putchar('1');
				putchar(' ');
			}
			putchar('\n');
		}
		putchar('\n');
	}
	else if (n == '5') { /* if  we want to convert BINARY ppm to pgm P6--> P( 6 -1)*/
		for (i = 0; i<height; i++) {
			for (j = 0; j < width; j++) {
				R = getchar(); /* there's no spaces*/
				G = getchar();
				B = getchar();
				putchar(0.299*R+0.587*G+0.114*B);
			}
		}
	}
	else if (n == '4') { /* if we want to convert BINARY pgm to pbm P5--->P(5-1)*/
		int count = 0; /* bit counter */
		int m = (max+1)/2;
		for (i = 0; i<height; i++) {
			int count = 0; /* initialization */
			for (j = 0; j < width; j++) {
				count++; /* increase counter*/
				R=getchar(); /* read the byte */
				if (R > m) 
					R = 0;
				else
					R = 1;
				t = 2*t + R;
				if (count == 8) { /* count=8 means that the bits we were read  are divised by 8 */
					count = 0; 
					putchar(t); 
				}
			}
			if (count != 0) { /* count !=0 m means that we must complete with bits*/
			    for (j = count; j< 8; j++) {  /* complete the rest of the bits  */
				t = 2*t + 1; /* bit padding */
			    }
			putchar(t);
	        }
		}
		
	}
	return 0;
}


//=================================================================================================

	
 
 
 
 

