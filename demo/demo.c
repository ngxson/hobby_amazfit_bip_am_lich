#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct app_data_ {
  void*   ret_f;          //  the address of the return function
  int     index;          //  the current index on database
  int     last_half;      //  if true => showing last half of month
  int     month;
  int     year;
  char    buffer[21];
  int     cursor;
};



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
  sprintf(&text_buffer[0], "%2.0d", n);
  n_write(a, text_buffer, 2);
}



char database[][4] = {
  {14, 11, 79, 2},
  {15, 12, 79, 5},
  {15, 1, 80, 6},
  {16, 2, 80, 2},
  {17, 3, 80, 4},
  {19, 4, 80, 0},
  {19, 5, 80, 2},
  {21, 6, 80, 5},
  {22, 7, 80, 1},
  {23, 8, 80, 3},
  {24, 9, 80, 6},
  {24, 10, 80, 1},
  {26, 11, 80, 4},
  {27, 12, 80, 0},
  {25, 1, 81, 0},
  {27, 2, 81, 3},
  {27, 3, 81, 5},
  {29, 4, 81, 1},
  {30, 5, 81, 3},
  {2, 7, 81, 6},
  {4, 8, 81, 2},
  {4, 9, 81, 4},
  {5, 10, 81, 0},
  {6, 11, 81, 2},
  {7, 12, 81, 5},
  {8, 1, 82, 1},
  {6, 2, 82, 1},
  {8, 3, 82, 4},
  {8, 4, 82, 6},
  {10, 4, 82, 2},
  {11, 5, 82, 4},
  {12, 6, 82, 0},
  {14, 7, 82, 3},
  {15, 8, 82, 5},
  {16, 9, 82, 1},
  {17, 10, 82, 3},
  {18, 11, 82, 6},
  {19, 12, 82, 2},
  {17, 1, 83, 2},
  {18, 2, 83, 5},
  {19, 3, 83, 0},
  {20, 4, 83, 3},
  {21, 5, 83, 5},
  {23, 6, 83, 1},
  {24, 7, 83, 4},
  {25, 8, 83, 6},
  {27, 9, 83, 2},
  {27, 10, 83, 4},
  {29, 11, 83, 0},
  {30, 12, 83, 3},
  {29, 1, 84, 4},
  {1, 3, 84, 0},
  {1, 4, 84, 2},
  {3, 5, 84, 5},
  {3, 6, 84, 0},
  {5, 7, 84, 3},
  {6, 8, 84, 6},
  {7, 9, 84, 1},
  {9, 10, 84, 4},
  {9, 11, 84, 6},
  {11, 12, 84, 2},
  {12, 1, 85, 5},
  {10, 2, 85, 5},
  {12, 2, 85, 1},
  {12, 3, 85, 3},
  {13, 4, 85, 6},
  {14, 5, 85, 1},
  {15, 6, 85, 4},
  {17, 7, 85, 0},
  {17, 8, 85, 2},
  {19, 9, 85, 5},
  {20, 10, 85, 0},
  {21, 11, 85, 3},
  {23, 12, 85, 6},
  {21, 1, 86, 6},
  {23, 2, 86, 2},
  {23, 3, 86, 4},
  {24, 4, 86, 0},
  {25, 5, 86, 2},
  {26, 6, 86, 5},
  {27, 7, 86, 1},
  {28, 8, 86, 3},
  {29, 9, 86, 6},
  {1, 11, 86, 1},
  {2, 12, 86, 4},
  {4, 1, 87, 0},
  {2, 2, 87, 0},
  {4, 3, 87, 3},
  {4, 4, 87, 5},
  {6, 5, 87, 1},
  {6, 6, 87, 3},
  {7, 7, 87, 6},
  {9, 7, 87, 2},
  {9, 8, 87, 4},
  {10, 9, 87, 0},
  {11, 10, 87, 2},
  {12, 11, 87, 5},
  {14, 12, 87, 1},
  {14, 1, 88, 2},
  {15, 2, 88, 5},
  {16, 3, 88, 0},
  {17, 4, 88, 3},
  {18, 5, 88, 5},
  {19, 6, 88, 1},
  {21, 7, 88, 4},
  {21, 8, 88, 6},
  {22, 9, 88, 2},
  {23, 10, 88, 4},
  {24, 11, 88, 0},
  {25, 12, 88, 3},
  {24, 1, 89, 3},
  {25, 2, 89, 6},
  {26, 3, 89, 1},
  {28, 4, 89, 4},
  {28, 5, 89, 6},
  {1, 7, 89, 2},
  {2, 8, 89, 5},
  {2, 9, 89, 0},
  {4, 10, 89, 3},
  {4, 11, 89, 5},
  {5, 12, 89, 1},
  {6, 1, 90, 4},
  {5, 2, 90, 4},
  {6, 3, 90, 0},
  {7, 4, 90, 2},
  {9, 5, 90, 5},
  {9, 5, 90, 0},
  {11, 6, 90, 3},
  {13, 7, 90, 6},
  {13, 8, 90, 1},
  {15, 9, 90, 4},
  {15, 10, 90, 6},
  {16, 11, 90, 2},
  {17, 12, 90, 5},
  {15, 1, 91, 5},
  {17, 2, 91, 1},
  {17, 3, 91, 3},
  {19, 4, 91, 6},
  {20, 5, 91, 1},
  {21, 6, 91, 4},
  {23, 7, 91, 0},
  {24, 8, 91, 2},
  {25, 9, 91, 5},
  {26, 10, 91, 0},
  {27, 11, 91, 3},
  {28, 12, 91, 6},
  {27, 1, 92, 0},
  {29, 2, 92, 3},
  {29, 3, 92, 5},
  {1, 5, 92, 1},
  {2, 6, 92, 3},
  {3, 7, 92, 6},
  {5, 8, 92, 2},
  {6, 9, 92, 4},
  {7, 10, 92, 0},
  {8, 11, 92, 2},
  {9, 12, 92, 5},
  {10, 1, 93, 1},
  {9, 2, 93, 1},
  {10, 3, 93, 4},
  {10, 3, 93, 6},
  {12, 4, 93, 2},
  {12, 5, 93, 4},
  {14, 6, 93, 0},
  {15, 7, 93, 3},
  {16, 8, 93, 5},
  {18, 9, 93, 1},
  {18, 10, 93, 3},
  {20, 11, 93, 6},
  {21, 12, 93, 2},
  {20, 1, 94, 2},
  {21, 2, 94, 5},
  {21, 3, 94, 0},
  {22, 4, 94, 3},
  {23, 5, 94, 5},
  {24, 6, 94, 1},
  {26, 7, 94, 4},
  {26, 8, 94, 6},
  {28, 9, 94, 2},
  {29, 10, 94, 4},
  {1, 12, 94, 0},
  {2, 1, 95, 3},
  {1, 2, 95, 3},
  {2, 3, 95, 6},
  {2, 4, 95, 1},
  {4, 5, 95, 4},
  {4, 6, 95, 6},
  {6, 7, 95, 2},
  {7, 8, 95, 5},
  {8, 8, 95, 0},
  {9, 9, 95, 3},
  {10, 10, 95, 5},
  {11, 11, 95, 1},
  {13, 12, 95, 4},
  {12, 1, 96, 5},
  {14, 2, 96, 1},
  {14, 3, 96, 3},
  {16, 4, 96, 6},
  {16, 5, 96, 1},
  {18, 6, 96, 4},
  {19, 7, 96, 0},
  {19, 8, 96, 2},
  {21, 9, 96, 5},
  {21, 10, 96, 0},
  {23, 11, 96, 3},
  {24, 12, 96, 6},
  {23, 1, 97, 6},
  {24, 2, 97, 2},
  {25, 3, 97, 4},
  {26, 4, 97, 0},
  {27, 5, 97, 2},
  {28, 6, 97, 5},
  {30, 7, 97, 1},
  {1, 9, 97, 3},
  {2, 10, 97, 6},
  {2, 11, 97, 1},
  {4, 12, 97, 4},
  {5, 1, 98, 0},
  {3, 2, 98, 0},
  {5, 3, 98, 3},
  {6, 4, 98, 5},
  {7, 5, 98, 1},
  {8, 5, 98, 3},
  {10, 6, 98, 6},
  {11, 7, 98, 2},
  {11, 8, 98, 4},
  {13, 9, 98, 0},
  {13, 10, 98, 2},
  {14, 11, 98, 5},
  {16, 12, 98, 1},
  {14, 1, 99, 1},
  {15, 2, 99, 4},
  {16, 3, 99, 6},
  {18, 4, 99, 2},
  {18, 5, 99, 4},
  {20, 6, 99, 0},
  {22, 7, 99, 3},
  {22, 8, 99, 5},
  {24, 9, 99, 1},
  {24, 10, 99, 3},
  {25, 11, 99, 6},
  {26, 12, 99, 2},
  {26, 1, 0, 3},
  {27, 2, 0, 6},
  {27, 3, 0, 1},
  {29, 4, 0, 4},
  {30, 5, 0, 6},
  {2, 7, 0, 2},
  {4, 8, 0, 5},
  {4, 9, 0, 0},
  {6, 10, 0, 3},
  {6, 11, 0, 5},
  {7, 12, 0, 1},
  {9, 1, 1, 4},
  {7, 2, 1, 4},
  {8, 3, 1, 0},
  {9, 4, 1, 2},
  {10, 4, 1, 5},
  {11, 5, 1, 0},
  {12, 6, 1, 3},
  {14, 7, 1, 6},
  {15, 8, 1, 1},
  {16, 9, 1, 4},
  {17, 10, 1, 6},
  {18, 11, 1, 2},
  {20, 12, 1, 5},
  {18, 1, 2, 5},
  {19, 2, 2, 1},
  {19, 3, 2, 3},
  {21, 4, 2, 6},
  {21, 5, 2, 1},
  {23, 6, 2, 4},
  {24, 7, 2, 0},
  {25, 8, 2, 2},
  {27, 9, 2, 5},
  {27, 10, 2, 0},
  {29, 11, 2, 3},
  {1, 1, 3, 6},
  {29, 1, 3, 6},
  {30, 2, 3, 2},
  {1, 4, 3, 4},
  {2, 5, 3, 0},
  {2, 6, 3, 2},
  {4, 7, 3, 5},
  {5, 8, 3, 1},
  {6, 9, 3, 3},
  {8, 10, 3, 6},
  {8, 11, 3, 1},
  {10, 12, 3, 4},
  {11, 1, 4, 0},
  {11, 2, 4, 1},
  {12, 2, 4, 4},
  {13, 3, 4, 6},
  {14, 4, 4, 2},
  {14, 5, 4, 4},
  {16, 6, 4, 0},
  {17, 7, 4, 3},
  {18, 8, 4, 5},
  {19, 9, 4, 1},
  {20, 10, 4, 3},
  {21, 11, 4, 6},
  {23, 12, 4, 2},
  {21, 1, 5, 2},
  {23, 2, 5, 5},
  {23, 3, 5, 0},
  {25, 4, 5, 3},
  {25, 5, 5, 5},
  {27, 6, 5, 1},
  {28, 7, 5, 4},
  {28, 8, 5, 6},
  {30, 9, 5, 2},
  {1, 11, 5, 4},
  {2, 12, 5, 0},
  {4, 1, 6, 3},
  {2, 2, 6, 3},
  {4, 3, 6, 6},
  {4, 4, 6, 1},
  {6, 5, 6, 4},
  {7, 6, 6, 6},
  {8, 7, 6, 2},
  {9, 7, 6, 5},
  {10, 8, 6, 0},
  {11, 9, 6, 3},
  {11, 10, 6, 5},
  {13, 11, 6, 1},
  {14, 12, 6, 4},
  {13, 1, 7, 4},
  {14, 2, 7, 0},
  {15, 3, 7, 2},
  {16, 4, 7, 5},
  {17, 5, 7, 0},
  {19, 6, 7, 3},
  {20, 7, 7, 6},
  {21, 8, 7, 1},
  {22, 9, 7, 4},
  {22, 10, 7, 6},
  {23, 11, 7, 2},
  {25, 12, 7, 5},
  {24, 1, 8, 6},
  {25, 2, 8, 2},
  {26, 3, 8, 4},
  {28, 4, 8, 0},
  {28, 5, 8, 2},
  {1, 7, 8, 5},
  {2, 8, 8, 1},
  {3, 9, 8, 3},
  {4, 10, 8, 6},
  {5, 11, 8, 1},
  {6, 12, 8, 4},
  {7, 1, 9, 0},
  {5, 2, 9, 0},
  {7, 3, 9, 3},
  {7, 4, 9, 5},
  {9, 5, 9, 1},
  {9, 5, 9, 3},
  {11, 6, 9, 6},
  {13, 7, 9, 2},
  {13, 8, 9, 4},
  {15, 9, 9, 0},
  {15, 10, 9, 2},
  {17, 11, 9, 5},
  {18, 12, 9, 1},
  {16, 1, 10, 1},
  {17, 2, 10, 4},
  {18, 3, 10, 6},
  {19, 4, 10, 2},
  {20, 5, 10, 4},
  {21, 6, 10, 0},
  {23, 7, 10, 3},
  {24, 8, 10, 5},
  {25, 9, 10, 1},
  {26, 10, 10, 3},
  {27, 11, 10, 6},
  {29, 12, 10, 2},
  {27, 1, 11, 2},
  {28, 2, 11, 5},
  {29, 3, 11, 0},
  {30, 4, 11, 3},
  {1, 6, 11, 5},
  {2, 7, 11, 1},
  {4, 8, 11, 4},
  {5, 9, 11, 6},
  {6, 10, 11, 2},
  {7, 11, 11, 4},
  {8, 12, 11, 0},
  {10, 1, 12, 3},
  {9, 2, 12, 4},
  {11, 3, 12, 0},
  {11, 4, 12, 2},
  {12, 4, 12, 5},
  {13, 5, 12, 0},
  {14, 6, 12, 3},
  {16, 7, 12, 6},
  {16, 8, 12, 1},
  {18, 9, 12, 4},
  {18, 10, 12, 6},
  {20, 11, 12, 2},
  {21, 12, 12, 5},
  {20, 1, 13, 5},
  {21, 2, 13, 1},
  {22, 3, 13, 3},
  {23, 4, 13, 6},
  {24, 5, 13, 1},
  {25, 6, 13, 4},
  {26, 7, 13, 0},
  {27, 8, 13, 2},
  {28, 9, 13, 5},
  {29, 10, 13, 0},
  {1, 12, 13, 3},
  {2, 1, 14, 6},
  {1, 2, 14, 6},
  {2, 3, 14, 2},
  {3, 4, 14, 4},
  {4, 5, 14, 0},
  {5, 6, 14, 2},
  {6, 7, 14, 5},
  {8, 8, 14, 1},
  {8, 9, 14, 3},
  {9, 9, 14, 6},
  {10, 10, 14, 1},
  {11, 11, 14, 4},
  {13, 12, 14, 0},
  {11, 1, 15, 0},
  {13, 2, 15, 3},
  {13, 3, 15, 5},
  {15, 4, 15, 1},
  {16, 5, 15, 3},
  {17, 6, 15, 6},
  {19, 7, 15, 2},
  {19, 8, 15, 4},
  {20, 9, 15, 0},
  {20, 10, 15, 2},
  {22, 11, 15, 5},
  {23, 12, 15, 1},
  {23, 1, 16, 2},
  {24, 2, 16, 5},
  {25, 3, 16, 0},
  {26, 4, 16, 3},
  {27, 5, 16, 5},
  {29, 6, 16, 1},
  {1, 8, 16, 4},
  {1, 9, 16, 6},
  {2, 10, 16, 2},
  {3, 11, 16, 4},
  {4, 12, 16, 0},
  {5, 1, 17, 3},
  {4, 2, 17, 3},
  {5, 3, 17, 6},
  {6, 4, 17, 1},
  {7, 5, 17, 4},
  {8, 6, 17, 6},
  {10, 6, 17, 2},
  {11, 7, 17, 5},
  {12, 8, 17, 0},
  {13, 9, 17, 3},
  {14, 10, 17, 5},
  {15, 11, 17, 1},
  {16, 12, 17, 4},
  {14, 1, 18, 4},
  {16, 2, 18, 0},
  {16, 3, 18, 2},
  {18, 4, 18, 5},
  {18, 5, 18, 0},
  {20, 6, 18, 3},
  {22, 7, 18, 6},
  {22, 8, 18, 1},
  {24, 9, 18, 4},
  {25, 10, 18, 6},
  {26, 11, 18, 2},
  {27, 12, 18, 5},
  {25, 1, 19, 5},
  {27, 2, 19, 1},
  {27, 3, 19, 3},
  {28, 4, 19, 6},
  {29, 5, 19, 1},
  {1, 7, 19, 4},
  {3, 8, 19, 0},
  {3, 9, 19, 2},
  {5, 10, 19, 5},
  {6, 11, 19, 0},
  {7, 12, 19, 3},
  {8, 1, 20, 6},
  {8, 2, 20, 0},
  {9, 3, 20, 3},
  {9, 4, 20, 5},
  {10, 4, 20, 1},
  {11, 5, 20, 3},
  {12, 6, 20, 6},
  {14, 7, 20, 2},
  {15, 8, 20, 4},
  {16, 9, 20, 0},
  {17, 10, 20, 2},
  {19, 11, 20, 5},
  {20, 12, 20, 1},
  {18, 1, 21, 1},
  {20, 2, 21, 4},
  {20, 3, 21, 6},
  {21, 4, 21, 2},
  {22, 5, 21, 4},
  {23, 6, 21, 0},
  {25, 7, 21, 3},
  {25, 8, 21, 5},
  {27, 9, 21, 1},
  {27, 10, 21, 3},
  {29, 11, 21, 6},
  {1, 1, 22, 2},
  {29, 1, 22, 2},
  {1, 3, 22, 5},
  {1, 4, 22, 0},
  {3, 5, 22, 3},
  {3, 6, 22, 5},
  {4, 7, 22, 1},
  {6, 8, 22, 4},
  {6, 9, 22, 6},
  {8, 10, 22, 2},
  {8, 11, 22, 4},
  {10, 12, 22, 0},
  {11, 1, 23, 3},
  {10, 2, 23, 3},
  {11, 2, 23, 6},
  {12, 3, 23, 1},
  {14, 4, 23, 4},
  {14, 5, 23, 6},
  {15, 6, 23, 2},
  {17, 7, 23, 5},
  {17, 8, 23, 0},
  {18, 9, 23, 3},
  {19, 10, 23, 5},
  {20, 11, 23, 1},
  {22, 12, 23, 4},
  {21, 1, 24, 5},
  {23, 2, 24, 1},
  {23, 3, 24, 3},
  {25, 4, 24, 6},
  {26, 5, 24, 1},
  {27, 6, 24, 4},
  {29, 7, 24, 0},
  {29, 8, 24, 2},
  {1, 10, 24, 5},
  {1, 11, 24, 0},
  {2, 12, 24, 3},
  {4, 1, 25, 6},
  {2, 2, 25, 6},
  {4, 3, 25, 2},
  {4, 4, 25, 4},
  {6, 5, 25, 0},
  {7, 6, 25, 2},
  {8, 6, 25, 5},
  {10, 7, 25, 1},
  {10, 8, 25, 3},
  {12, 9, 25, 6},
  {12, 10, 25, 1},
  {13, 11, 25, 4},
  {14, 12, 25, 0},
  {13, 1, 26, 0},
  {14, 2, 26, 3},
  {15, 3, 26, 5},
  {16, 4, 26, 1},
  {17, 5, 26, 3},
  {19, 6, 26, 6},
  {20, 7, 26, 2},
  {21, 8, 26, 4},
  {23, 9, 26, 0},
  {23, 10, 26, 2},
  {24, 11, 26, 5},
  {25, 12, 26, 1},
  {24, 1, 27, 1},
  {25, 2, 27, 4},
  {25, 3, 27, 6},
  {27, 4, 27, 2},
  {27, 5, 27, 4},
  {29, 6, 27, 0},
  {1, 8, 27, 3},
  {2, 9, 27, 5},
  {4, 10, 27, 1},
  {4, 11, 27, 3},
  {5, 12, 27, 6},
  {7, 1, 28, 2},
  {6, 2, 28, 3},
  {7, 3, 28, 6},
  {7, 4, 28, 1},
  {9, 5, 28, 4},
  {9, 5, 28, 6},
  {11, 6, 28, 2},
  {13, 7, 28, 5},
  {13, 8, 28, 0},
  {15, 9, 28, 3},
  {16, 10, 28, 5},
  {17, 11, 28, 1},
  {18, 12, 28, 4},
  {17, 1, 29, 4},
  {18, 2, 29, 0},
  {18, 3, 29, 2},
  {20, 4, 29, 5},
  {20, 5, 29, 0},
  {22, 6, 29, 3},
  {23, 7, 29, 6},
  {24, 8, 29, 1},
  {25, 9, 29, 4},
  {26, 10, 29, 6},
  {28, 11, 29, 2},
  {29, 12, 29, 5},
  {28, 1, 30, 5},
  {29, 2, 30, 1},
  {29, 3, 30, 3},
  {1, 5, 30, 6},
  {1, 6, 30, 1},
  {3, 7, 30, 4},
  {4, 8, 30, 0},
  {5, 9, 30, 2},
  {6, 10, 30, 5},
  {7, 11, 30, 0},
  {8, 12, 30, 3},
  {10, 1, 31, 6},
  {9, 2, 31, 6},
  {10, 3, 31, 2},
  {11, 3, 31, 4},
  {12, 4, 31, 0},
  {12, 5, 31, 2},
  {14, 6, 31, 5},
  {15, 7, 31, 1},
  {15, 8, 31, 3},
  {17, 9, 31, 6},
  {17, 10, 31, 1},
  {19, 11, 31, 4},
  {20, 12, 31, 0},
  {20, 1, 32, 1},
  {22, 2, 32, 4},
  {22, 3, 32, 6},
  {24, 4, 32, 2},
  {24, 5, 32, 4},
  {26, 6, 32, 0},
  {27, 7, 32, 3},
  {27, 8, 32, 5},
  {29, 9, 32, 1},
  {29, 10, 32, 3},
  {1, 12, 32, 6},
  {2, 1, 33, 2},
  {1, 2, 33, 2},
  {2, 3, 33, 5},
  {3, 4, 33, 0},
  {5, 5, 33, 3},
  {5, 6, 33, 5},
  {7, 7, 33, 1},
  {8, 8, 33, 4},
  {9, 9, 33, 6},
  {10, 10, 33, 2},
  {10, 11, 33, 4},
  {11, 11, 33, 0},
  {13, 12, 33, 3},
  {11, 1, 34, 3},
  {13, 2, 34, 6},
  {13, 3, 34, 1},
  {15, 4, 34, 4},
  {16, 5, 34, 6},
  {17, 6, 34, 2},
  {19, 7, 34, 5},
  {20, 8, 34, 0},
  {21, 9, 34, 3},
  {21, 10, 34, 5},
  {22, 11, 34, 1},
  {24, 12, 34, 4},
  {22, 1, 35, 4},
  {23, 2, 35, 0},
  {24, 3, 35, 2},
  {25, 4, 35, 5},
  {26, 5, 35, 0},
  {28, 6, 35, 3},
  {29, 7, 35, 6},
  {1, 9, 35, 1},
  {2, 10, 35, 4},
  {2, 11, 35, 6},
  {4, 12, 35, 2},
  {5, 1, 36, 5},
  {4, 2, 36, 6},
  {5, 3, 36, 2},
  {6, 4, 36, 4},
  {7, 5, 36, 0},
  {8, 6, 36, 2},
  {10, 6, 36, 5},
  {11, 7, 36, 1},
  {12, 8, 36, 3},
  {14, 9, 36, 6},
  {14, 10, 36, 1},
  {16, 11, 36, 4},
  {17, 12, 36, 0},
  {15, 1, 37, 0},
  {16, 2, 37, 3},
  {17, 3, 37, 5},
  {18, 4, 37, 1},
  {18, 5, 37, 3},
  {20, 6, 37, 6},
  {22, 7, 37, 2},
  {22, 8, 37, 4},
  {24, 9, 37, 0},
  {25, 10, 37, 2},
  {26, 11, 37, 5},
  {28, 12, 37, 1},
  {26, 1, 38, 1},
  {27, 2, 38, 4},
  {28, 3, 38, 6},
  {29, 4, 38, 2},
  {29, 5, 38, 4},
  {1, 7, 38, 0},
  {3, 8, 38, 3},
  {3, 9, 38, 5},
  {5, 10, 38, 1},
  {6, 11, 38, 3},
  {7, 12, 38, 6},
  {9, 1, 39, 2},
  {7, 2, 39, 2},
  {8, 3, 39, 5},
  {9, 4, 39, 0},
  {10, 5, 39, 3},
  {10, 5, 39, 5},
  {12, 6, 39, 1},
  {13, 7, 39, 4},
  {14, 8, 39, 6},
  {15, 9, 39, 2},
  {16, 10, 39, 4},
};

