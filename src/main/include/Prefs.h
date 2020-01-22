
#pragma once // only add this code once; saves space by removing redundancy

// Declare constants such as CAN IDs here 


/*====== MOTOR CONTROLLER IDS ======*/
#define TEST_STEER_ID 21 // Module 3 Turn
#define TEST_DRIVE_ID 22 // Module 3 Drive

// Module CAN IDs
// Module 1 Turn - 1
// Module 1 Drive - 2

// Module 2 Turn - 11
// Module 2 Drive - 12

// Module 3 Turn - 21
// Module 3 Drive - 22

// Module 4 Turn - 31
// Module 4 Drive - 32




/* ========== Joystick Ports ========= */
#define JOYSTICK_PORT 1


#define TICKS_STEERING 18.0 // roughly 18 "position" units per steering rotation

/* ====== ASCII ART ======= */
//   <====[-<('-'<)


#define bridge_host "10.23.58.26"
#define DEFAULT_PORT 1185
#define bridge_port DEFAULT_PORT
#define LIGHT_RING_CONTROLLER_ADDRESS 0x4