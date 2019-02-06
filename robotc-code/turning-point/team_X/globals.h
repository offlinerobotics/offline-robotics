#ifndef GLOBALS
#define GLOBALS

//	motors.h
#define MAX_SPEED 127
#define REV_SPEED -127
#define MIN_SPEED 1
#define NO_SPEED 0

//	auto_functions.h

typedef enum AUTO_SELECTION {
	RED_FRONT,
	RED_BACK,
	BLUE_FRONT,
	BLUE_BACK,
} Autoselection;
Autoselection currentSelection = RED_FRONT; // Global Autonomous Selection

#endif /* GLOBALS */
