#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>


typedef enum
{
	false, true,
}pare;

FILE *file;
char buffer[1000];
char ident_string[1000];

int ch;

int line_num = 0;
int level = 0;
int length = 0;


typedef enum
{
	SYSTEM_HEADER, SUB_HEADER, GLOBAL, LOCAL,  FUNCTION_HEADER, MANAGER, FILE_TYPE, DATA_TYPE, DATA_MODIFIER, DATA_TOOLS,
	TRANSLATE,
	HAVEN, IO,
	PUBLIC, PRIVATE, ELEM, OBJECT,
	MARK, HOLLOW, DECI, DECII, NUM,
	RETURN, CALL, ACT, KEYWORD,
	READ, WRITE,
	FILES,
	LOOP, SET, CHECK, ELSE, PARE, COMPARE, LIST, CONSTRUCT, LOG, BRIDGE,
	EXTERN, STATIC, REGISTER, SHORT, LONG, SIGNED, UNSIGNED, DONE,

	WORD, NOT_WORD, IDENT, NUMBER, DIGIT, LETTER, ERROR, UNKNOWN,

	ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, ADD, SUB, MULTI, DIVI, ASSIGNMENT,
	SPACE, NELI, TAB, SEPERATOR, OPERATOR, EQUALIZER, STRAND,
	OPEN_PAREN, CLOSE_PAREN, SEMICOLON, ASSIGN, EQUAL, LARROW, LPAREN, RPAREN, COMMA, PERIOD, LBRACKET, RBRACKET, COLON, INCREMENT, DECREMENT, POINTER, DECIMAL,
	ENFI, CONSTANT, PLACEHOLDER, FUNCTION, HASH, RARROW,

} token_type;
token_type current_token;

struct keywords
{
	char * str;
	token_type token;
};

struct keywords system_header[] = { { "system",SYSTEM_HEADER },{ "translate",SYSTEM_HEADER } };
struct keywords sub_header[] = { { "haven",SUB_HEADER},{ "io", SUB_HEADER } };
struct keywords manager_type[] = { { "manager",MANAGER },{ "public",PUBLIC },{ "private",PRIVATE },{ "elem",ELEM },{ "object",OBJECT } };
struct keywords data_type[] = { { "mark", MARK },{ "hollow", HOLLOW},{ "deci", DECI},{ "decii",  DECII},{ "num",NUM},{ "return", RETURN}, {"hold", PLACEHOLDER}, };
struct keywords function_type[] = { { "read",READ },{ "write",WRITE } };
struct keywords file_type[] = { { "file",FILES } };
struct keywords data_tools[] = { { "loop",LOOP },{ "set",SET },{ "check",CHECK },{ "else",ELSE },{ "pare",PARE },{ "compare",COMPARE },{ "list",LIST },{ "construct",CONSTRUCT },{ "log",LOG },{ "bridge",BRIDGE }, {"act", ACT},};
struct keywords data_modifier[] = { { "extern",EXTERN },{ "static",STATIC },{ "register",REGISTER },{ "short",SHORT },{ "long",LONG },{ "signed",SIGNED },{ "unsigned",UNSIGNED } };


extern get_char();
extern next_token();
extern print_token(token_type current_token, char * buffer);
extern check_word(char t[]);
extern check_ident(char s[]);


typedef enum { StmtK, ExpK } NodeKind;
typedef enum { IfK, RepeatK, AssignK, ReadK, WriteK } StmtKind;
typedef enum { OpK, ConstK, IdK } ExpKind;

/* ExpType is used for type checking */
typedef enum { hollow, num} ExpType; //void, int, bool

#define MAXCHILDREN 3

typedef struct treeNode
{
	struct treeNode * child[MAXCHILDREN];
	struct treeNode * sibling;
	int lineno;
	NodeKind nodekind;
	union { StmtKind stmt; ExpKind exp; } kind;
	union {
		token_type op;
		int val;
		char * name;
	} attr;
	ExpType type; /* for type checking of exps */
} tree_node;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int mixture(int ch)
{
	return (letter(ch) || number(ch));
}

int letter(int ch)
{
	return (((ch >= 'a') && (ch <= 'z')) || (ch >= 'A') && (ch <= 'Z') || (ch == '_'));
}

int number(int ch)
{
	return ((ch >= '0') && (ch <= '9'));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int operators(int ch)
{
	return (addition(ch) || subtraction(ch) || multiplication(ch) || division(ch) || percentage(ch));
}

int addition(int ch)
{
	return ((ch == '+'));
}

int subtraction(int ch)
{
	return ((ch == '-'));
}

int multiplication(int ch)
{
	return ((ch == '*'));
}

int division(int ch)
{
	return ((ch == '/'));
}

int percentage(int ch)
{
	return ((ch == '%'));
}

int equalizer(int ch)
{
	return ((ch == "<=") || (ch == ">=") || (ch == "==") || (ch == "!="));
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int seperator(int ch)
{
	return ((percentage(ch)) || (ch == '#') || (ch == '[') || (ch == ']') || (ch == '<') || (ch == '>') || (ch == ':'));
}

int block(int ch)
{
	return ((lbracket(ch)) && (rbracket(ch)));
}

int lbracket(int ch)
{
	return ((ch == '{'));
}

int rbracket(int ch)
{
	return ((ch == '}'));
}

int lengthen(int ch)
{
	return ((lparen(ch)) && (rparen(ch)));
}

int lparen(int ch)
{
	return ((ch == '('));
}

int rparen(int ch)
{
	return ((ch == ')'));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int larrow(int ch)
{
	return ((ch == '<'));
}

int rarrow(int ch)
{
	return ((ch == '>'));
}

int comma(int ch)
{
	return ((ch == ','));
}

int period(int ch)
{
	return ((ch == '.'));
}

int semicolon(int ch)
{
	return ((ch == ';'));
}

int colon(int ch)
{
	return ((ch == ':'));
}

int increment(int ch)
{
	return (ch == '+');
}

int decrement(int ch)
{
	return (ch == '-');
}
int hash(int ch)
{
	return(ch == '#');
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int pointer(int ch)
{
	return ((ch == '*'));
}

int strand(int ch)
{
	return ((ch == '\"'));
}

int comment(int ch)
{
	return ((ch == '/'));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int space(int ch)
{
	return ((ch == ' '));
}

int care(int ch)
{
	return ((ch == '\r'));
}

int neli(int ch)
{
	return ((ch == '\n'));
}

int tab(int ch)
{
	return ((ch == '\t'));
}

int nuller(int ch)
{
	return ((ch == '\0'));
}
