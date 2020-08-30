#include "Arduino.h"
#include "arduterm.h"
#include <ChRt.h>

void arduterm::printheader(){
	Serial.println("[Shell version: v1.0]");
	Serial.println(term_header);
}

int arduterm::prompt(){
	Serial.print(term_prompt);

	//== Read commands from serial
	char cmd[100];
	while(Serial.available() == 0) chThdSleepMilliseconds(10);
	chThdSleepMilliseconds(100);
	int len = Serial.available();
	char input[len];
	int i = 0;
	while(Serial.available() > 0){
		char c = Serial.read();
		if(c == '\n') continue;
		input[i++] = c;
	}

	input[len] = NULL;
	Serial.println(input);

	//== Parse arguments
	int argc = 0;
	for(int i = 0; i < len; i++){
		if(input[i] == ' ') argc++;
	}
	char* argv[argc];
	if(argc == 0){
		for(int i = 0; i < len; i++){
			cmd[i] = input[i];
			cmd[i+1] = NULL;
		}
	}else{
		int i;
		for(i=0; i < len; i++){
			if(input[i] == ' ') break;
			cmd[i] = input[i];
			cmd[i+1] = NULL;
		}
		i++;

		for(int k = 0; k < argc; k++){
			int j = 0;
			while(i < len){
				if(input[i] == ' ') break;
				argv[k][j] = input[i];
				argv[k][j+1] = NULL;
				i++; j++;
			}
			i++;
		}
	}

	for(int i = 0; i < commands_len; i++){
		if(strcmp(cmd, commands[i].cmd) == 0){
			return commands[i].func(argc, argv);
		}
	}
}
