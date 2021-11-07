#include <stddef.h>  //Size_t
#include <stdlib.h>  //Calloc

void swap_bytes(char *byteX, char *byteY)
{
	if((byteX != NULL) && (byteY != NULL))
	{
		char temp;
		temp   = *byteX;
		*byteX = *byteY;
		*byteY = temp;
	}
}

/*
 *  The strlen() function calculates the length of the string s, 
 *  excluding the terminating null byte ('\0').
 */
size_t Strlen(const char *str)
{
	size_t count = 0;
	if(str != NULL)
	{
		for(count = 0; str[count] != '\0'; count++)
		{
			;
		}
	}
	return count;
}

void Strrev(char *str)
{
	if(str != NULL)
	{
		int i, j = Strlen(str) - 1;
		for(i=0; (j > i) && (str[i] != '\0'); j--, i++ )
		{
			swap_bytes(str + i, str + j);
		}
	}
}

void Strrev2(const char *src, char *tar)
{
	if((src != NULL) && (tar != NULL))
	{
		int index, n = 0, len = Strlen(src);
		for(index = len - 1; index >= 0; index-- )
		{
			tar[n++] = src[index];
		}
		tar[len] = '\0';
	}
}

void Strcpy(const char *src, char *tar)
{
	if((src != NULL) && (tar != NULL))
	{
		int index = 0, len = Strlen(src);
		for(index = 0; index <= len; index++ )
		{
			tar[index] = src[index];
		}
	}
}

void Strncpy(const char *src, char *tar, size_t n)
{
	if((src != NULL) && (tar != NULL))
	{
		int index = 0, len = Strlen(src);
		len = (len < n) ? len : n;
		
		for(index = 0; index < len; index++ )
		{
			tar[index] = src[index];
		}
		tar[index] = '\0';
	}
}

char* Strcat(char *tar, char *src)
{
	if((src != NULL) && (tar != NULL))
	{
		int index;
		int len = Strlen(tar);
		for(index = 0; src[index] != '\0' ; index++)
		{
			tar[len + index] = src[index];
		}
		tar[len + index] = '\0';
	}
	return tar;
}

char* Strncat(char *tar, char *src, size_t n)
{
	if((src != NULL) && (tar != NULL))
	{
		int index;
		int len = Strlen(tar);
		for(index = 0; (n > index) && (src[index] != '\0') ; index++)
		{
			tar[len + index] = src[index];
		}
		tar[len + index] = '\0';
	}
	return tar;
}

char* Strchr(char *src, int ch)
{
	char* ptr = NULL;
	if(src != NULL)
	{
		for(int index = 0; index < Strlen(src); index++)
		{
			if(src[index] == ch)
			{
				ptr = &src[index];
				break;
			}
		}
	}
	return ptr;
}

char* Strrchr(char *src, int ch)
{
	char* ptr = NULL;
	if(src != NULL)
	{
		for(int index = 0; index < Strlen(src); index++)
		{
			if(src[index] == ch)
			{
				ptr = &src[index];
			}
		}
	}
	return ptr;
}

char* Strstr(const char *haystack,const char *needle)
{
	int i, j;
	for(i=0; haystack[i]; i++)
	{
		if(haystack[i] == needle[0])
		{
			for(j=0; needle[j]; j++)
			{
				if(haystack[i+j] != needle[j])
					break;
			}
			if(needle[j]=='\0')
				return (char*)(haystack+i);
		}
	}
	return NULL;
}

// Recursive function to implement `strstr()` function
const char* Strstr2(const char* X, const char* Y)
{
    if (*Y == '\0')
	{
        return X;
    }
 
    for (int i = 0; i < Strlen(X); i++)
    {
        if (*(X + i) == *Y)
        {
            char* ptr = Strstr2(X + i + 1, Y + 1);
            return (ptr) ? ptr - 1 : NULL;
        }
    }
 
    return NULL;
}

char* Strrstr(const char *haystack,const char *needle)
{
	int i, j;
	char* str = NULL;
	for(i=0; i < Strlen(haystack); i++)
	{
		if(haystack[i] == needle[0])
		{
			for(j=0; needle[j]; j++)
			{
				if(haystack[i+j] != needle[j]) break;
			}
			if(needle[j] == '\0')
				str = (char*)(haystack+i);
		}
	}
	return str;
}

int Strcmp(const char *s1, const char *s2)
{
	while(*s1 && *s2)
	{
		if(*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	
	if(*s1 == *s2)
	{
		return 0;
	}
	else if(*s1 > *s2)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void Memcpy(void *dest,const void *src, size_t n)
{
	if((src != NULL) && (dest != NULL) && (n > 0))
	{	
		int index = 0, len = Strlen(src);
		len = (len < n) ? len : n;
		
		for(index = 0; index < len; index++ )
		{
			*((char *) (dest + index)) = *((char*) src + index);
		}
		*((char *)dest+index) = '\0';	
	}
}

/*
 * memmove() is similar to memcpy() as it also copies data from a source to destination.
 * memcpy() leads to problems when source and destination addresses overlap 
 * as memcpy() simply copies data one by one from one location to another.
 */
void Memmove(void *dest,const void *src, size_t n)
{
	if((src != NULL) && (dest != NULL) && (n > 0))
	{
		// Typecast src and dest addresses to (char *)
		char *csrc = (char *)src;
		char *cdest = (char *)dest;
		
		// Create a temporary array to hold data of src
		char *temp = calloc(1, n);
		
		// Copy data from csrc[] to temp[]
		for (int i=0; i<n; i++)
			temp[i] = csrc[i];
		
		// Copy data from temp[] to cdest[]
		for (int i=0; i<n; i++)
			cdest[i] = temp[i];

		free(temp);
	}
}

void* Memset(void *s,int c,size_t n)
{
	while(n--)
	{
		*((char*)s) = c;
		((char*)s++);
	}
	return s;
}	

#include <stdio.h>
void main(void)
{
	char str0[100] = "!";
	char str1[100] = "";
	char str2[100] = "I Love My India.";
	char str3[100] = "India Is Great";	

	//---> strlen
	//printf("String Length : %ld\n", Strlen(str1));
	
	//---> Strrev, strrev2
	//Strrev(str2);
	//Strrev2(str2, str1);
	//printf("Reverse String : %s, %s\n", str2, str1);
	
	//---> strcpy
	//Strcpy(str3, str1);
	//printf("Copy String : %s\n", str1);
	
	//---> strncpy
	//Strncpy(str2, str1, 6);
	//printf("Copy n bytes String : %s\n", str1);
	
	//--> Memmove
	//Memmove(str2+7, str2, strlen(str2)+1);
	//printf("Memmove String : %s\n", str2);
	
	//--> Strcat, Strncat
	//printf("Strcat : %s\n", Strcat(str2, str3));
	//printf("Strcat : %s\n", Strncat(str2, str3, 4));
	
	//--> Strchr, Strrchr
	//printf("Strchr : %s\n", Strchr(str3, ' '));
	
	//--> Strstr, Strrstr
	//printf("Strstr : %s\n", Strstr("India Is India Great", "India"));
	//printf("Strrstr : %s\n", Strrstr("India Is India Great", "India"));
		
	//--> Strcmp
	//if(Strcmp("India", "India")==0)
	//	printf("Equal\n");
	//else
	//	printf("Not Equal\n");
}