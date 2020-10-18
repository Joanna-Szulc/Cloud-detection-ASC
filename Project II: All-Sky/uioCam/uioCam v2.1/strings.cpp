
/*
**
** #######################################################################
** #                                                                     #
** #                    A C D _ S T R I N G S . C                        #
** #                                                                     #
** #         This file contains string functions                         #
** #                                                                     #
** #######################################################################
**
**
**
*/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* --------------------------------------------------------------------- */

/* MyAtoi(txt)
*
* This version of atoi also includes hex numbers
*
*/

int MyAtoi(char *txt)
{
	int retval = 0;
	int hex = 0;

	if ((int)strlen(txt) > 2)
	{
		if ((strncmp(txt, "0x", 2) == 0) || (strncmp(txt, "0X", 2) == 0))
		{
			hex = 1;
		}
	}

	if (hex)
	{
		sscanf_s(txt, "%x", &retval);
	}
	else
	{
		retval = atoi(txt);
	}

	return(retval);
}

/* ------------------------------------------------------------------------ */

/*
#FN Function name: Get2DigitNumber

#FD return a 2 digit number from a string

#FID Interface:
#FI c1 - input first character
#FI c2 - input second character

#FR returns 'c1'*10+'c2'
*/

int Get2DigitNumber(char c1, char c2)
{
	return(10 * (c1 - '0') + c2 - '0');
}

/* ------------------------------------------------------------------------ */

/*
#FN Function name: MtblDigit

#FD extended isdigit to handle negative  numbers

#FID Interface:
#FI d - input character

#FR returns 1 if decimal-digit character or '-'
#FR else it returns 0
*/

int MtblDigit(int d)
{
	if (isdigit(d) || (d == '-')) return(1);
	else                          return(0);
}


/* ------------------------------------------------------------------------ */

/*
#FN Function name: HtoI

#FD Calculate integer value of a hexadecimal string

#FC Constraints:

#FID Interface:
#FI string - char string[] is in the format:
#FI          0x#..#   0X#..#  or #..#
#FI          # is a hexadecimal number ('0' ... '9' , 'A' ... 'F' or 'a' ... 'f')

#FR returns integer value of the hexadecimal string
*/


int HtoI(char *string)
{
	int k;
	int s;
	int d;
	int retval;

	retval = 0;

	if ((string[1] == 'x') || (string[1] == 'X'))
		s = 2;
	else
		s = 0;

	for (k = s; k < (int)strlen(string); k++)
	{
		d = string[k] - 48;   /* '0' */
		if (d > 9)  d -= 7;   /* 'A' */
		if (d > 15) d -= 32;  /* 'a' */

		if ((d < 0) || (d > 15)) continue;  /* silent correction */

		retval = (retval << 4) + d;
	}
	return(retval);
}


/* ------------------------------------------------------------------------- */


/*
#FN Function name: BtoI

#FD Calculate the integer value of a bit string

#FC Constraints:

#FID Interface:
#FI string - string is in the format # ... #
#FI          where '#' is '0' or '1'

#FR returns integer value of the hexadecimal string
*/


int BtoI(char *string)
{
	int d;
	int k;
	int retval;

	retval = 0;

	for (k = 0; k < (int)strlen(string); k++)
	{
		d = string[k] - 48;   /* '0' */

		if ((d < 0) || (d > 1)) continue;  /* silent correction */

		retval = (retval << 1) + d;
	}
	return(retval);
}

/* ------------------------------------------------------------------------- */

/*
#FN Function name: ItoB

#FD This function returns the 8 character bitstring of an integer value
#FD Example
#FD        int d = 3;
#FD        printf("%s\n",ItoB(d)");
#FD        Printed string is: "0000 0011"

#FC Constraints:
#FC The function works only in the range 0 to 255

#FID Interface:
#FI val - input value ,   0 <= val < 256

#FR This function returns the 8 character bitstring
*/

