/*
	Application template for Amazfit Bip BipOS
	(C) Maxim Volkov  2019 <Maxim.N.Volkov@ya.ru>
	
	Application template loader for the BipOS
	
*/

#include <libbip.h>

#include "amlich.h"
#include "amlich_utils.h"

//	screen menu structure - each screen has its own
struct regmenu_ screen_data = {
  55, //	main screen number, value 0-255, for custom windows it is better to take from 50 and above
  1, //	auxiliary screen number (usually 1)
  0, //	0
  dispatch_screen, //	pointer to the function handling touch, swipe, long press
  key_press_screen, //	pointer to the function handling pressing the button
  screen_job, //	pointer to the callback function of the timer  
  0, //	0
  show_screen, //	pointer to the screen display function
  0, //	
  0 //	long press of the button
};
int main(int param0, char ** argv) { //	here the variable argv is not defined
  show_screen((void * ) param0);
}

void show_screen(void * param0) {
  struct app_data_ ** app_data_p = get_ptr_temp_buf_2(); //	pointer to a pointer to screen data
  struct app_data_ * app_data; //	pointer to screen data

  Elf_proc_ * proc;

  // check the source at the procedure launch
  if ((param0 == * app_data_p) && get_var_menu_overlay()) { // return from the overlay screen (incoming call, notification, alarm, target, etc.)

    app_data = * app_data_p; //	the data pointer must be saved for the deletion 
    //	release memory function reg_menu
    * app_data_p = NULL; //	reset the pointer to pass it to the function reg_menu		

    // 	create a new screen when the pointer temp_buf_2 is equal to 0 and the memory is not released		
    reg_menu( &screen_data, 0); // 	menu_overlay=0

    * app_data_p = app_data; //	restore the data pointer after the reg_menu function

    //   here we perform actions when returning from the overlay screen: restore data, etc.

  } else { // if the function is started for the first time i.e. from the menu 

    // create a screen (register in the system) 
    reg_menu( &screen_data, 0);

    // allocate the necessary memory and place the data in it (the memory by the pointer stored at temp_buf_2 is released automatically by the function reg_menu of another screen)
    * app_data_p = (struct app_data_ * ) pvPortMalloc(sizeof(struct app_data_));
    app_data = * app_data_p; //	data pointer

    // clear the memory for data
    _memclr(app_data, sizeof(struct app_data_));

    //	param0 value contains a pointer to the data of the running process structure Elf_proc_
    proc = param0;

    // remember the address of the pointer to the function you need to return to after finishing this screen
    if (param0 && proc->ret_f) //	if the return pointer is passed, then return to it
      app_data->ret_f = proc->elf_finish;
    else //	if not, to the watchface
      app_data->ret_f = show_watchface;

    // here we perform actions that are necessary if the function is launched for the first time from the menu: filling all data structures, etc.

    struct datetime_ datetime;
    _memclr( &datetime, sizeof(struct datetime_));
    get_current_date_time(&datetime);
    // remember: datetime.month is from 1 to 12
    app_data->day = datetime.day;
    app_data->month = datetime.month;
    app_data->today_month = datetime.month;
    app_data->year = datetime.year;
    app_data->today_year = datetime.year;
    app_data->buffer[20] = '\0';
    app_data->show_about_us = 0;
  }

  // here we do the interface drawing, there is no need to update (move to video memory) the screen

  draw_screen(app_data);

  // if necessary, set the call timer screen_job in ms
  // set_update_period(1, 30000);
}

void key_press_screen() {
  struct app_data_ ** app_data_p = get_ptr_temp_buf_2(); //	pointer to a pointer to screen data 
  struct app_data_ * app_data = * app_data_p; //	pointer to screen data

  // call the return function (usually this is the start menu), specify the address of the function of our application as a parameter
  show_menu_animate(app_data->ret_f, (unsigned int) show_screen, ANIMATE_RIGHT);
};

void screen_job() {
  // if necessary, you can use the screen data in this function
  struct app_data_ ** app_data_p = get_ptr_temp_buf_2(); //	pointer to pointer to screen data  
  struct app_data_ * app_data = * app_data_p; //	pointer to screen data

  show_menu_animate(app_data->ret_f, (unsigned int) show_screen, ANIMATE_LEFT);
}

