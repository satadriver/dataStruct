#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GetNext(char* p, int next[])
{
	int pLen = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < pLen - 1)
	{
		//p[k]��ʾǰ׺��p[j]��ʾ��׺  
		if (k == -1 || p[j] == p[k])
		{
			++k;
			++j;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}



int KmpSearch(char* s, char* p)
{
	int next[1024] = { 0 };
	GetNext(p, next);

	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	while (i < sLen && j < pLen)
	{
		//�����j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++      
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			//�����j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���S[i] != P[j]�������� i ���䣬j = next[j]      
			//next[j]��Ϊj����Ӧ��nextֵ        
			j = next[j];
		}
	}
	if (j == pLen)
		return i - j;
	else
		return -1;
}



int NEXT_1[256] = { 0 };


void get_nextval(char* t, int nextval[]) {
	int i = 1;
	nextval[1] = 0;
	int j = 0;
	while (i < t[0])
	{
		if (j == 0 || t[i] == t[j])
		{
			i++;
			j++;
			if (t[i] != t[j])
			{
				nextval[i] = j;
			}
			else {
				nextval[i] = nextval[j];
			}
		}
		else {
			j = nextval[j];
		}
	}
}

void get_next(char* t, int next[]) {
	int i = 1;
	NEXT_1[1] = 0;
	int j = 0;
	while (i < t[0]) {
		if (j == 0 || t[i] == t[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else {
			j = NEXT_1[j];
		}
	}
	return;
}



void get_next_str(char* t, int next[]) {
	int i = 0;
	NEXT_1[0] = 0;
	int j = 0;

	int tlen = strlen(t);

	while (i < tlen) {
		if (j == 0 || t[i] == t[j])
		{
			i++;
			j++;
			next[i] = j;
		}
		else {
			j = NEXT_1[j];
		}
	}
	return;
}


int IndexKMP_str(char* s, char* t, int pos) {
	int i = pos;
	int j = 0;

	int slen = strlen(s);
	int tlen = strlen(t);

	while (i <= slen && j <= tlen)
	{
		if (j == 0 || s[i] == t[j])
		{
			i++;
			j++;
		}
		else {
			j = NEXT_1[j];
		}
	}

	if (j > tlen)
	{
		return i - tlen;
	}

	return 0;
}



int IndexKMP(char* s, char* t, int pos) {
	int i = pos;
	int j = 1;
	while (i <= s[0] && j <= t[0])
	{
		if (j == 0 || s[i] == t[j])
		{
			i++;
			j++;
		}
		else {
			j = NEXT_1[j];
		}
	}

	if (j > t[0])
	{
		return i - t[0];
	}

	return 0;
}




void testkmp() {
	int result = 0;
	char* s = "assaasssas";
	char* p = "ssas";
// 	get_next_str(p, NEXT_1);
 	//result = IndexKMP_str(s, p, 0);
	result =  KmpSearch(s, p);
	printf("ok\r\n");
	return;

// 	char* s = "\x20hello asdfghasdfdgdadfsfdsfdadfdfffsd";
// 	char* p = "\x05""fsfds";
// 
// 	get_next(p, NEXT_1);
// 	//get_nextval(p, NEXT_1);
// 
// 	result = IndexKMP(s, p,1);
// 
// 	char* pos = strstr(s, p + 1);
// 	if (pos )
// 	{
// 		int hdr = pos - s;
// 		if (hdr == result)
// 		{
// 			printf("oo\r\n");
// 		}
// 	}
// 	return;
}
