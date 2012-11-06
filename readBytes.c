#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char map[16] ={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
int main(int argc,char *argv[]) {
	if(argc == 3) {
		FILE *fp = fopen(argv[1],"r");
		char actualKey[41];
		int i=0;
		char buffer[1024];
		if(fp != NULL) {
			int noOfBytesRead = fread(buffer,1,1024,fp);
			int j=0;
			actualKey[40] = NULL;
			for(i=0;i < noOfBytesRead ;i++) {
				actualKey[j++] = map[((unsigned)(buffer[i] & 0xF0)) >> 4];
				actualKey[j++] = map[((unsigned)(buffer[i] & 0x0F))];
			}
			printf("\nKey:%s\n",actualKey);
			fclose(fp);
		}
		printf("\nThis might take some time, Please wait....\n");
		fp = fopen(argv[2],"r");
		int found = 0;
		if(fp != NULL) {
			while(fgets(buffer,sizeof(buffer),fp) != NULL) {
				if(strstr(buffer,actualKey)) {
					printf("\nMatched Pattern:%s\n",buffer);
					found = 1;
					break;
				}
			}
			fclose(fp);
		}
		if(!found) {
			printf("\nNo Matching Pattern Found\n");
		}
		return !found;
	} else{
		printf("\nUsage : %s <gesture.key> <dictionaryFile>\n");
		return -1;
	}	
}
