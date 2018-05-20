#include<stdio.h>
#include<string.h>
#include<stdbool.h>

char code[20][20];
int cc=0;
int leaders[20];
int lc=0;
struct 
{
	int start,end;
}block[10];
int bc=0;

void fromFile()
{
	system("COLOR F0");
	FILE *ptr=fopen("tac.txt","r");
	int j=0;
	char c;
	while(!feof(ptr))
	{
		fscanf(ptr,"%c",&c);
		if(c=='\n')
		{
			code[cc][j]=0;
			j=0;
			cc++;
		}
		else
		{
			code[cc][j++]=c;
		}
		
		
	}
	cc--;
	fclose(ptr);
	printf("Code is \n==========\n");
	int i;
	for(i=0;i<cc;i++)
	{
		printf("%s",code[i]);
		printf("\n");
	}
}

int hasGoto(int ln)
{
	int i=0;
	int n=strlen(code[ln]);
	for(;i<n-4;i++)
	{
		if(code[ln][i]=='g'&&code[ln][i+1]=='o'&&code[ln][i+2]=='t'&&code[ln][i+3]=='o')
		{
			return i;
		}
	}
	return -1;
}

bool isInLeader(int ln)
{
	int i;
	for(i=0;i<lc;i++)
	{
		if(leaders[i]==ln)
			return true;
	}
	return false;
}

int findTarget(int ln)
{

	int i=hasGoto(ln);
	int t=0;
	for(i=i+5;i<strlen(code[ln]);i++)
	{
		t=t*10+code[ln][i]-48;
	}
	return t;
}
	

void findLeaders()
{
	int i,j;
	leaders[cc]=0;
	for(i=0;i<cc;i++)
	{
		if(hasGoto(i)>=0)
		{
			if(!isInLeader(i+1)&&i<cc-1)
			{
					leaders[lc++]=i+1;
			}
			if(!isInLeader(findTarget(i)))
			{
				leaders[lc++]=findTarget(i);
			}
		}
	}
	//sort leaders
	for(i=0;i<lc-1;i++)
	{
		for(j=i+1;j<lc;j++)
		{
			if(leaders[i]>leaders[j])
			{
				int t=leaders[i];
				leaders[i]=leaders[j];
				leaders[j]=t;
			}
		}
	}
	printf("Leaders are \n==========\n");
	for(i=0;i<lc;i++)
		printf("%d ",leaders[i]);
	printf("\n");
}

void findBlocks()
{
	int i;
	for(i=0;i<lc-1;i++)
	{
		block[bc].start=leaders[i];
		block[bc++].end=leaders[i+1]-1;
	}
	block[bc].start=leaders[lc-1];
	block[bc++].end=cc-1;
	printf("Blocks are \n==========\n");
	for(i=0;i<bc;i++)
	{
		printf("%d-%d\n",block[i].start,block[i].end);
	}
	printf("\n");
}
	

int main()
{
	fromFile();
	findLeaders();
	findBlocks();
	return 0;
}
	
