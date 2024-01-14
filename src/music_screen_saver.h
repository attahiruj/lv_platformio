	/**
	 * @file        music_screen_saver.h
	 * @author      Attahiru Jibril (attahiruj@gmail.com)
	 * @brief       Functions to create a music screen saver GUI with various elements such as: 
	 *              current date, time, sleep timer, visualizer, temperature, and icons.using the LVGL library. 
	 * @version     0.1
	 * @date        2024-01-07
	 * 
	 * @copyright   Copyright (c)2MJ 2024
	 * 
	 */

	#include "lvgl.h"
	#include "fonts/fonts.h"
	#include <time.h>

	void getCurrentTime(int *hours, int *minutes, int *seconds);
	void getCurrentDate(char *dayOfWeek, int *day, int *month, int *year);
	void music_screen_saver(void);
	void task_ui_update(lv_timer_t * task);

	/**
	 * @brief Functions to create a music screen saver GUI with elements.
	 * 
	 */
	void music_screen_saver(void){

		{
			#define COLOR_BLACK lv_color_hex(0x000000)
			#define COLOR_WHITE lv_color_hex(0xFFFFFF)
			#define COLOR_GREEN lv_color_hex(0x219653)
			#define MAX_CONT_W 300
			#define MAX_CONT_H 300
			#define PAD 32
			
			//main container
			lv_obj_t * container = lv_obj_create(lv_scr_act());
			lv_obj_set_size(container, MAX_CONT_W, MAX_CONT_H);
			lv_obj_align(container, LV_ALIGN_CENTER, 0, 0);
			lv_obj_set_style_bg_color(container, COLOR_BLACK, 0);
			lv_obj_set_style_radius(container, 30, 0);
			lv_obj_set_style_border_width(container, 0, 0);
			lv_obj_set_style_pad_all(container, PAD, 0);
			lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
			lv_obj_set_style_text_color(container, COLOR_WHITE, 0);

			//date
			{	
				char weekday[20];
				int day, month, year;
				getCurrentDate(weekday, &day, &month, &year);
				lv_obj_t * label_date = lv_label_create(container);
				lv_label_set_text_fmt(label_date, "%s %02d", weekday, day);
				lv_obj_set_style_text_font(label_date, &saira_semi_condensed_thin_14, LV_STATE_DEFAULT);
			}
			//time
			{	
				// const char* time = "08:26 43";
				int time_hour, time_minute, time_sec;
				getCurrentTime(&time_hour, &time_minute, &time_sec);
				lv_obj_t * cont_time = lv_obj_create(container);
				lv_obj_set_flex_flow(cont_time, LV_FLEX_FLOW_ROW);
				lv_obj_set_pos(cont_time, 0, 62 - PAD);
				lv_obj_set_size(cont_time, lv_pct(100), 48);
				lv_obj_set_style_bg_color(cont_time, COLOR_BLACK, 0);
				lv_obj_set_style_text_color(cont_time, COLOR_WHITE, 0);
				lv_obj_set_style_radius(cont_time, 0, 0);
				lv_obj_set_style_border_width(cont_time, 0, 0);
				lv_obj_set_style_pad_all(cont_time, 0, 0);
				{
					lv_obj_t * label_time_hm = lv_label_create(cont_time);
					lv_label_set_text_fmt(label_time_hm, "%02d:%02d", time_hour, time_minute);
					lv_obj_set_style_text_font(label_time_hm, &saira_semi_condensed_thin_48, LV_STATE_DEFAULT);
					lv_obj_set_align(label_time_hm, LV_ALIGN_TOP_LEFT);
				}
				{
					lv_obj_t * label_time_sec = lv_label_create(cont_time);
					lv_label_set_text_fmt(label_time_sec, "%02d", time_sec);
					lv_obj_set_style_text_font(label_time_sec, &saira_semi_condensed_thin_32, LV_STATE_DEFAULT);
					lv_obj_set_align(label_time_sec, LV_ALIGN_BOTTOM_LEFT);
				}
			}
			//sleep timer
			{
				lv_obj_t * label_sleep = lv_label_create(container);
				lv_label_set_text(label_sleep, "sleep");
				lv_obj_set_style_text_font(label_sleep, &saira_semi_condensed_thin_12, LV_STATE_DEFAULT);
				lv_obj_set_pos(label_sleep, 0, 140 - PAD);
			}
			{
				lv_obj_t * cont_sleep_time = lv_obj_create(container);
				lv_obj_set_pos(cont_sleep_time, 210 - PAD, 140 - PAD);
				lv_obj_set_size(cont_sleep_time, 58, 13);
				lv_obj_set_style_bg_color(cont_sleep_time, COLOR_GREEN, 0);
				lv_obj_set_style_radius(cont_sleep_time, 3, 0);
				lv_obj_set_style_border_width(cont_sleep_time, 0, 0);
				lv_obj_set_style_pad_all(cont_sleep_time, 0, 0);
				{
					int sleep_time_hr = 1;
					int sleep_time_min = 5;
					lv_obj_t * label_sleep_time = lv_label_create(cont_sleep_time);
					lv_label_set_text_fmt(label_sleep_time, "%dH %dM", sleep_time_hr, sleep_time_min);
					lv_obj_set_style_text_font(label_sleep_time, &saira_semi_condensed_thin_12, LV_STATE_DEFAULT);
					lv_obj_set_align(label_sleep_time, LV_ALIGN_CENTER);
					lv_obj_set_style_text_color(label_sleep_time, COLOR_WHITE, 0);
				}
			}
			//visualiser
			{
				lv_obj_t * cont_vis_wrapper = lv_obj_create(container);
				lv_obj_set_pos(cont_vis_wrapper, 0, 158 - PAD);
				lv_obj_set_size(cont_vis_wrapper, lv_pct(100), 76);
				lv_obj_set_style_bg_color(cont_vis_wrapper, COLOR_GREEN, 0);
				lv_obj_set_style_radius(cont_vis_wrapper, 15, 0);
				lv_obj_set_style_border_width(cont_vis_wrapper, 0, 0);
				lv_obj_set_style_pad_all(cont_vis_wrapper, 8, 0);
				
				//song details [name	artist]
				{
					lv_obj_t * cont_song_details = lv_obj_create(cont_vis_wrapper);
					lv_obj_set_size(cont_song_details, lv_pct(100), 16);
					lv_obj_set_style_bg_color(cont_song_details, COLOR_GREEN, 0);
					lv_obj_set_style_text_color(cont_song_details, COLOR_WHITE, 0);
					lv_obj_set_style_radius(cont_song_details, 0, 0);
					lv_obj_set_style_border_width(cont_song_details, 0, 0);
					lv_obj_set_style_pad_all(cont_song_details, 2, 0);
					//song name
					{
						const char* song_name = "Joha";
						lv_obj_t * label_song_name = lv_label_create(cont_song_details);
						lv_label_set_text(label_song_name, song_name);
						lv_obj_set_style_text_font(label_song_name, &saira_semi_condensed_thin_12, LV_STATE_DEFAULT);
						lv_obj_set_align(label_song_name, LV_ALIGN_LEFT_MID);
					}
					//song artist
					{
						const char* song_artist = "Asake";
						lv_obj_t * label_song_artist = lv_label_create(cont_song_details);
						lv_label_set_text(label_song_artist, song_artist);
						lv_obj_set_style_text_font(label_song_artist, &saira_semi_condensed_thin_12, LV_STATE_DEFAULT);
						lv_obj_set_align(label_song_artist, LV_ALIGN_RIGHT_MID);
					}
				}
				//visualizer
				{
					lv_obj_t * cont_viz_wrapper = lv_obj_create(cont_vis_wrapper);
					lv_obj_remove_style_all(cont_viz_wrapper);
					lv_obj_set_size(cont_viz_wrapper, lv_pct(100), lv_pct(80));
					lv_obj_set_flex_flow(cont_viz_wrapper, LV_FLEX_FLOW_COLUMN);
					lv_obj_set_align(cont_viz_wrapper, LV_ALIGN_BOTTOM_MID);

					{
						/* This code is creating a bar chart using the LVGL library. */
						int bar_count = 14;
						lv_obj_t * chart = lv_chart_create(cont_viz_wrapper);
						lv_obj_set_size(chart, lv_pct(100), lv_pct(100));
						lv_obj_set_flex_grow(chart, 1);
						lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
						lv_chart_set_div_line_count(chart, 0, 0);
						lv_obj_set_style_bg_opa(chart, 0, 0);
						lv_obj_set_style_radius(chart, 2, 0);
						lv_obj_set_style_border_width(chart, 0, LV_STATE_DEFAULT);
						lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
						// lv_chart_set_range(chart, LV_CHART_AXIS_SECONDARY_Y, 0, 400);
						lv_chart_set_point_count(chart, bar_count);

						/* This code is adding a series to a chart and populating it with random values. */
						lv_chart_series_t * waves = lv_chart_add_series(chart, COLOR_BLACK, LV_CHART_AXIS_PRIMARY_Y);
						uint32_t i;
						for(i = 0; i < bar_count; i++) {
							lv_chart_set_next_value(chart, waves, lv_rand(10, 100));
						}
						lv_chart_refresh(chart);
					}
				}
			}
			//temp
			{	
				int temp = 29;
				lv_obj_t * label_temp = lv_label_create(container);
				lv_label_set_text_fmt(label_temp, "%02d°C", temp);
				lv_obj_set_style_text_font(label_temp, &saira_semi_condensed_thin_32, LV_STATE_DEFAULT);
				lv_obj_set_align(label_temp, LV_ALIGN_BOTTOM_LEFT);
			}
			// icons
			{
				lv_obj_t * icon_headphone = lv_label_create(container);
				lv_label_set_text(icon_headphone, LV_SYMBOL_AUDIO);
				lv_obj_set_pos(icon_headphone, 225 - PAD, 242 - PAD);
			}
			{
				lv_obj_t * icon_bluetooth = lv_label_create(container);
				lv_label_set_text(icon_bluetooth, LV_SYMBOL_BLUETOOTH);
				lv_obj_set_pos(icon_bluetooth, 254 - PAD, 242 - PAD);
			}
		}
	}

	/**
	 * The function getCurrentTime retrieves the current time and updates the provided integer variables
	 * with the hours, minutes, and seconds components of the time.
	 * 
	 * @param hours A pointer to an integer variable that will store the current hour.
	 * @param minutes  A pointer to an integer variable that will be updated with the current minute value.
	 * @param seconds A pointer to an integer variable that will be updated with the current seconds
	 * component of the time.
	 */
	void getCurrentTime(int *hours, int *minutes, int *seconds) {
		time_t currentTime;
		struct tm *localTime;

		// Get current time
		time(&currentTime);
		localTime = localtime(&currentTime);

		// Update the integers with the current time components
		*hours = localTime->tm_hour;
		*minutes = localTime->tm_min;
		*seconds = localTime->tm_sec;
	}

	/**
	 * The function getCurrentDate retrieves the current day of the week, day, month, and year and stores
	 * them in the provided variables.
	 * 
	 * @param dayOfWeek A character array that will be updated with the current day of the week.
	 * @param day A pointer to an integer variable that will be updated with the current day of the month.
	 * @param month The month parameter is a pointer to an integer variable that will be updated with the
	 * current month.
	 * @param year A pointer to an integer variable that will be updated with the current year.
	 */
	void getCurrentDate(char *dayOfWeek, int *day, int *month, int *year) {
		time_t currentTime;
		struct tm *localTime;

		// Get current time
		time(&currentTime);
		localTime = localtime(&currentTime);

		// Update the string with the current day of the week
		strftime(dayOfWeek, 20, "%A", localTime);

		// Update the integers with the current date components
		*day = localTime->tm_mday;
		*month = localTime->tm_mon + 1;  // Months are 0-based in struct tm
		*year = localTime->tm_year + 1900;  // Years since 1900 in struct tm
	}

	/**
	 * @brief a callback function that is called periodically by a timer.
	 * 
	 * @param task `lv_timer_t` pointer
	 */
	void task_ui_update(lv_timer_t * task){
		music_screen_saver();
	}