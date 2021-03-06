#ifndef REMAP_H
#define REMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <math.h>
#include <string.h>
#include "debugnet.h"

#define debug(format, args...) debugNetPrintf(DEBUG, format "\n", args)

typedef enum trigger {
    CTRL_SELECT      = 0x000001,        //!< Select button.
    CTRL_L3          = 0x000002,        //!< L3 button.
    CTRL_R3          = 0x000004,        //!< R3 button.
    CTRL_START       = 0x000008,        //!< Start button.
    CTRL_UP          = 0x000010,        //!< Up D-Pad button.
    CTRL_RIGHT       = 0x000020,        //!< Right D-Pad button.
    CTRL_DOWN        = 0x000040,        //!< Down D-Pad button.
    CTRL_LEFT        = 0x000080,        //!< Left D-Pad button.
    CTRL_LTRIGGER    = 0x000100,        //!< Left trigger.
    CTRL_RTRIGGER    = 0x000200,        //!< Right trigger.
    CTRL_L1          = 0x000400,        //!< L1 button.
    CTRL_R1          = 0x000800,        //!< R1 button.
    CTRL_TRIANGLE    = 0x001000,        //!< Triangle button.
    CTRL_CIRCLE      = 0x002000,        //!< Circle button.
    CTRL_CROSS       = 0x004000,        //!< Cross button.
    CTRL_SQUARE      = 0x008000,        //!< Square button.


    RS_UP = 0x500000,
    RS_DOWN,
    RS_LEFT,
    RS_RIGHT,

    LS_UP,
    LS_DOWN,
    LS_LEFT,
    LS_RIGHT,

    TOUCHSCREEN_NW = 0x400000,
    TOUCHSCREEN_NE,
    TOUCHSCREEN_SW,
    TOUCHSCREEN_SE,

    RS_ANY = 0x300000,
    LS_ANY,
} trigger_t;

extern int TRIGGERS[30];
#define TRIGGERS_COUNT 30
#define TRIGGERS_BUTTONS_COUNT 16
#define TRIGGERS_NOTOUCH_COUNT TRIGGERS_BUTTONS_COUNT + 8

typedef enum {
    ACTION_BUTTON,
    ACTION_FRONTTOUCHSCREEN,
    ACTION_BACKTOUCHSCREEN,
    ACTION_RS,
    ACTION_LS,
} action_type_t;

typedef struct {
    action_type_t type;
    int value;
    int x, y;
} action_t;

typedef struct {
    int size;
    action_t *list;
} action_list_t;

typedef struct {
    int rs_deadzone, ls_deadzone;
    int back_touch_deadzone_vertical, back_touch_deadzone_horizontal;
    int front_touch_deadzone_vertical, front_touch_deadzone_horizontal;

    int size;
    trigger_t *triggers;
    action_list_t *actions;
} remap_config_t;

#define REMAP_MAX_ACTIONS 24

//

void remap_deadzone_ignore(remap_config_t config, SceCtrlData *mut_pad, SceTouchData *mut_front, SceTouchData *mut_back);
void remap(remap_config_t config, SceCtrlData *mut_pad, SceTouchData *mut_front, SceTouchData *mut_back);

int remap_read_trigger(trigger_t *trigger, SceCtrlData pad, SceTouchData front, SceTouchData back);
int remap_read_actions(action_list_t *actions, SceCtrlData pad, SceTouchData front, SceTouchData back);

#define TRIGGER_NAME_SIZE 256
#define ACTION_NAME_SIZE 1024
void remap_trigger_name(int id, char buf[TRIGGER_NAME_SIZE]);
void remap_config_action_name(remap_config_t config, int i, char buf[ACTION_NAME_SIZE]);

#include "config.h"

#endif
