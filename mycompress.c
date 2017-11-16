#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define DEBUG 0

int compress (FILE *input, FILE *output);
void usage (){
	printf("\r\n./mycompress -o output_file inputfiles....\r\n");
}

int main (int argc, char *argv[]) {
	int ch;//return value of getopt.
	FILE *input[argc], *output;
	int inputfiles=0;
	int x;//counter for for-loop
	int OFLAG=0; 
	int IFLAG=0;
	
	while(optind < argc) {
		if ((ch = getopt(argc, argv, "o:")) != -1) {
			switch (ch) {
			case 'o':
				output = fopen(optarg, "w");
				OFLAG=1;
				#if DEBUG ==1
				printf("Output = %s\r\n",optarg);
				#endif
				break;
			case '?':
			default:
				usage();
			}
		}
		else {
			#if DEBUG ==1
			printf("Input: %s\r\n",argv[optind]);
			#endif
			input[inputfiles]=fopen(argv[optind],"r"); 
			#if DEBUG ==1
			printf("Input: %d/%d\r\n",inputfiles,input[inputfiles]);
			#endif
			IFLAG=1;
			optind++;
			inputfiles++;
			
		}
    }
    if(IFLAG == 0){//no inpput
    	if(OFLAG == 0){ // no output
    		compress(stdin,stdout); //read from terminal, write on terminal
    	}
    	else {
    		compress(stdin,output);//no input, yes output. read from stdin, write on outputfile
    	}
    }
    else if(OFLAG == 0) { //no output, yes input
    	for(x=0;x<inputfiles;x++) {
    		compress(input[x],stdout);
    		fclose(input[x]);
    	}
    }
    else { //yes input,yes output.
    	for(x=0;x<inputfiles;x++) {
    		compress(input[x],output);
    		fclose(input[x]);
    	}
    }
    
    fclose(output);
    
    
    
    return 0;
}

int compress (FILE *input, FILE *output) {
	char read,before;
	int cnt=1;
	int counter1=0;
	int counter2=0;
	#if DEBUG ==1
	fprintf(stdout,"compressfunction %d",input);
	#endif
	before=fgetc(input);
	counter1++;
	if(feof(input))
		return 0;
	
	fprintf(output,"%c",before);
	counter2++;
	while((read = fgetc(input))) {
		if(feof(input))
			break;
		#if DEBUG ==1
		fprintf(stdout,"read %c\r\n",read);
		#endif
		counter1++;
		if(read == before){
			cnt++;
			
		}
		else {
			before=read;
			#if DEBUG ==1
			fprintf(stdout,"write %c\r\n",read);
			#endif
			fprintf(output,"%d%c",cnt,read);
			counter2+=2;
			
			cnt=1;
		}	
	}
	fprintf(output,"%d",cnt);
	counter2++;
	
    fprintf(stderr,"Gelesen:\t%d Zeichen\r\n" , counter1);
    fprintf(stderr,"Geschrieben:\t%d Zeichen\r\n", counter2);
    fprintf(stderr,"Komprimierungsrate:\t%.1f %%\r\n" ,(((float)counter2/counter1)) * 100);
    
    return 0;
}
