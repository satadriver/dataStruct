#include <stdio.h>
#include <string.h>

int indexstr(char * s, char * t, int pos) {
	int sl = strlen(s);
	int tl = strlen(t);

	if (pos >= sl)
	{
		return 0;
	}

	int i = pos; 
	int j = 0;
	while (i < sl && j < tl) {
		if (s[i] == t[j])
		{
			i++;
			j++;
			if (j >= tl)
			{
				return i - j;
				//break;
			}
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}

	return 0;
}