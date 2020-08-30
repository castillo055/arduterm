// Includes corresponding to ChibiOS
#include <ChRt.h>

// Auxiliary includes
#include "Arduino.h"
#include "src/arduterm.h"
#include <SPI.h>

char* term_header = "===== TEENSY TERMINAL =>\n";
char* term_prompt = "$_>";

static int echo(int argc, char* argv[]);
static int sayhello(int argc, char* argv[]);

int commands_len = 2;
Command commands[] = {
	{"echo" 	, echo 		},
	{"sayhello" 	, sayhello 	},
};

int echo(int argc, char* argv[]){
	for(int i = 0; i < argc; i++){
		Serial.print(argv[i]);
		Serial.print(" ");
	}
	Serial.println("");
	return 0;
}
int sayhello(int argc, char* argv[]){
	Serial.println("HELLO");
	return 0;
}

static THD_WORKING_AREA(waMEMTST, 200); // 64 byte stack

static THD_FUNCTION(MEMTST_TH, arg) {
	(void)arg;

	teensyterm::printheader();
	systime_t prev = chVTGetSystemTime(); // Current system time.
	while (!chThdShouldTerminateX()) {
		teensyterm::prompt();
		prev = chThdSleepUntilWindowed(prev, prev + 150);
	}
}

//==============================================================================
void chSetup() {

	Serial.begin(19200);
	pinMode(13, OUTPUT);
	while(!Serial){
		digitalWrite(13, HIGH);
	}
	digitalWrite(13, LOW);

	chThdCreateStatic(waMEMTST, sizeof(waMEMTST),
			NORMALPRIO + 1, MEMTST_TH, NULL);
}
//------------------------------------------------------------------------------

//========== BAD LANDS - Nothing to do from here on ============================
void setup() {
	// Initialize OS and then call chSetup.
	chBegin(chSetup);
	// chBegin() resets stacks and should never return.
	while (true) {}
}

void loop() { }
