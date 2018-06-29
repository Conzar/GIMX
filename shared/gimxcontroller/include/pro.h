/*
 Copyright (c) 2014 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */


/* Details attained from here:
  https://github.com/dekuNukem/Nintendo_Switch_Reverse_Engineering/blob/master/bluetooth_hid_notes.md#standard-input-report---stick-data
 */
#ifndef PRO_H_
#define PRO_H_

#include "defs.h"

#define PRO_USB_INTERRUPT_ENDPOINT_IN 4
#define PRO_USB_INTERRUPT_ENDPOINT_OUT 3
#define PRO_USB_INTERRUPT_PACKET_SIZE 64

#define PRO_USB_HID_IN_REPORT_ID 0x01

#define PRO_DEVICE_NAME "Pro Controller"

#define PRO_VENDOR 0x054c
#define PRO_PRODUCT 0x05c4
#define PRO_PRODUCT_2 0x09cc

#define PRO_DOWN_MASK       0x01
#define PRO_RIGHT_MASK      0x02
#define PRO_LEFT_MASK       0x04
#define PRO_UP_MASK         0x08

#define PRO_SQUARE_MASK     0x10
#define PRO_CROSS_MASK      0x20
#define PRO_CIRCLE_MASK     0x40
#define PRO_TRIANGLE_MASK   0x80

#define PRO_L1_MASK         0x0001
#define PRO_R1_MASK         0x0002
#define PRO_L2_MASK         0x0004
#define PRO_R2_MASK         0x0008

#define PRO_SHARE_MASK      0x0020
#define PRO_OPTIONS_MASK    0x0010
#define PRO_L3_MASK         0x0040
#define PRO_R3_MASK         0x0080

#define PRO_PS_MASK         0x0100
#define PRO_TOUCHPAD_MASK   0x0200

#ifndef WIN32
#define PRO_SQUARE_ID     0
#define PRO_CROSS_ID      1
#define PRO_CIRCLE_ID     2
#define PRO_TRIANGLE_ID   3

#define PRO_L1_ID         4
#define PRO_R1_ID         5
#define PRO_L2_ID         6
#define PRO_R2_ID         7

#define PRO_SHARE_ID      8
#define PRO_OPTIONS_ID    9
#define PRO_L3_ID         10
#define PRO_R3_ID         11

#define PRO_PS_ID         12
#define PRO_TOUCHPAD_ID   13

#define PRO_UP_ID         14
#define PRO_RIGHT_ID      15
#define PRO_DOWN_ID       16
#define PRO_LEFT_ID       17

#define PRO_AXIS_X_ID     0
#define PRO_AXIS_Y_ID     1
#define PRO_AXIS_Z_ID     2
#define PRO_AXIS_L2_ID    3
#define PRO_AXIS_R2_ID    4
#define PRO_AXIS_RZ_ID    5
#else
#define PRO_X_ID          2
#define PRO_Y_ID          0
#define PRO_A_ID          1
#define PRO_B_ID          3

#define PRO_L1_ID         9
#define PRO_R1_ID         10
#define PRO_L2_ID         10//bug?
#define PRO_R2_ID         7//bug?

#define PRO_SHARE_ID      4
#define PRO_OPTIONS_ID    6
#define PRO_L3_ID         7
#define PRO_R3_ID         8

#define PRO_PS_ID         5
#define PRO_TOUCHPAD_ID   15//not detected by the default hid driver

#define PRO_UP_ID         11
#define PRO_RIGHT_ID      14
#define PRO_DOWN_ID       12
#define PRO_LEFT_ID       13

#define PRO_AXIS_X_ID     0
#define PRO_AXIS_Y_ID     1
#define PRO_AXIS_Z_ID     2
#define PRO_AXIS_RZ_ID    3
#define PRO_AXIS_L2_ID    4
#define PRO_AXIS_R2_ID    5
#endif

#define PRO_TRACKPAD_MAX_X 1919
#define PRO_TRACKPAD_MAX_Y 919

typedef enum
{
  pro_lstick_x  = rel_axis_lstick_x,
  pro_lstick_y  = rel_axis_lstick_y,
  pro_rstick_x  = rel_axis_rstick_x,
  pro_rstick_y  = rel_axis_rstick_y,
  pro_finger1_x = rel_axis_4,
  pro_finger1_y = rel_axis_5,
  pro_finger2_x = rel_axis_6,
  pro_finger2_y = rel_axis_7,
  pro_share     = abs_axis_0,
  pro_options   = abs_axis_1,
  pro_ps        = abs_axis_2,
  pro_up        = abs_axis_3,
  pro_right     = abs_axis_4,
  pro_down      = abs_axis_5,
  pro_left      = abs_axis_6,
  pro_x         = abs_axis_7,
  pro_y         = abs_axis_8,
  pro_a         = abs_axis_9,
  pro_b         = abs_axis_10,
  pro_l1        = abs_axis_11,
  pro_r1        = abs_axis_12,
  pro_l2        = abs_axis_13,
  pro_r2        = abs_axis_14,
  pro_l3        = abs_axis_15,
  pro_r3        = abs_axis_16,
  pro_touchpad  = abs_axis_17,
  pro_finger1   = abs_axis_18,
  pro_finger2   = abs_axis_19,
} e_ds4_axis_index;

typedef struct GIMX_PACKED
{
  unsigned char id;
  unsigned char coords[3];
} s_trackpad_finger;

typedef struct GIMX_PACKED
{
  unsigned char counter;
  s_trackpad_finger finger1;
  s_trackpad_finger finger2;
} s_trackpad_packet;

typedef struct GIMX_PACKED
{
  short x;
  short y;
  short z;
} s_motion_acc;

typedef struct GIMX_PACKED
{
  short roll;
  short yaw;
  short pitch;
} s_motion_gyro;

/*
 *
 */
typedef struct GIMX_PACKED
{
  unsigned char report_id; //USB: 0x01, BT: 0x00
  unsigned char X;
  unsigned char Y;
  unsigned char Z;
  unsigned char Rz;
  unsigned char HatAndButtons;
  unsigned short ButtonsAndCounter;
  unsigned char Rx;
  unsigned char Ry;
  unsigned short _time;
  unsigned char battery_level;
  s_motion_acc motion_acc;
  s_motion_gyro motion_gyro;
  unsigned char _unknown1[5];
  unsigned char ext;
  unsigned char _unknown2[2];
  unsigned char packets;
  s_trackpad_packet packet1;
  s_trackpad_packet packet2;
  s_trackpad_packet packet3;
  s_trackpad_packet packet4;
  unsigned char _unknown5[2];
} s_report_ds4;

typedef struct
{
  // TODO MLA
} s_gc_state_ds4;

#endif /* PRO_H_ */