void exit_app() {
  Elf_proc_* proc = get_proc_by_addr(main);
  proc->ret_f = NULL;
  elf_finish(main);
}

int dispatch_screen(void * param) {
  struct app_data_ ** app_data_p = get_ptr_temp_buf_2(); //	pointer to a pointer to screen data 
  struct app_data_ * app_data = * app_data_p; //	pointer to screen data

  // in case of rendering the interface, update (transfer to video memory) the screen

  struct gesture_ * gest = param;
  int result = 0;
  int idx = get_index(app_data->month, app_data->year);

  switch (gest->gesture) {
    case GESTURE_CLICK: {
      if (gest->touch_pos_y < 24) {
        app_data->show_about_us = !app_data->show_about_us;
        draw_screen(app_data);
        repaint_screen_lines(0, 176);
      }
      break;
    };

    case GESTURE_SWIPE_RIGHT: { //	swipe to the right
      if (idx == 0) {
        vibrate(1, 100, 0); // top of database
      } else {
        vibrate (1, 40, 0);
        app_data->year--;
        draw_screen(app_data);
        repaint_screen_lines(0, 176);
      }
      break;
    };

    case GESTURE_SWIPE_LEFT: { // swipe to the left
      if (idx == DATABASE_SIZE - 1) {
        vibrate(1, 100, 0); // bottom of database
      } else {
        vibrate(1, 40, 0);
        app_data->year++;
        draw_screen(app_data);
        repaint_screen_lines(0, 176);
      }
      break;
    };

    case GESTURE_SWIPE_UP: { // swipe up
      if (idx == DATABASE_SIZE - 1) {
        vibrate(1, 100, 0); // bottom of database
      } else {
        vibrate(1, 40, 0);
        if (app_data->last_half) {
          if (app_data->month == 12) {
            app_data->month = 1;
            app_data->year++;
          } else {
            app_data->month++;
          }
          app_data->last_half = 0;
        } else {
          app_data->last_half = 1;
        }
        draw_screen(app_data);
        repaint_screen_lines(0, 176);
      }
      break;
    };

    case GESTURE_SWIPE_DOWN: { // swipe down
      if (idx == 0) {
        vibrate(1, 100, 0); // top of database
      } else {
        vibrate (1, 40, 0);
        if (app_data->last_half) {
          app_data->last_half = 0;
        } else {
          if (app_data->month == 1) {
            app_data->month = 12;
            app_data->year--;
          } else {
            app_data->month--;
          }
          app_data->last_half = 1;
        }
        draw_screen(app_data);
        repaint_screen_lines(0, 176);
      }
      break;
    };

    default: { // something went wrong ...
      break;
    };
  }

  return result;
};

#define LAST_HAFT_HIDE_NB_LINES 2
#define OFFSET_CALENDER_X 5
#define OFFSET_CALENDER_Y 18*2
#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8

void draw_buffer(char *buffer, int y) {
  char buf[2];
  buf[1] = '\0';
  for (int i = 0; i < 20; i++) {
    if (buffer[i] == ' ') continue;
    buf[0] = buffer[i];
    text_out(buf, OFFSET_CALENDER_X + i * CHAR_WIDTH, OFFSET_CALENDER_Y + y * CHAR_HEIGHT);
  }
}

void draw_today_mark(int x, int y) {
  int from_x = OFFSET_CALENDER_X + x * CHAR_WIDTH;
  int from_y = OFFSET_CALENDER_Y + y * CHAR_HEIGHT;
  draw_horizontal_line(from_y, from_x, from_x + 2*CHAR_WIDTH);
  draw_horizontal_line(from_y + 2*CHAR_HEIGHT, from_x, from_x + 2*CHAR_WIDTH);
  draw_vertical_line(from_x, from_y, from_y + 2*CHAR_HEIGHT);
  draw_vertical_line(from_x + 2*CHAR_WIDTH, from_y, from_y + 2*CHAR_HEIGHT);
}

// custom function

