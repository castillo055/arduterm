#ifndef ARDUTERM_H
#define ARDUTERM_H

typedef struct {
	char cmd[100];
	int (*func)(int argc, char* argv[]);
} Command;

extern char* term_header;
extern char* term_prompt;
extern int commands_len;
extern Command commands[];

namespace arduterm{
	void printheader();

	int prompt();
};

#endif /* ARDUTERM_H */
