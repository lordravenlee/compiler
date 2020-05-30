#include "errors.h"


void match(token_type expected);
tree_node * parse(void);
tree_node * stmt_sequence(void);
tree_node * statement(void);
tree_node * check_stmt(void);
tree_node * expression(void);
tree_node * simple_expression(void);
tree_node * term(void);
tree_node * factor(void);
tree_node * new_statement(StmtKind kind);
tree_node * new_expression(ExpKind kind);
char * copy_string(char * s);

void match(token_type expected)
{
	if (current_token == expected)
	{
		current_token = next_token();
	}
	else
	{
		parser_error(" token not matching up");
		print_token(current_token, buffer);
	}
}

tree_node * parse(void)
{
	tree_node * i;
	current_token = next_token();
	i = stmt_sequence();

	if (current_token != EOF)
	{
		parser_error("code ends before file\n");
	}
	return i;
}

tree_node * stmt_sequence(void)
{
	tree_node * i = statement();
	tree_node * ii = i;

	while ((current_token != EOF) && (current_token != RBRACKET) && (current_token != ELSE) && (current_token != LBRACKET))
	{
		tree_node * iii;
		match(SEMICOLON);
		iii = statement();

		if (iii != NULL)
		{
			if (i == NULL) i = ii = iii;
			else /* now p cannot be NULL either */
			{
				ii->sibling = iii;
				ii = iii;
			}
		}
	}
	return i;
}

tree_node * statement(void)
{
	tree_node * i = NULL;
	switch (current_token)
	{
	case CHECK: i = check_stmt(); break;
		//case REPEAT: t = repeat_stmt(); break;
		//case ID: t = assign_stmt(); break;
		//case READ: t = read_stmt(); break;
		//case WRITE: t = write_stmt(); break;
	default: break;
	}
	return i;
}

tree_node * check_stmt(void)
{
	tree_node * i = new_statement(IfK);

	match(CHECK);

	if (i != NULL)
	{
		i->child[0] = expression();
	}
	match(LBRACKET);
	if (i != NULL)
	{
		i->child[1] = stmt_sequence();
	}
	if (current_token == ELSE)
	{
		match(ELSE);
		if (i != NULL)
		{
			i->child[2] = stmt_sequence();
		}
	}
	match(RBRACKET);
	return i;
}

tree_node * expression(void)
{
	tree_node * i = simple_expression();

	if ((current_token == LARROW) || (current_token == EQUALIZER))
	{
		tree_node * ii = new_expression(OpK);

		if (ii != NULL)
		{
			ii->child[0] = i;
			ii->attr.op = current_token;
			i = ii;
		}
		match(current_token);
		if (i != NULL)
		{
			i->child[1] = simple_expression();
		}
	}
	return i;
}

tree_node * simple_expression(void)
{
	tree_node * i = term();

	while ((current_token == ADDITION) || (current_token == SUBTRACTION))
	{
		tree_node * ii = new_expression(OpK);
		if (ii != NULL)
		{
			ii->child[0] = i;
			ii->attr.op = current_token;
			i = ii;
			match(current_token);
			i->child[1] = term();
		}
	}
	return i;
}

tree_node * term(void)
{
	tree_node * i = factor();

	while ((current_token == MULTIPLICATION) || (current_token == DIVISION))
	{
		tree_node * ii = new_expression(OpK);

		if (ii != NULL)
		{
			ii->child[0] = i;
			ii->attr.op = current_token;
			i = ii;
			match(current_token);
			ii->child[1] = factor();
		}
	}
	return i;
}

tree_node * factor(void)
{
	tree_node * i = NULL;

	switch (current_token)
	{
	case NUMBER:
		i = new_expression(ConstK);
		if ((i != NULL) && (current_token == NUMBER))
			i->attr.val = atoi(print_token(current_token, buffer));
		match(NUM);
		break;
	case IDENT:
		i = new_expression(IdK);
		if ((i != NULL) && (current_token == IDENT))
		{
			i->attr.name = copy_string(print_token(current_token, buffer));
		}
		match(IDENT);
		break;
	case LPAREN:
		match(LPAREN);
		i = expression();
		match(RPAREN);
		break;
	default: break;
	}
	return i;
}

tree_node * new_statement(StmtKind kind)
{
	tree_node * i = (tree_node *)malloc(sizeof(tree_node));
	int j;
	if (i == NULL)
	{
		printf("  out of memory error at line %d\n", line_num);
	}
	else
	{
		for (j = 0; j < MAXCHILDREN; j++)
		{
			i->child[j] = NULL;
		}
		i->sibling = NULL;
		i->nodekind = StmtK;
		i->kind.stmt = kind;
		i->lineno = line_num;
	}
	return i;
}


tree_node * new_expression(ExpKind kind)
{
	tree_node * i = (tree_node *)malloc(sizeof(tree_node));
	int j;
	if (i == NULL)
	{
		printf("  out of memory error at line %d\n", line_num);
	}
	else
	{
		for (j = 0; j < MAXCHILDREN; j++) i->child[j] = NULL;
		i->sibling = NULL;
		i->nodekind = ExpK;
		i->kind.exp = kind;
		i->lineno = line_num;
		i->type = hollow;
	}
	return i;
}


char * copy_string(char * s)
{
	int n;
	char * t;
	if (s == NULL) return NULL;
	n = strlen(s) + 1;
	t = malloc(n);
	if (t == NULL)
	{
		printf("  out of memory error at line %d\n", line_num);
	}
	else strcpy(t, s);
	return t;
}
