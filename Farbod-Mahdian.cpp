/*
	Farbod Mahdian
	135438190
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void clear(char str[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		str[i] = NULL;
	}
}

int main()
{
	FILE* data_file, * out_put; //Input and output file

	char ch;
	char w[1000][20] = {};//All of the WRODS
	char ptn[17] = { '.', ',', ';', ':', '!', '?', '-', '(', ')', '{', '}', '[', '}', '\'', '\"', '—', '_' };//Punctuations
	char mover[20] = {}; //A temprary variable for sorting the repeated WORDS
	char w_temp[1000][20] = {}; //Only uniq WORDS (non-similars)

	int chars = 0; //Number of CHARS
	int i;
	int x = 0, y = 0, w_num = 0, l = 0; //w_num -> number of WRODS & l -> number of LINES
	int flag_ptn = 0;
	int j, a = 0;
	int w_number[1000] = { 0 }, temp; //How many times every each of WORDS are repeated

	data_file = fopen("C:\\Users\\NFARMAD\\Desktop\\DATA.txt", "r"); //file open

	//Reading the FILE char by char
	while ((ch = getc(data_file)) != EOF)
	{
		if (ch != ' ' && ch != '\t' && ch != '\n')
		{
			for (i = 0; i < 17; i++)
			{
				if (ch == ptn[i])//Removing punctuations
				{
					flag_ptn = 1;
					break;
				}
			}

			if (flag_ptn == 0)
			{
				//Make the CHARs lowercase before storing it
				w[x][y] = tolower(ch);
				y++;
			}
			else
			{
				if (y != 0)
				{
					y = 0;
					x++;
					//Counting WORDS
					w_num++;
				}
				flag_ptn = 0;
			}
		}
		else
		{
			if (ch == '\n')
			{
				//Counting LINES
				l++;
			}
			if (y != 0)
			{
				y = 0;
				x++;
				//Counting WORDS
				w_num++;
			}
		}
	}

	//Checking for the last WORD in the end of the file
	if (y != 0)
	{
		y = 0;
		x++;
		//Counting WORDS
		w_num++;
	}

	//Counting CHARS
	for (y = 0; y < w_num; y++)
		chars += strlen(w[y]);

	//Finding the repeated WORDS and counting them
	for (i = 0; i < w_num; i++)
	{
		temp = 1;
		if (w[i][0] != NULL)
		{
			for (j = i + 1; j < w_num; j++)
			{
				if (strcmp(w[i], w[j]) == 0)
				{
					temp++;
					clear(w[j], strlen(w[j]));
				}
			}
			strcpy(w_temp[a], w[i]);
			w_number[a] = temp;
			a++;
		}
	}

	//Sorting the repeated WRODS in order to find the 10 WRODS with the most repetitions
	for (i = 0; i < w_num; i++)
	{
		for (j = i + 1; j < w_num; j++)
		{
			if (w_number[i] < w_number[j])
			{
				temp = w_number[i];
				w_number[i] = w_number[j];
				w_number[j] = temp;

				strcpy(mover, w_temp[i]);
				strcpy(w_temp[i], w_temp[j]);
				strcpy(w_temp[j], mover);
			}
		}
	}

	//Showing LINES, CHARS and WORDS
	printf("Lines = %d\n", l + 1);//One more than the number of ENTERS will be our LINES
	printf("Chars = %d\n", chars);
	printf("Words = %d\n\n", w_num);
	printf("Different words = %d\n\n", a);

	//Showing 10 WORDS that are repeated the most
	for (y = 0; y < 10; y++)
	{
		if (w_number[y] != 0)
			printf("<%d> word: %s -> Repeated: %d\n", y + 1, w_temp[y], w_number[y]);
	}

	fclose(data_file);

	//Opening the output file
	out_put = fopen("C:\\Users\\NFARMAD\\Desktop\\Farbod-output.txt", "w");

	//Wrtite the number of LINES, CHARS and WORDS in the output file
	fprintf(out_put, "Lines = %d\n", l + 1);
	fprintf(out_put, "Chars = %d\n", chars);
	fprintf(out_put, "Words = %d\n", w_num);
	fprintf(out_put, "\nDifferent words = %d\n\n", a);

	//Wrtite the repeated WORDS and the number of their repetitions in the output file
	for (y = 0; y < 10; y++)
	{
		if (w_number[y] != 0)
			fprintf(out_put, "<%d> word: %s -> Repeated: %d\n", y + 1, w_temp[y], w_number[y]);
	}

	fclose(out_put);

	getchar();

	return 0;
}