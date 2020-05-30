#include "type.h"
#include <stdlib.h>


lexical_error(char * m)
{
	printf(" lexical_error: line_%03d:  %s \n", line_num, m);
	exit(1);
}

parser_error(char * m)
{
	printf(" parser_error: line_%03d:  %s \n", line_num, m);
	exit(1);
}

symbol_table_error(char * m)
{
	printf(" symbol_table_error: line_%03d:  %s \n", line_num, m);
	exit(1);
}


syntax_error(char * m)
{
	printf(" syntax_error: line_%03d:  %s \n", line_num, m);
	exit(1);
}

data_type_error(char * m)
{
	printf(" data_type_error: line_%03d:  %s \n", line_num, m);
	exit(1);
}

file_error(char * m)
{
	printf(" file_error: line_%03d:  %s \n", line_num, m);
	exit(1);
}
