#ifndef __AMLICH_UTILS_H__
#define __AMLICH_UTILS_H__

#include "amlich.h"
#include "libbip.h"

char number_of_days(int month, int year) {
  if (month == 1 || month == 3 || month ==  5 || month ==  7 || month ==  8 || month ==  10 || month ==  12) {
    return 31;
  } else if (month == 2) {
    if (
      (
        ( year % 4 == 0 ) && ( year % 100 ) != 0
      )
      || ( year % 400 == 0 )
    ) {
      return 29; // leap year
    } else {
      return 28;
    }
  } else {
    return 30;
  }
}

int get_index(int month, int year) {
  return (year - 1980) * 12 + month - 1;
}

void n_write(struct app_data_ *a, char *txt, int length) {
  for (int i = 0; i < length ; i++) {
    if (a->cursor == 20) {
      break;
    } else {
      a->buffer[a->cursor] = txt[i];
      a->cursor++;
    }
  }
}

void n_clear(struct app_data_ *a) {
  a->cursor = 0;
}

void n_write_number(struct app_data_ *a, char n) {
  char text_buffer[4];
  _sprintf(&text_buffer[0], "%2.0d", n);
  n_write(a, text_buffer, 2);
}

#endif