
#pragma once // only add this code once; saves space by removing redundancy

// Declare constants such as CAN IDs here 


/*====== MOTOR CONTROLLER IDS ======*/
#define FL_STEER_ID 1
#define FL_DRIVE_ID 2

#define FR_STEER_ID 11
#define FR_DRIVE_ID 12

#define BL_STEER_ID 21
#define BL_DRIVE_ID 22

#define BR_STEER_ID 31
#define BR_DRIVE_ID 32




/*
// Module CAN IDs FL, FR, BL, BR
FL:
 Module 1 Turn - 1
 Module 1 Drive - 2

FR:
 Module 2 Turn - 11
 Module 2 Drive - 12

BL:
 Module 3 Turn - 21
 Module 3 Drive - 22

BR:
 Module 4 Turn - 31
 Module 4 Drive - 32
*/




/* ========== Joystick Ports ========= */
#define JOYSTICK_PORT 1


#define TICKS_STEERING 18.0 // roughly 18 "position" units per steering rotation

/* ====== ASCII ART ======= */
//   <====[-<('-'<)