char *ItoB(int val)
{
	static char retstring[10];
	int b;
	int k;

	b = 0x80;
	strcpy_s(retstring, 8, "");
	for (k = 7; k >= 0; k--)
	{
		if (val & b) strcat_s(retstring, 8, "1");
		else         strcat_s(retstring, 8, "0");
		b /= 2;
		if (k == 4) strcat_s(retstring, 8, " ");
	}
	return(retstring);
}


/* ------------------------------------------------------------------------- */

/*
#FN Function name: StrMatch

#FD compare two strings

#FID Interface:
#FI str1 - first string to compare
#FI str2 - second string to compare

#FR True if char str1[] is equal to char str2[], else False
#FR If one of these strings does not exist the function returns False
*/


int StrMatch(char *str1, char *str2)
{
	if (!str1 || !str2) return(1);

	if (strcmp(str1, str2) == 0)
		return(1);
	else
		return(0);
}

/* ------------------------------------------------------------------------- */

/*
#FN Function name: StrPreFillSpace

#FD This function fill some space charcters in front of the
#FD source string. The minimum length of the returned string
#FD is len charcters. If the length of the source string is equal
#FD or greater than len the source string is returned.

#FC Constraints:
#FC Maximum number of characters returned is 256

#FID Interface:
#FI source   - source string
#FI len      - minimum length of returned string

#FR Return selected string from char source[]
*/

char *StrPreFillSpace(char *source, int len)
{
	static char retstring[257];
	int k;
	int j;
	int source_len;

	source_len = strlen(source);

	if (source_len >= len) return(source); /* return original string */

	j = 0;
	strcpy_s(retstring, 256, "");
	for (k = 0; k < len; k++)
	{
		strcat_s(retstring, 256, " ");
		if ((len - source_len) <= k)
		{
			retstring[k] = source[j];
			j++;
			if (j > 256) break;
		}
	}

	return(retstring);
}

/* ------------------------------------------------------------------------- */

/*
#FN Function name: StrCopyN

#FD This function returns no number of characters from char source[] .
#FD The function starts to copy at charcter number startpos

#FC Constraints:
#FC Maximum number of characters returned is 256

#FID Interface:
#FI source   - source string
#FI startpos - start character in source
#FI no       - number of characters to copy

#FR Return selected string from char source[]
*/


char *StrCopyN(char *source, int startpos, int no)
{
	static char retstring[257];
	int k;
	int len;
	int source_len;

	len = 0;
	source_len = strlen(source);
	strcpy_s(retstring, 256, "");

	if ((source_len == 0) || (startpos >= source_len)) return(retstring);

	for (k = startpos; k < source_len; k++)
	{
		strcat_s(retstring, 256, " ");
		retstring[k - startpos] = source[k];
		len++;
		if (len >= no) break;
		if (len > 255) break;
	}

	return(retstring);
}

/* ------------------------------------------------------------------------- */

/*
#FN Function name: SubStringN

#FD The function checks if the char sub[] is in char source[]
#FD The search starts at character number startpos in source[].
#FD The first character position in source[] is 0
#FD Example: SubStringN("DEF","ABCDEFG",0); returns 3

#FC Constraints:
#FC The maximum length of the source string is 1024 characters.

#FID Interface:
#FI sub      - char sub[] , string to search for
#FI source   - char source[], string to search into
#FI startpos - start position in source

#FR if sub[] is in source[] the function returns the position in
#FR char source[] of sub[0]
#FR if sub[] is in not in source[] the function returns
#FR a negative number
*/


int SubStringN(char *sub, char *source, int startpos)
{
	int len;
	char *cp;

	len = strlen(source);
	/* start position out of range */
	if (startpos < 0 || startpos >= len) return (-2);

	cp = strstr(source + startpos, sub);
	if (!cp) return -1;

	return cp - source;
}

/* ------------------------------------------------------------------------- */

