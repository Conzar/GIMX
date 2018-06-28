/*
 Copyright (c) 2014 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#include <pro.h>
#include <report.h>
#include <string.h>
#include "../include/controller.h"

static s_axis axes[AXIS_MAX] =
{
  [pro_lstick_x] =  { .name = "lstick x",  .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_lstick_y] =  { .name = "lstick y",  .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_rstick_x] =  { .name = "rstick x",  .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_rstick_y] =  { .name = "rstick y",  .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  
  [pro_finger1_x] = { .name = "finger1 x", .max_unsigned_value = PRO_TRACKPAD_MAX_X },
  [pro_finger1_y] = { .name = "finger1 y", .max_unsigned_value = PRO_TRACKPAD_MAX_Y },
  [pro_finger2_x] = { .name = "finger2 x", .max_unsigned_value = PRO_TRACKPAD_MAX_X },
  [pro_finger2_y] = { .name = "finger2 y", .max_unsigned_value = PRO_TRACKPAD_MAX_Y },
  
  [pro_share] =     { .name = "share",     .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_options] =   { .name = "options",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_up] =        { .name = "up",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_right] =     { .name = "right",     .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_down] =      { .name = "down",      .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_left] =      { .name = "left",      .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_triangle] =  { .name = "triangle",  .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_circle] =    { .name = "circle",    .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_cross] =     { .name = "cross",     .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_square] =    { .name = "square",    .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_l1] =        { .name = "l1",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_r1] =        { .name = "r1",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_l2] =        { .name = "l2",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_r2] =        { .name = "r2",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_l3] =        { .name = "l3",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_r3] =        { .name = "r3",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_ps] =        { .name = "PS",        .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_touchpad] =  { .name = "touchpad",  .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_finger1] =   { .name = "finger1",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
  [pro_finger2] =   { .name = "finger2",   .max_unsigned_value = MAX_AXIS_VALUE_8BITS },
};

static s_axis_name_dir axis_name_dirs[] =
{
  {.name = "rstick x",     {.axis = pro_rstick_x, .props = AXIS_PROP_CENTERED}},
  {.name = "rstick y",     {.axis = pro_rstick_y, .props = AXIS_PROP_CENTERED}},
  {.name = "lstick x",     {.axis = pro_lstick_x, .props = AXIS_PROP_CENTERED}},
  {.name = "lstick y",     {.axis = pro_lstick_y, .props = AXIS_PROP_CENTERED}},

  {.name = "rstick left",  {.axis = pro_rstick_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},
  {.name = "rstick right", {.axis = pro_rstick_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},
  {.name = "rstick up",    {.axis = pro_rstick_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},
  {.name = "rstick down",  {.axis = pro_rstick_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},

  {.name = "lstick left",  {.axis = pro_lstick_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},
  {.name = "lstick right", {.axis = pro_lstick_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},
  {.name = "lstick up",    {.axis = pro_lstick_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},
  {.name = "lstick down",  {.axis = pro_lstick_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},

  {.name = "finger1 x",    {.axis = pro_finger1_x, .props = AXIS_PROP_CENTERED,}},
  {.name = "finger1 y",    {.axis = pro_finger1_y, .props = AXIS_PROP_CENTERED,}},
  {.name = "finger2 x",    {.axis = pro_finger2_x, .props = AXIS_PROP_CENTERED,}},
  {.name = "finger2 y",    {.axis = pro_finger2_y, .props = AXIS_PROP_CENTERED,}},

  {.name = "finger1 x -",  {.axis = pro_finger1_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},
  {.name = "finger1 y -",  {.axis = pro_finger1_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},
  {.name = "finger2 x -",  {.axis = pro_finger2_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},
  {.name = "finger2 y -",  {.axis = pro_finger2_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_NEGATIVE}},

  {.name = "finger1 x +",  {.axis = pro_finger1_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},
  {.name = "finger1 y +",  {.axis = pro_finger1_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},
  {.name = "finger2 x +",  {.axis = pro_finger2_x, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},
  {.name = "finger2 y +",  {.axis = pro_finger2_y, .props = AXIS_PROP_CENTERED | AXIS_PROP_POSITIVE}},

  {.name = "r2",           {.axis = pro_r2,       .props = AXIS_PROP_POSITIVE}},
  {.name = "l2",           {.axis = pro_l2,       .props = AXIS_PROP_POSITIVE}},

  {.name = "share",        {.axis = pro_share,    .props = AXIS_PROP_TOGGLE}},
  {.name = "options",      {.axis = pro_options,  .props = AXIS_PROP_TOGGLE}},
  {.name = "PS",           {.axis = pro_ps,       .props = AXIS_PROP_TOGGLE}},
  {.name = "up",           {.axis = pro_up,       .props = AXIS_PROP_TOGGLE}},
  {.name = "down",         {.axis = pro_down,     .props = AXIS_PROP_TOGGLE}},
  {.name = "right",        {.axis = pro_right,    .props = AXIS_PROP_TOGGLE}},
  {.name = "left",         {.axis = pro_left,     .props = AXIS_PROP_TOGGLE}},
  {.name = "r1",           {.axis = pro_r1,       .props = AXIS_PROP_TOGGLE}},
  {.name = "r3",           {.axis = pro_r3,       .props = AXIS_PROP_TOGGLE}},
  {.name = "l1",           {.axis = pro_l1,       .props = AXIS_PROP_TOGGLE}},
  {.name = "l3",           {.axis = pro_l3,       .props = AXIS_PROP_TOGGLE}},
  {.name = "circle",       {.axis = pro_circle,   .props = AXIS_PROP_TOGGLE}},
  {.name = "square",       {.axis = pro_square,   .props = AXIS_PROP_TOGGLE}},
  {.name = "cross",        {.axis = pro_cross,    .props = AXIS_PROP_TOGGLE}},
  {.name = "triangle",     {.axis = pro_triangle, .props = AXIS_PROP_TOGGLE}},
  {.name = "touchpad",     {.axis = pro_touchpad, .props = AXIS_PROP_TOGGLE}},
  {.name = "finger1",      {.axis = pro_finger1,  .props = AXIS_PROP_TOGGLE}},
  {.name = "finger2",      {.axis = pro_finger2,  .props = AXIS_PROP_TOGGLE}},
};

static s_report_pro default_report =
{
  .report_id = 0x00,
  .X = 0x80,
  .Y = 0x80,
  .Z = 0x80,
  .Rz = 0x80,
  .HatAndButtons = 0x08,
  .ButtonsAndCounter = 0xfc00,
  .Rx = 0x00,
  .Ry = 0x00,
  ._time = 0x5099,
  .battery_level = 0xff,
  .motion_acc = {0x0006, 0x0001, 0x350f},
  .motion_gyro = {0x1903,  0x0001, 0x0008},
  ._unknown1 = {0x00, 0x00, 0x00, 0x00, 0x00},
  .ext = 0x08,
  ._unknown2 = {0x00, 0x00},
  .packets = 0x00,
  .packet1 =
  {
    .counter = 0x00,
    .finger1 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
    .finger2 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
  },
  .packet2 =
  {
    .counter = 0x00,
    .finger1 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
    .finger2 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
  },
  .packet3 =
  {
    .counter = 0x00,
    .finger1 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
    .finger2 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
  },
  .packet4 =
  {
    .counter = 0x00,
    .finger1 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
    .finger2 =
    {
      .id = 0x80,
      .coords = {0x00, 0x00, 0x00}
    },
  },
  ._unknown5 = {0x00, 0x00},
};

static void init_report(s_report * report)
{
  memcpy(report, &default_report, sizeof(default_report));
}

/*
 * Update touchpad finger.
 * The axes are relative to the last position.
 */
