
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
#define JOYSTICK_DEADZONE 0.15

#define BUTTON_BOX 3
#define XBOX_CONTROLLER 5

#define TICKS_STEERING 18.0 // roughly 18 "position" units per steering rotation

/* ====== ASCII ART ======= */
//   <====[-<('-'<)

#define LIGHT_RING_CONTROLLER_ADDRESS 0x4
/* ============ GEAR RATIOS ======== */
// drive motor -> wheel = 10:1 (10 drive rotations for one wheel rotation)
// radius of wheel = 2 inches
// circumfrence = 4 Pi inches
// 10 ticks = 4 Pi inches
#define INCHES_PER_TICK (2.0 / 5) * M_PI // inches

/* ============= AUTO VALUES 4 Jason yoyoyo =========== */
#define ARBITRARY_DIST_BACKWARDS 30.0 // inches
#define TOF_TO_WALL 27.0 // inches
#define LINE_TO_BALL_FAR 192.66 // inches


#define VOLTS_MAX 1.783 //CHANGE PLZ CHANGE PLA WHEN WE KNOW
#define VOLTS_MIN 2.67 //CHANGE PLZ CHANGE PLA WHEN WE KNOW
#define ANGLE_MAX 90
#define ANGLE_MIN 24


#define AUTO_START_BALL_NUM 3 // KNOWN FACT ITS WHAT WE START WITH!!!!!

#define ARM_DEFAULT_POSITION 90 //degrees???? CHANGE WHEN ACTUALLY FOUND
#define AUTO_ARM_FINAL_POS 23 //degrees???? CHANGE WHEN ACTUALLY FOUND
#define AUTO_SHOOT_VELOCITY 400 // RPM, change after PID tuned and Tested
#define AUTO_FEED_VAL 600 // wowowowow



/*----------------------------------------------*/

#define SHOOT_VOLTS .7
#define COLLECT_SPEED .5
#define FEED_SPEED .23

#define SHOOT_VELOCITY 462.5
#define DRIVE_VELOCITY 500
#define FEED_VELOCITY 1200 // velocity of the feeder stuff

#define SHOOT_1 41
#define SHOOT_2 42
#define FEED_1 43
#define FEED_2 44
#define COLLECT 45
#define PIVOT 46
#define CLIMBER 47

// int shoot1, int shoot2, int feed1, int feed2, int collect, int pivot

#define REESES_BEAM 2 // Top Beam
#define BROKEN_BEAM 1 // Bottom Beam

/* ============= MQTTHandler ============= */

#define SEND_BUF_LEN 2048
#define RECV_BUF_LEN 2048

/* ============= Vision ============= */

#define CONTROL_VELOCITY
// TARGET_HEIGHT 20
// COS2_ANGLE 0.786788218
#define SHOOTER_ANGLE 21
// 2 * taget height cos^2 (shooter angle)
#define TH2_COS2_ANGLE 31.47152872
// sin (2 * shooter angle)
#define SIN_2ANGLE 0.819152044