int main() {
  struct app_data_ *a = malloc(sizeof(struct app_data_));
  a->month = 2;
  a->year = 2021;
  a->buffer[20] = '\0';

  printf("CN T2 T3 T4 T5 T6 T7\n");

  int current_day = 1;
  char nb_days = number_of_days(a->month, a->year);
  char *data = database[get_index(a->month, a->year)];
  char l_day = data[0];
  char l_month = data[1];
  int l_current_day = 1;
  char first_day_of_week = data[3];

  for (char y = 0; y < 6; y++) {
    for (char x = 0; x < 7; x++) {
      if ( ( y == 0 && x < first_day_of_week ) || current_day > nb_days ) {
        n_write(a, "   ", 3);
      } else {
        n_write_number(a, current_day);
        if (x < 6) { n_write(a, " ", 1); }
        current_day++;
      }
    }

    printf("%s\n", a->buffer);
    n_clear(a);

    // lunar date
    for (char x = 0; x < 7; x++) {
      if ( ( y == 0 && x < first_day_of_week ) || l_current_day > nb_days ) {
        n_write(a, "   ", 3);
      } else {
        n_write_number(a, l_day);
        if (x < 6) { n_write(a, " ", 1); }
        l_current_day++;
        l_day = l_day <= 30 ? l_day + 1 : 1;
      }
    }

    printf("%s\n", a->buffer);
    n_clear(a);
  }

  return 0;
}