void draw_about_us() {
  set_fg_color(COLOR_RED);
  text_out_center("\x4c\xe1\xbb\x8b\x63\x68\x20\xc3\xa2\x6d\x20\x64\xc6\xb0\xc6\xa1\x6e\x67", 88, 88-18);
  set_fg_color(COLOR_BLACK);
  text_out_center("\x54\xc3\xa1\x63\x20\x67\x69\xe1\xba\xa3: Nui", 88, 88);
  text_out_center("Web: ngxson.com", 88, 88+18);
  text_out("x", 179-18-5, 5);
}

void draw_screen(struct app_data_ *a) {
  set_bg_color(COLOR_WHITE);
  fill_screen_bg();
  set_graph_callback_to_ram_1();
  load_font();

  if (a->show_about_us) return draw_about_us();

  char buf[20];
  char *data = database[get_index(a->month, a->year)];
  char l_day = data[0];
  char l_month = data[1];
  char l_year = data[2] & 0x7F;
  char l_is_leap_month = data[2] & 0x80;
  char l_month_nb_of_days = l_is_leap_month ? 29 : 30;
  int l_current_day = 1;

  // mm/yyyy
  set_fg_color(COLOR_BLACK);
  _sprintf(buf, "\x4c\xe1\xbb\x8b\x63\x68 %d/%d", a->month, a->year);
  text_out_center(buf, 88, 0);

  // Dau thang:dd/mm/yyyy
  set_fg_color(COLOR_RED);
  _sprintf(buf, "\xc4\x90\xe1\xba\xa7\x75\x20\x74\x68\xc3\xa1\x67\x3a%02d/%02d/%d", l_day, l_month, l_year <= 60 ? (2000 + l_year) : (1900 + l_year));
  text_out(buf, OFFSET_CALENDER_X, 18);
  set_fg_color(COLOR_BLACK);
  text_out("\xc4\x90\xe1\xba\xa7\x75\x20\x74\x68\xc3\xa1\x67\x3a", OFFSET_CALENDER_X, 18);

  int current_day = 1;
  char nb_days = number_of_days(a->month, a->year);
  char first_day_of_week = data[3];

  char should_show_this_line = 0;
  char y_coord = 0;
  char today_x = 100;
  char today_y = 100;

  for (char y = 0; y < 6; y++) {
    today_x = 100;
    today_y = 100;
    should_show_this_line = a->last_half ? (y >= LAST_HAFT_HIDE_NB_LINES) : 1;
    y_coord = a->last_half ? y - LAST_HAFT_HIDE_NB_LINES : y;

    for (char x = 0; x < 7; x++) {
      if ( ( y == 0 && x < first_day_of_week ) || current_day > nb_days ) {
        n_write(a, "   ", 3);
      } else {
        n_write_number(a, current_day);
        if (x < 6) { n_write(a, " ", 1); }

        // check today
        if (
          a->month == a->today_month
          && a->year == a->today_year
          && current_day == a->day
        ) {
          today_x = x;
          today_y = y_coord;
        }

        // next day
        current_day++;
      }
    }

    if (should_show_this_line) draw_buffer(a->buffer, y_coord * 2 + 1);
    n_clear(a);

    // lunar date
    for (char x = 0; x < 7; x++) {
      if ( ( y == 0 && x < first_day_of_week ) || l_current_day > nb_days ) {
        n_write(a, "   ", 3);
      } else {
        n_write_number(a, l_day);
        if (x < 6) { n_write(a, " ", 1); }
        l_current_day++;
        l_day = l_day < l_month_nb_of_days ? l_day + 1 : 1;
      }
    }

    set_fg_color(COLOR_RED);
    if (should_show_this_line) draw_buffer(a->buffer, (y_coord * 2) + 2);
    n_clear(a);
    set_fg_color(COLOR_BLACK);

    if (should_show_this_line && today_x != 100)
      draw_today_mark(
        today_x * 3,
        today_y * 2 + 1
      );
  }

  // draw header
  set_fg_color(COLOR_BLUE);
  draw_buffer("CN T2 T3 T4 T5 T6 T7", 0);
  draw_horizontal_line(OFFSET_CALENDER_Y - 1, 0, 176);
  draw_horizontal_line(OFFSET_CALENDER_Y + CHAR_HEIGHT + 1, 0, 176);
  set_fg_color(COLOR_BLACK);

  n_clear(a);
};