/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "lvgl.h"
#include "app_hal.h"
#include <stdio.h>
#include "demos/lv_demos.h"
#include "music_screen_saver.h"


int main(void)
{
	lv_init();

	hal_setup();
  // lv_demo_widgets();
	// music_screen_saver();
	lv_timer_create(task_ui_update, 500, NULL);
	hal_loop();
}
