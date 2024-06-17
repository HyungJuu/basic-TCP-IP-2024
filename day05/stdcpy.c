#include <stdio.h>
#define BUF_SIZE 3	// 배열의 길이의 최도한으로 구성

int main(int argc, char *argv[])
{
	FILE * fp1;
	FILE * fp2;
	char buf[BUF_SIZE];

	fp1 = fopen("news.txt", "r");
	fp2 = fopen("cpt.txt", "w");

	while(fgets(buf, BUF_SIZE, fp1) != NULL)
		fputs(buf, fp2);

	fclose(fp1);
	fclose(fp2);
	return 0;
}