static inline void update_finger(s_trackpad_finger* finger, int presence, int* axis_x, int* axis_y)
{
  unsigned char* coords = finger->coords;

  unsigned short finger_x;
  unsigned short finger_y;

  if(presence)
  {
    if(finger->id & 0x80)
    {
      //increase the finger id in case of new touch
      finger->id++;

      //start movement from center
      finger_x = PRO_TRACKPAD_MAX_X/2;
      finger_y = PRO_TRACKPAD_MAX_Y/2;
    }
    else
    {
      //continue movement from last position
      finger_x = ((coords[1] & 0x0F) << 8) | coords[0];
      finger_y = coords[2] << 4 | (coords[1]>>4);
    }

    //finger present
    finger->id &= 0x7F;

    int x = finger_x + *axis_x;
    int y = finger_y + *axis_y;

    finger_x = clamp(0, x, PRO_TRACKPAD_MAX_X);
    finger_y = clamp(0, y, PRO_TRACKPAD_MAX_Y);

    coords[0] = finger_x & 0xFF;
    coords[1] =  ((finger_x >> 8) & 0x0F) | ((finger_y & 0x0F) << 4);
    coords[2] =  finger_y >> 4;
  }
  else
  {
    //finger absent
    finger->id |= 0x80;
  }
}