/*
#FN Function name: WordAfterN

#FD This function return the word after char string[] in char source[].
#FD The search starts at character number pos in source[].
#FD The first character position in source[] is 0.

#FD Example:                       0123456789012345678901234567
#FD           char source[] is:   "This test is a test you know"
#FD           char string[] is:   "test"
#FD           pos = 12;
#FD           WordAfterN(string,source,&pos)
#FD           returns "you" and pos is set to 20

#FC Constraints:
#FC The maximum length of returned string is 255 characters.

#FID Interface:
#FI string - char string[] , string to search for
#FI source - char source[], string to search into
#FI pos    - start position in source
#FO pos    - The value returned in int *pos is the start position of
#FO          the word after char string[] in char source[]
#FR This function return the word after char string[] in char source[].
*/


char *WordAfterN(char *string, char *source, int *pos)
{
	int k;
	int len;
	int startpos;
	char *cp;
	char *word;
	static char retstr[256];

	startpos = *pos;
	*pos = -1;
	*retstr = '\0';

	k = SubStringN(string, source, startpos); /* negative if no match */
	if (k < 0) return retstr;

	for (cp = source + k; *cp && *cp > ' '; cp++); /* skip "FREQ:" */
	for (; *cp && *cp <= ' '; cp++); /* blanks after "FREQ:" */
	if (!*cp) return retstr;
	word = cp;

	len = word - source;
	if (!len) return retstr;
	*pos = word - source; /* start position of the word after "FREQ:" */

	for (cp = word; *cp && *cp > ' '; cp++);
	len = cp - word;
	if (!len) return retstr;

	strncpy_s(retstr, 255, word, len);
	retstr[len] = '\0';

	return(retstr);
}

/* ------------------------------------------------------------------------- */

/*
#FN Function name: FirstWord

#FD This function return the first word in char source[].
#FD This function skips ' ' and '\t' in the start of char source[].

#FC Constraints:
#FC The maximum length of the returned string is 255 characters.

#FID Interface:
#FI  source   - source string

#FR This function return the first word in char source[].
*/


char *FirstWord(char *source)
{
	int len;
	char *cp;
	char *word;
	static char retstr[257];

	*retstr = '\0';

	for (cp = source; *cp && *cp <= ' '; cp++); /* skip leding blanks */
	if (!*cp) return retstr;
	word = cp;

	for (cp = word; *cp && *cp > ' '; cp++);
	len = cp - word;
	if (!len) return retstr;

	strncpy_s(retstr, 256, word, len);
	retstr[len] = '\0';

	return(retstr);
}

/* ------------------------------------------------------------------------- */


/*
#FN Function name: LineAfterN

#FD This function return the text after char string[] in char source[].
#FD The search starts at character number pos in source[].
#FD The first character position in source[] is 0.

#FD Example:                       0123456789012345678901234567
#FD           char source[] is:   "This test is a test you know  "
#FD           char string[] is:   "test"
#FD           pos = 12;
#FD           LineAfterN(string,source,&pos)
#FD           returns "you know  " and pos is set to 20
#FD           Linefeed at end of line is removed.

#FC Constraints:
#FC The maximum length of returned string is 255 characters.

#FID Interface:
#FI string - char string[] , string to search for
#FI source - char source[], string to search into
#FI pos    - start position in source
#FO pos    - The value returned in int *pos is the start position of
#FO          the word after char string[] in char source[]
#FR This function return the text after char string[] in char source[].
*/


char *LineAfterN(char *string, char *source, int *pos)
{

	int k;
	int len;
	int startpos;
	char *cp;
	char *words;
	static char retstr[256];

	startpos = *pos;
	*pos = -1;
	*retstr = '\0';

	k = SubStringN(string, source, startpos); /* negative if no match */
	if (k < 0) return retstr;

	for (cp = source + k; *cp && *cp > ' '; cp++); /* skip "FREQ:" */
	for (; *cp && *cp <= ' '; cp++); /* blanks after "FREQ:" */
	if (!*cp) return retstr;
	words = cp;

	len = words - source;
	if (!len) return retstr;
	*pos = words - source; /* start position of the words after "FREQ:" */

	for (cp = words; *cp && *cp >= ' '; cp++);
	len = cp - words;
	if (!len) return retstr;

	strncpy_s(retstr, words, len);
	retstr[len] = '\0';

	return(retstr);

}

/* ------------------------------------------------------------------------- */

