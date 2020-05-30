#include"parse.h"


check_word(char t[])
{
	int i;

	for (i = 0; i < 2; i++)
	{
		if (strcmp(system_header[i].str, t) == 0)
		{
			printf(" %03d:   %s\t              system_header\n", line_num, t);
			current_token = system_header[i].token;
			return SYSTEM_HEADER;
		}
	}
	for (i = 0; i < 2; i++)
	{
		if (strcmp(t, sub_header[i].str) == 0)
		{
			printf(" %03d:   %s\t              sub_header\n", line_num, t);
			current_token = sub_header[i].token;
			return SUB_HEADER;
		}
	}
	for (i = 0; i < 5; i++)
	{
		if (strcmp(t, manager_type[i].str) == 0)
		{
			printf(" %03d:   %s\t              manager_type\n", line_num, t);
			current_token = manager_type[i].token;
			return MANAGER;
		}
	}
	for (i = 0; i < 2; i++)
	{
		if (strcmp(t, function_type[i].str) == 0)
		{
			printf(" %03d:   %s\t              function_type\n", line_num, t);
			current_token = function_type[i].token;
			return FUNCTION;
		}
	}
	for (i = 0; i < 1; i++)
	{
		if (strcmp(t, file_type[i].str) == 0)
		{
			printf(" %03d:   %s\t              file_type\n", line_num, t);
			current_token = file_type[i].token;
			return FILE_TYPE;
		}
	}
	for (i = 0; i < 6; i++)
	{

		if (strcmp(t, data_type[i].str) == 0)
		{
			printf(" %03d:   %s\t              data_type\n", line_num, t);
			current_token = data_type[i].token;
			return DATA_TYPE;
		}
	}
	for (i = 0; i < 10; i++)
	{
		if (strcmp(t, data_tools[i].str) == 0)
		{
			printf(" %03d:   %s\t              data_tool\n", line_num, t);
			current_token = data_tools[i].token;
			return DATA_TOOLS;
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (strcmp(t, data_modifier[i].str) == 0)
		{
			printf(" %03d:   %s\t              data_modifiers\n", line_num, t);
			current_token = data_modifier[i].token;
			return DATA_MODIFIER;
		}
	}
	check_ident(buffer);
	return;
}

check_ident(char s[])
{
	strcpy_s(ident_string, sizeof(ident_string), s);
	printf(" %03d:   %s\t              identifier\n", line_num, ident_string);
	return IDENT;
}