static unsigned int build_report(int axis[AXIS_MAX], s_report_packet report[MAX_REPORTS])
{
  unsigned int index = 0;
  report[index].length = sizeof(s_report_pro);
  s_report_pro* pro = &report[index].value.pro;

  unsigned char counter;
  unsigned short buttons = 0x0000;

  pro->X = clamp(0, axis[pro_lstick_x] + CENTER_AXIS_VALUE_8BITS, MAX_AXIS_VALUE_8BITS);
  pro->Y = clamp(0, axis[pro_lstick_y] + CENTER_AXIS_VALUE_8BITS, MAX_AXIS_VALUE_8BITS);
  pro->Z = clamp(0, axis[pro_rstick_x] + CENTER_AXIS_VALUE_8BITS, MAX_AXIS_VALUE_8BITS);
  pro->Rz = clamp(0, axis[pro_rstick_y] + CENTER_AXIS_VALUE_8BITS, MAX_AXIS_VALUE_8BITS);

  if (axis[pro_right])
  {
    if (axis[pro_down])
    {
      pro->HatAndButtons = 0x03;
    }
    else if (axis[pro_up])
    {
      pro->HatAndButtons = 0x01;
    }
    else
    {
      pro->HatAndButtons = 0x02;
    }
  }
  else if (axis[pro_left])
  {
    if (axis[pro_down])
    {
      pro->HatAndButtons = 0x05;
    }
    else if (axis[pro_up])
    {
      pro->HatAndButtons = 0x07;
    }
    else
    {
      pro->HatAndButtons = 0x06;
    }
  }
  else if (axis[pro_down])
  {
    pro->HatAndButtons = 0x04;
  }
  else if (axis[pro_up])
  {
    pro->HatAndButtons = 0x00;
  }
  else
  {
    pro->HatAndButtons = 0x08;
  }

  if (axis[pro_square])
  {
    pro->HatAndButtons |= PRO_SQUARE_MASK;
  }
  if (axis[pro_cross])
  {
    pro->HatAndButtons |= PRO_CROSS_MASK;
  }
  if (axis[pro_circle])
  {
    pro->HatAndButtons |= PRO_CIRCLE_MASK;
  }
  if (axis[pro_triangle])
  {
    pro->HatAndButtons |= PRO_TRIANGLE_MASK;
  }

  if (axis[pro_l1])
  {
    buttons |= PRO_L1_MASK;
  }
  if (axis[pro_r1])
  {
    buttons |= PRO_R1_MASK;
  }
  if (axis[pro_l2])
  {
    buttons |= PRO_L2_MASK;
  }
  if (axis[pro_r2])
  {
    buttons |= PRO_R2_MASK;
  }
  if (axis[pro_share])
  {
    buttons |= PRO_SHARE_MASK;
  }
  if (axis[pro_options])
  {
    buttons |= PRO_OPTIONS_MASK;
  }
  if (axis[pro_l3])
  {
    buttons |= PRO_L3_MASK;
  }
  if (axis[pro_r3])
  {
    buttons |= PRO_R3_MASK;
  }
  if (axis[pro_ps])
  {
    buttons |= PRO_PS_MASK;
  }
  if (axis[pro_touchpad])
  {
    buttons |= PRO_TOUCHPAD_MASK;
  }

  counter = (pro->ButtonsAndCounter >> 8) & 0xFC;
  counter += 4;

  pro->ButtonsAndCounter = (counter << 8) | buttons;

  pro->Rx = clamp(0, axis[pro_l2], MAX_AXIS_VALUE_8BITS);
  pro->Ry = clamp(0, axis[pro_r2], MAX_AXIS_VALUE_8BITS);

  pro->packets = 1;

  if(axis[pro_finger1] || axis[pro_finger2])
  {
    pro->packet1.counter += 4;
  }

  update_finger(&pro->packet1.finger1, axis[pro_finger1], &axis[pro_finger1_x], &axis[pro_finger1_y]);

  update_finger(&pro->packet1.finger2, axis[pro_finger2], &axis[pro_finger2_x], &axis[pro_finger2_y]);

  return index;
}

static s_controller controller =
{
  .name = "PRO",
  .vid = PRO_VENDOR,
  .pid = PRO_PRODUCT,
  .refresh_period = { .min_value = 1000, .default_value = 10000 },
  .auth_required = 1,
  .axes = axes,
  .axis_name_dirs = { .nb = sizeof(axis_name_dirs)/sizeof(*axis_name_dirs), .values = axis_name_dirs },
  .fp_build_report = build_report,
  .fp_init_report = init_report,
  .activation_button = pro_ps,
};

void pro_init(void) __attribute__((constructor));
void pro_init(void)
{
  controller_register(C_TYPE_PRO, &controller);
}

