#include "check_words.h"



int main()
{
	if ((file = fopen("Text.txt", "r")) == NULL)
	{
		file_error("error opening program file");
		exit(1);
	}

	do
	{
		//next_token();
		parse();
		
	} while (current_token != EOF);

	fclose(file);
	return 0;
}


get_char()
{
	int length = 0;
	int j = 0;

	if ((ch = fgetc(file)) == EOF)
	{
		return EOF;
	}

	buffer[length++] = ch;
	buffer[length] = 0;

	//if (ch == '"')
	//{
	//
	//	ch = get_s(file); //Get next character and increment if character = newline

	//	for (; ; )
	//	{
	//		if (ch == '"') break;
	//		buffer[length++] = ch;

	//		ch = get_s(file);
	//	}
	//	buffer[length] = '\0';
	//	//current_token = createList(current_token, " ", SLITERAL, 0, buffer);
	//}

	if (number(ch)) { return NUMBER; }
	if (operators(ch)) { return OPERATOR; }
	if (seperator(ch)) { return SEPERATOR; }
	if (equalizer(ch)) { return EQUALIZER; }
	if (space(ch)) { return SPACE; }
	if (neli(ch)) { return NELI; }
	if (period(ch)) { return PERIOD; }
	if (comma(ch)) { return COMMA; }
	if (colon(ch)) { return COLON; }
	if (lparen(ch)) { return LPAREN; }
	if (rparen(ch)) { return RPAREN; }
	if (lbracket(ch)) { return LBRACKET; }
	if (rbracket(ch)) { return RBRACKET; }
	if (semicolon(ch)) { return SEMICOLON; }
	if (addition(ch)) { return ADDITION; }
	if (subtraction(ch)) { return SUBTRACTION; }
	if (multiplication(ch)) { return MULTIPLICATION; }
	if (division(ch)) { return DIVISION; }

	while ((ch = fgetc(file)) != EOF)
	{
		if (!letter(ch))
		{
			ungetc(ch, file);
			break;
		}
		buffer[length++] = ch;
	}
	buffer[length] = 0;
	return WORD;
}

next_token()
{
	current_token = get_char();

	line_num++;

	switch (current_token)
	{
	case WORD:				 current_token = check_word(buffer);                   break;
	case IDENT:              current_token = check_ident(buffer);                  break;
	case SPACE:               line_num--;                                          break;
	case NELI:                line_num--;                                          break;
	case NUMBER:                             print_token(current_token, buffer);   break;
	case STRAND:                             print_token(current_token, buffer);   break;
	case SEPERATOR:                          print_token(current_token, buffer);   break;
	case EQUALIZER:                          print_token(current_token, buffer);   break;
	case OPERATOR:                           print_token(current_token, buffer);   break;
	case PERIOD:                             print_token(current_token, buffer);   break;
	case COMMA:                              print_token(current_token, buffer);   break;
	case LPAREN:                             print_token(current_token, buffer);   break;
	case RPAREN:                             print_token(current_token, buffer);   break;
	case LBRACKET:                           print_token(current_token, buffer);   break;
	case RBRACKET:                           print_token(current_token, buffer);   break;
	case SEMICOLON:                          print_token(current_token, buffer);   break;
	case COLON:                              print_token(current_token, buffer);   break;
	case ADDITION:                           print_token(current_token, buffer);   break;
	case SUBTRACTION:                        print_token(current_token, buffer);   break;
	case MULTIPLICATION:                     print_token(current_token, buffer);   break;
	case DIVISION:                           print_token(current_token, buffer);   break;
	case INCREMENT:                          print_token(current_token, buffer);   break;
	case DECREMENT:                          print_token(current_token, buffer);   break;
	case POINTER:                            print_token(current_token, buffer);   break;
	default:                                                                       break;
	}
	return current_token;
}

print_token(token_type current_token, char* buffer)
{
	switch (current_token)
	{
	case OPERATOR:            printf(" %03d:   %s\t              operator\n", line_num, buffer);                           break;
	case SEPERATOR:           printf(" %03d:   %s\t              seperator\n", line_num, buffer);                          break;
	case NUMBER:              printf(" %03d:   %s\t              number\n", line_num, buffer);                             break;
	case STRAND:              printf(" %03d:   %s\t              strand\n", line_num, buffer);                             break;
	case EQUALIZER:           printf(" %03d:   %s\t              equalizer\n", line_num, buffer);                          break;
	case PERIOD:              printf(" %03d:   %s\t              period\n", line_num, buffer);                             break;
	case COMMA:               printf(" %03d:   %s\t              comma\n", line_num, buffer);                              break;
	case LPAREN:              printf(" %03d:   %s\t              lparen\n", line_num, buffer);                             break;
	case RPAREN:              printf(" %03d:   %s\t              rparen\n", line_num, buffer);                             break;
	case LBRACKET:            printf(" %03d:   %s\t              lbracket\n", line_num, buffer);                           break;
	case RBRACKET:            printf(" %03d:   %s\t              rbracket\n", line_num, buffer);                           break;
	case SEMICOLON:           printf(" %03d:   %s\t              semicolon\n", line_num, buffer);                          break;
	case COLON:               printf(" %03d:   %s\t              colon\n", line_num, buffer);                              break;

	case ADDITION:            printf(" %03d:   %s\t              addition\n", line_num, buffer);                           break;
	case SUBTRACTION:         printf(" %03d:   %s\t              subtraction\n", line_num, buffer);                        break;
	case MULTIPLICATION:      printf(" %03d:   %s\t              multiplication\n", line_num, buffer);                     break;
	case DIVISION:            printf(" %03d:   %s\t              division\n", line_num, buffer);                           break;

	case INCREMENT:           printf(" %03d:   %s%s\t            increment\n", line_num, buffer, buffer);                  break;
	case DECREMENT:           printf(" %03d:   %s%s\t            decrement\n", line_num, buffer, buffer);                  break;
	case POINTER:             printf(" %03d:   %s%s\t            pointer\n", line_num, buffer, buffer);                    break;

	default:                  lexical_error("unknown token in print_token function%d\n", current_token);                   break;
	}
}
