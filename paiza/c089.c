#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int col = 0;
	int row = 0;

	char str[1000];
	char *p = NULL;
	int i, j;
	int sum = 0;

	fgets(str, sizeof(str), stdin);
	p = str;
	while (*p != '\n')
	{
		if (*p == ' ')
		{
			*p = '\0';
			row = atoi(str);
			p++;
			col = atoi(p);
			break;
		}
		p++;
	}
	char **ret = (char **)malloc(sizeof(char *) * row);
	for (i = 0; i < row; i++)
	{
		ret[i] = (char *)malloc(sizeof(char) * (col + 1));
		fgets(ret[i], sizeof(ret[i]), stdin);
	}

	for (i = 0; i < row; i++)
	{
		char *score = (char *)malloc(sizeof(char) * (col * 3 + col - 1 + 1));
		char *p1 = NULL;
		char *p2 = NULL;
		fgets(score, sizeof(score), stdin);
		p1 = score;
		p2 = score;
		for (j = 0; j < col; j++)
		{
			int num = 0;
			while ((*p2 != ' ') && (*p2 != '\0'))
			{
				p2++;
			}
			*p2 = '\0';
			num = atoi(p1);
			p2++;
			p1 = p2;
			if (ret[i][j] == 'o')
			{
				sum += num;
			}
		}
	}

	printf("%d", sum);
	return 0;
}