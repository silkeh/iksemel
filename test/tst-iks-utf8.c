/* iksemel (XML parser for Jabber)
** Copyright (C) 2000-2003 Gurer Ozen
** This code is free software; you can redistribute it and/or
** modify it under the terms of GNU Lesser General Public License.
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "iksemel.h"

int main (int argc, char *argv[])
{
	setlocale (LC_ALL, "");
	static char xml[] = "<test>"
						"<text>Hello, &#x4e16;&#x754c;</text>"
						"<emoji>&#x1f4a9;</emoji>"
						"<invalid></invalid>"
						"<null></null>"
						"<nonprint>&#x01;&#x07;&#x0b;&#x7f;</nonprint>"
						"</test>";

	iks *x = iks_new ("test");
	iks_insert_cdata (iks_insert (x, "text"), "Hello, 世界", 13);
	iks_insert_cdata (iks_insert (x, "emoji"), "\U0001F4A9", 4);
	iks_insert_cdata (iks_insert (x, "invalid"), "\x80\x81", 2);
	iks_insert_cdata (iks_insert (x, "null"), "\0", 1);
	iks_insert_cdata (iks_insert (x, "nonprint"), "\x1\a\v\x7F", 4);

	char *t = iks_string (iks_stack (x), x);
	if(!t || strcmp(t, xml) != 0) {
		printf("Result:   %s\n", t);
		printf("Expected: %s\n", xml);
		return 1;
	}
	iks_delete(x);

	return 0;
}
