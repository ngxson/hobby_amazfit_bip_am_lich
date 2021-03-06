#ifndef __APP_TEMPLATE_H__
#define __APP_TEMPLATE_H__

// the data structure for our screen
struct app_data_ {
  void*   ret_f;          //  the address of the return function
  int     index;          //  the current index on database
  int     last_half;      //  if true => showing last half of month
  int     month;
  int     today_month;
  int     year;
  int     today_year;
  int     day;
  char    buffer[21];
  int     cursor;
  char    show_about_us;
  Elf_proc_* proc;
};

// template.c
void   show_screen (void *return_screen);
void   key_press_screen();
int    dispatch_screen (void *param);
void   screen_job();
void   draw_screen(struct app_data_ *a);

#define DATABASE_SIZE 960

/*
  entity[0]               = lunar day of month
  entity[1] & 0x0F        = lunar month
  entity[2] & 0x7F        = lunar year
  entity[2] & 0x80        = is leap month or not
  (entity[1] & 0xF0) >> 4 = day of week
*/
char database[][3] = {
  {14, 43, 79},
  {15, 92, 207},
  {15, 97, 80},
  {16, 34, 208},
  {17, 67, 208},
  {19, 4, 80},
  {19, 37, 208},
  {21, 86, 80},
  {22, 23, 208},
  {23, 56, 80},
  {24, 105, 80},
  {24, 26, 208},
  {26, 75, 80},
  {27, 12, 80},
  {25, 1, 209},
  {27, 50, 81},
  {27, 83, 209},
  {29, 20, 209},
  {30, 53, 209},
  {2, 103, 209},
  {4, 40, 81},
  {4, 73, 81},
  {5, 10, 209},
  {6, 43, 81},
  {7, 92, 81},
  {8, 17, 82},
  {6, 18, 210},
  {8, 67, 82},
  {8, 100, 210},
  {10, 36, 210},
  {11, 69, 82},
  {12, 6, 210},
  {14, 55, 210},
  {15, 88, 82},
  {16, 25, 210},
  {17, 58, 82},
  {18, 107, 82},
  {19, 44, 82},
  {17, 33, 83},
  {18, 82, 211},
  {19, 3, 83},
  {20, 52, 211},
  {21, 85, 211},
  {23, 22, 83},
  {24, 71, 211},
  {25, 104, 211},
  {27, 41, 83},
  {27, 74, 211},
  {29, 11, 83},
  {30, 60, 83},
  {29, 65, 84},
  {1, 3, 84},
  {1, 36, 212},
  {3, 85, 84},
  {3, 6, 212},
  {5, 55, 84},
  {6, 104, 212},
  {7, 25, 212},
  {9, 74, 84},
  {9, 107, 212},
  {11, 44, 84},
  {12, 81, 85},
  {10, 82, 213},
  {12, 18, 85},
  {12, 51, 85},
  {13, 100, 213},
  {14, 21, 85},
  {15, 70, 213},
  {17, 7, 85},
  {17, 40, 213},
  {19, 89, 213},
  {20, 10, 85},
  {21, 59, 213},
  {23, 108, 85},
  {21, 97, 214},
  {23, 34, 86},
  {23, 67, 86},
  {24, 4, 214},
  {25, 37, 86},
  {26, 86, 86},
  {27, 23, 214},
  {28, 56, 86},
  {29, 105, 214},
  {1, 27, 86},
  {2, 76, 214},
  {4, 1, 87},
  {2, 2, 215},
  {4, 51, 87},
  {4, 84, 215},
  {6, 21, 87},
  {6, 54, 87},
  {7, 103, 215},
  {9, 39, 87},
  {9, 72, 87},
  {10, 9, 215},
  {11, 42, 87},
  {12, 91, 215},
  {14, 28, 215},
  {14, 33, 88},
  {15, 82, 216},
  {16, 3, 88},
  {17, 52, 216},
  {18, 85, 88},
  {19, 22, 216},
  {21, 71, 88},
  {21, 104, 88},
  {22, 41, 216},
  {23, 74, 88},
  {24, 11, 88},
  {25, 60, 216},
  {24, 49, 89},
  {25, 98, 217},
  {26, 19, 217},
  {28, 68, 89},
  {28, 101, 217},
  {1, 39, 89},
  {2, 88, 89},
  {2, 9, 217},
  {4, 58, 89},
  {4, 91, 89},
  {5, 28, 89},
  {6, 65, 218},
  {5, 66, 90},
  {6, 3, 218},
  {7, 36, 218},
  {9, 85, 90},
  {9, 5, 218},
  {11, 54, 218},
  {13, 103, 90},
  {13, 24, 218},
  {15, 73, 90},
  {15, 106, 90},
  {16, 43, 90},
  {17, 92, 90},
  {15, 81, 219},
  {17, 18, 91},
  {17, 51, 219},
  {19, 100, 219},
  {20, 21, 91},
  {21, 70, 219},
  {23, 7, 219},
  {24, 40, 91},
  {25, 89, 219},
  {26, 10, 91},
  {27, 59, 91},
  {28, 108, 91},
  {27, 1, 220},
  {29, 50, 92},
  {29, 83, 92},
  {1, 21, 220},
  {2, 54, 92},
  {3, 103, 220},
  {5, 40, 220},
  {6, 73, 92},
  {7, 10, 220},
  {8, 43, 92},
  {9, 92, 92},
  {10, 17, 221},
  {9, 18, 93},
  {10, 67, 93},
  {10, 99, 221},
  {12, 36, 93},
  {12, 69, 221},
  {14, 6, 93},
  {15, 55, 221},
  {16, 88, 221},
  {18, 25, 93},
  {18, 58, 221},
  {20, 107, 93},
  {21, 44, 221},
  {20, 33, 94},
  {21, 82, 94},
  {21, 3, 94},
  {22, 52, 222},
  {23, 85, 94},
  {24, 22, 222},
  {26, 71, 94},
  {26, 104, 222},
  {28, 41, 222},
  {29, 74, 94},
  {1, 12, 94},
  {2, 49, 95},
  {1, 50, 95},
  {2, 99, 95},
  {2, 20, 223},
  {4, 69, 95},
  {4, 102, 223},
  {6, 39, 95},
  {7, 88, 223},
  {8, 8, 95},
  {9, 57, 223},
  {10, 90, 95},
  {11, 27, 223},
  {13, 76, 95},
  {12, 81, 224},
  {14, 18, 96},
  {14, 51, 224},
  {16, 100, 96},
  {16, 21, 224},
  {18, 70, 96},
  {19, 7, 96},
  {19, 40, 224},
  {21, 89, 96},
  {21, 10, 224},
  {23, 59, 96},
  {24, 108, 224},
  {23, 97, 97},
  {24, 34, 225},
  {25, 67, 97},
  {26, 4, 225},
  {27, 37, 97},
  {28, 86, 225},
  {30, 23, 97},
  {1, 57, 97},
  {2, 106, 97},
  {2, 27, 225},
  {4, 76, 97},
  {5, 1, 98},
  {3, 2, 226},
  {5, 51, 226},
  {6, 84, 98},
  {7, 21, 226},
  {8, 53, 226},
  {10, 102, 98},
  {11, 39, 98},
  {11, 72, 226},
  {13, 9, 98},
  {13, 42, 98},
  {14, 91, 226},
  {16, 28, 98},
  {14, 17, 99},
  {15, 66, 227},
  {16, 99, 227},
  {18, 36, 99},
  {18, 69, 227},
  {20, 6, 227},
  {22, 55, 99},
  {22, 88, 227},
  {24, 25, 99},
  {24, 58, 99},
  {25, 107, 99},
  {26, 44, 227},
  {26, 49, 0},
  {27, 98, 0},
  {27, 19, 128},
  {29, 68, 128},
  {30, 101, 128},
  {2, 39, 128},
  {4, 88, 0},
  {4, 9, 128},
  {6, 58, 0},
  {6, 91, 0},
  {7, 28, 128},
  {9, 65, 1},
  {7, 66, 1},
  {8, 3, 129},
  {9, 36, 1},
  {10, 84, 129},
  {11, 5, 1},
  {12, 54, 129},
  {14, 103, 129},
  {15, 24, 1},
  {16, 73, 129},
  {17, 106, 1},
  {18, 43, 129},
  {20, 92, 1},
  {18, 81, 2},
  {19, 18, 2},
  {19, 51, 130},
  {21, 100, 2},
  {21, 21, 130},
  {23, 70, 2},
  {24, 7, 130},
  {25, 40, 130},
  {27, 89, 2},
  {27, 10, 130},
  {29, 59, 2},
  {1, 97, 3},
  {29, 97, 3},
  {30, 34, 3},
  {1, 68, 3},
  {2, 5, 3},
  {2, 38, 131},
  {4, 87, 3},
  {5, 24, 131},
  {6, 57, 131},
  {8, 106, 3},
  {8, 27, 131},
  {10, 76, 3},
  {11, 1, 132},
  {11, 18, 4},
  {12, 66, 132},
  {13, 99, 4},
  {14, 36, 4},
  {14, 69, 132},
  {16, 6, 4},
  {17, 55, 132},
  {18, 88, 4},
  {19, 25, 132},
  {20, 58, 4},
  {21, 107, 132},
  {23, 44, 4},
  {21, 33, 133},
  {23, 82, 5},
  {23, 3, 133},
  {25, 52, 5},
  {25, 85, 133},
  {27, 22, 5},
  {28, 71, 5},
  {28, 104, 133},
  {30, 41, 5},
  {1, 75, 5},
  {2, 12, 133},
  {4, 49, 6},
  {2, 50, 134},
  {4, 99, 6},
  {4, 20, 134},
  {6, 69, 134},
  {7, 102, 6},
  {8, 39, 6},
  {9, 87, 134},
  {10, 8, 6},
  {11, 57, 6},
  {11, 90, 134},
  {13, 27, 6},
  {14, 76, 134},
  {13, 65, 7},
  {14, 2, 135},
  {15, 35, 7},
  {16, 84, 135},
  {17, 5, 135},
  {19, 54, 7},
  {20, 103, 135},
  {21, 24, 7},
  {22, 73, 7},
  {22, 106, 7},
  {23, 43, 135},
  {25, 92, 7},
  {24, 97, 8},
  {25, 34, 136},
  {26, 67, 136},
  {28, 4, 8},
  {28, 37, 136},
  {1, 87, 8},
  {2, 24, 136},
  {3, 57, 8},
  {4, 106, 136},
  {5, 27, 8},
  {6, 76, 8},
  {7, 1, 9},
  {5, 2, 137},
  {7, 51, 9},
  {7, 84, 137},
  {9, 21, 9},
  {9, 53, 137},
  {11, 102, 137},
  {13, 39, 9},
  {13, 72, 137},
  {15, 9, 9},
  {15, 42, 137},
  {17, 91, 9},
  {18, 28, 9},
  {16, 17, 10},
  {17, 66, 138},
  {18, 99, 10},
  {19, 36, 138},
  {20, 69, 10},
  {21, 6, 138},
  {23, 55, 138},
  {24, 88, 10},
  {25, 25, 138},
  {26, 58, 10},
  {27, 107, 138},
  {29, 44, 10},
  {27, 33, 11},
  {28, 82, 139},
  {29, 3, 11},
  {30, 52, 11},
  {1, 86, 11},
  {2, 23, 139},
  {4, 72, 139},
  {5, 105, 11},
  {6, 42, 139},
  {7, 75, 11},
  {8, 12, 139},
  {10, 49, 12},
  {9, 66, 140},
  {11, 3, 12},
  {11, 36, 12},
  {12, 84, 140},
  {13, 5, 12},
  {14, 54, 140},
  {16, 103, 12},
  {16, 24, 140},
  {18, 73, 12},
  {18, 106, 140},
  {20, 43, 12},
  {21, 92, 140},
  {20, 81, 13},
  {21, 18, 141},
  {22, 51, 13},
  {23, 100, 141},
  {24, 21, 13},
  {25, 70, 13},
  {26, 7, 141},
  {27, 40, 13},
  {28, 89, 141},
  {29, 10, 13},
  {1, 60, 13},
  {2, 97, 14},
  {1, 98, 14},
  {2, 35, 142},
  {3, 68, 14},
  {4, 5, 142},
  {5, 38, 14},
  {6, 87, 142},
  {8, 24, 14},
  {8, 57, 14},
  {9, 105, 142},
  {10, 26, 14},
  {11, 75, 142},
  {13, 12, 14},
  {11, 1, 143},
  {13, 50, 15},
  {13, 83, 143},
  {15, 20, 143},
  {16, 53, 15},
  {17, 102, 143},
  {19, 39, 15},
  {19, 72, 15},
  {20, 9, 15},
  {20, 42, 143},
  {22, 91, 15},
  {23, 28, 143},
  {23, 33, 16},
  {24, 82, 144},
  {25, 3, 16},
  {26, 52, 144},
  {27, 85, 144},
  {29, 22, 16},
  {1, 72, 16},
  {1, 105, 16},
  {2, 42, 144},
  {3, 75, 16},
  {4, 12, 16},
  {5, 49, 145},
  {4, 50, 17},
  {5, 99, 145},
  {6, 20, 17},
  {7, 69, 145},
  {8, 102, 145},
  {10, 38, 17},
  {11, 87, 145},
  {12, 8, 17},
  {13, 57, 145},
  {14, 90, 17},
  {15, 27, 17},
  {16, 76, 17},
  {14, 65, 146},
  {16, 2, 18},
  {16, 35, 146},
  {18, 84, 18},
  {18, 5, 146},
  {20, 54, 146},
  {22, 103, 18},
  {22, 24, 146},
  {24, 73, 146},
  {25, 106, 18},
  {26, 43, 18},
  {27, 92, 18},
  {25, 81, 147},
  {27, 18, 19},
  {27, 51, 19},
  {28, 100, 147},
  {29, 21, 19},
  {1, 71, 147},
  {3, 8, 19},
  {3, 41, 147},
  {5, 90, 147},
  {6, 11, 19},
  {7, 60, 19},
  {8, 97, 148},
  {8, 2, 20},
  {9, 51, 20},
  {9, 84, 20},
  {10, 20, 148},
  {11, 53, 20},
  {12, 102, 148},
  {14, 39, 148},
  {15, 72, 20},
  {16, 9, 148},
  {17, 42, 148},
  {19, 91, 20},
  {20, 28, 20},
  {18, 17, 149},
  {20, 66, 21},
  {20, 99, 21},
  {21, 36, 149},
  {22, 69, 21},
  {23, 6, 149},
  {25, 55, 21},
  {25, 88, 149},
  {27, 25, 21},
  {27, 58, 149},
  {29, 107, 21},
  {1, 33, 22},
  {29, 33, 22},
  {1, 83, 22},
  {1, 4, 150},
  {3, 53, 22},
  {3, 86, 22},
  {4, 23, 150},
  {6, 72, 22},
  {6, 105, 150},
  {8, 42, 22},
  {8, 75, 150},
  {10, 12, 22},
  {11, 49, 151},
  {10, 50, 23},
  {11, 98, 151},
  {12, 19, 151},
  {14, 68, 23},
  {14, 101, 23},
  {15, 38, 151},
  {17, 87, 23},
  {17, 8, 23},
  {18, 57, 151},
  {19, 90, 23},
  {20, 27, 151},
  {22, 76, 23},
  {21, 81, 152},
  {23, 18, 24},
  {23, 51, 152},
  {25, 100, 152},
  {26, 21, 24},
  {27, 70, 152},
  {29, 7, 24},
  {29, 40, 24},
  {1, 90, 24},
  {1, 11, 24},
  {2, 60, 152},
  {4, 97, 25},
  {2, 98, 153},
  {4, 35, 25},
  {4, 68, 153},
  {6, 5, 153},
  {7, 38, 25},
  {8, 86, 153},
  {10, 23, 25},
  {10, 56, 153},
  {12, 105, 25},
  {12, 26, 25},
  {13, 75, 25},
  {14, 12, 153},
  {13, 1, 26},
  {14, 50, 154},
  {15, 83, 26},
  {16, 20, 154},
  {17, 53, 154},
  {19, 102, 26},
  {20, 39, 154},
  {21, 72, 154},
  {23, 9, 26},
  {23, 42, 26},
  {24, 91, 26},
  {25, 28, 154},
  {24, 17, 27},
  {25, 66, 27},
  {25, 99, 155},
  {27, 36, 27},
  {27, 69, 155},
  {29, 6, 155},
  {1, 56, 155},
  {2, 89, 155},
  {4, 26, 27},
  {4, 59, 27},
  {5, 108, 155},
  {7, 33, 28},
  {6, 50, 28},
  {7, 99, 28},
  {7, 20, 156},
  {9, 69, 28},
  {9, 101, 156},
  {11, 38, 156},
  {13, 87, 28},
  {13, 8, 156},
  {15, 57, 156},
  {16, 90, 28},
  {17, 27, 28},
  {18, 76, 156},
  {17, 65, 29},
  {18, 2, 29},
  {18, 35, 157},
  {20, 84, 29},
  {20, 5, 157},
  {22, 54, 29},
  {23, 103, 157},
  {24, 24, 29},
  {25, 73, 157},
  {26, 106, 157},
  {28, 43, 29},
  {29, 92, 157},
  {28, 81, 30},
  {29, 18, 30},
  {29, 51, 158},
  {1, 101, 30},
  {1, 22, 158},
  {3, 71, 30},
  {4, 8, 158},
  {5, 41, 30},
  {6, 90, 158},
  {7, 11, 30},
  {8, 60, 158},
  {10, 97, 159},
  {9, 98, 31},
  {10, 35, 159},
  {11, 67, 31},
  {12, 4, 31},
  {12, 37, 159},
  {14, 86, 31},
  {15, 23, 31},
  {15, 56, 159},
  {17, 105, 31},
  {17, 26, 159},
  {19, 75, 31},
  {20, 12, 159},
  {20, 17, 160},
  {22, 66, 32},
  {22, 99, 160},
  {24, 36, 32},
  {24, 69, 160},
  {26, 6, 32},
  {27, 55, 32},
  {27, 88, 160},
  {29, 25, 32},
  {29, 58, 32},
  {1, 108, 32},
  {2, 33, 33},
  {1, 34, 33},
  {2, 83, 161},
  {3, 4, 161},
  {5, 53, 33},
  {5, 86, 161},
  {7, 23, 33},
  {8, 72, 161},
  {9, 105, 33},
  {10, 42, 33},
  {10, 75, 33},
  {11, 11, 161},
  {13, 60, 33},
  {11, 49, 162},
  {13, 98, 34},
  {13, 19, 162},
  {15, 68, 162},
  {16, 101, 34},
  {17, 38, 162},
  {19, 87, 162},
  {20, 8, 34},
  {21, 57, 34},
  {21, 90, 34},
  {22, 27, 162},
  {24, 76, 34},
  {22, 65, 35},
  {23, 2, 163},
  {24, 35, 35},
  {25, 84, 163},
  {26, 5, 163},
  {28, 54, 35},
  {29, 103, 163},
  {1, 25, 35},
  {2, 74, 35},
  {2, 107, 163},
  {4, 44, 35},
  {5, 81, 36},
  {4, 98, 36},
  {5, 35, 164},
  {6, 68, 36},
  {7, 5, 164},
  {8, 38, 164},
  {10, 86, 36},
  {11, 23, 164},
  {12, 56, 164},
  {14, 105, 36},
  {14, 26, 164},
  {16, 75, 36},
  {17, 12, 36},
  {15, 1, 37},
  {16, 50, 165},
  {17, 83, 37},
  {18, 20, 37},
  {18, 53, 165},
  {20, 102, 165},
  {22, 39, 37},
  {22, 72, 165},
  {24, 9, 165},
  {25, 42, 37},
  {26, 91, 165},
  {28, 28, 37},
  {26, 17, 38},
  {27, 66, 166},
  {28, 99, 38},
  {29, 36, 38},
  {29, 69, 166},
  {1, 7, 166},
  {3, 56, 38},
  {3, 89, 166},
  {5, 26, 166},
  {6, 59, 38},
  {7, 108, 166},
  {9, 33, 39},
  {7, 34, 39},
  {8, 83, 167},
  {9, 4, 39},
  {10, 53, 39},
  {10, 85, 167},
  {12, 22, 39},
  {13, 71, 167},
  {14, 104, 39},
  {15, 41, 167},
  {16, 74, 167},
  {18, 11, 39},
  {19, 60, 167},
  {19, 65, 40},
  {20, 2, 168},
  {21, 35, 40},
  {22, 84, 40},
  {22, 5, 168},
  {24, 54, 40},
  {25, 103, 168},
  {26, 24, 40},
  {27, 73, 40},
  {27, 106, 168},
  {29, 43, 40},
  {1, 81, 41},
  {29, 81, 169},
  {1, 19, 169},
  {2, 52, 41},
  {3, 101, 169},
  {4, 22, 41},
  {5, 71, 169},
  {7, 8, 41},
  {7, 41, 41},
  {8, 90, 41},
  {8, 11, 169},
  {10, 60, 41},
  {11, 97, 170},
  {10, 98, 42},
  {11, 34, 170},
  {12, 67, 170},
  {14, 4, 42},
  {14, 37, 170},
  {16, 86, 42},
  {17, 23, 170},
  {18, 56, 42},
  {19, 105, 42},
  {19, 26, 170},
  {21, 75, 42},
  {22, 12, 42},
  {20, 1, 171},
  {22, 50, 43},
  {22, 83, 171},
  {24, 20, 171},
  {25, 53, 43},
  {26, 102, 171},
  {28, 39, 171},
  {29, 72, 43},
  {30, 9, 43},
  {1, 43, 43},
  {2, 92, 43},
  {3, 17, 44},
  {2, 34, 172},
  {4, 83, 44},
  {4, 4, 172},
  {6, 53, 172},
  {7, 86, 44},
  {8, 23, 172},
  {10, 71, 172},
  {11, 104, 44},
  {12, 41, 172},
  {13, 74, 44},
  {14, 11, 44},
  {15, 60, 44},
  {13, 49, 45},
  {14, 98, 173},
  {15, 19, 45},
  {16, 68, 173},
  {17, 101, 173},
  {19, 38, 45},
  {20, 87, 173},
  {21, 8, 173},
  {23, 57, 45},
  {23, 90, 173},
  {25, 27, 45},
  {26, 76, 45},
  {24, 65, 46},
  {25, 2, 174},
  {26, 35, 46},
  {27, 84, 174},
  {28, 5, 46},
  {29, 54, 174},
  {1, 104, 174},
  {2, 25, 174},
  {4, 74, 46},
  {4, 107, 174},
  {6, 44, 46},
  {7, 81, 47},
  {5, 82, 175},
  {7, 19, 47},
  {7, 52, 47},
  {8, 101, 175},
  {9, 21, 47},
  {10, 70, 175},
  {12, 7, 47},
  {12, 40, 175},
  {14, 89, 175},
  {15, 10, 47},
  {16, 59, 175},
  {18, 108, 47},
  {17, 1, 176},
  {19, 50, 48},
  {19, 83, 48},
  {20, 20, 176},
  {21, 53, 48},
  {22, 102, 48},
  {23, 39, 176},
  {24, 72, 48},
  {25, 9, 176},
  {26, 42, 176},
  {28, 91, 48},
  {29, 28, 176},
  {28, 17, 49},
  {29, 66, 177},
  {30, 99, 177},
  {2, 37, 49},
  {2, 70, 49},
  {3, 7, 177},
  {5, 56, 49},
  {5, 89, 177},
  {7, 26, 49},
  {7, 59, 49},
  {8, 108, 177},
  {10, 33, 178},
  {9, 34, 50},
  {10, 83, 178},
  {11, 3, 50},
  {12, 52, 178},
  {13, 85, 50},
  {14, 22, 178},
  {16, 71, 50},
  {16, 104, 50},
  {17, 41, 178},
  {18, 74, 50},
  {19, 11, 50},
  {20, 60, 178},
  {19, 49, 179},
  {21, 98, 51},
  {21, 19, 179},
  {23, 68, 51},
  {23, 101, 179},
  {25, 38, 179},
  {27, 87, 51},
  {27, 8, 51},
  {28, 57, 179},
  {29, 90, 51},
  {30, 27, 51},
  {1, 65, 52},
  {1, 82, 52},
  {2, 19, 180},
  {3, 52, 180},
  {5, 101, 52},
  {5, 22, 180},
  {7, 71, 180},
  {9, 8, 52},
  {9, 40, 180},
  {11, 89, 52},
  {11, 10, 52},
  {12, 59, 52},
  {13, 108, 180},
  {12, 97, 53},
  {13, 34, 53},
  {13, 67, 181},
  {15, 4, 181},
  {16, 37, 53},
  {17, 86, 181},
  {19, 23, 181},
  {20, 56, 53},
  {21, 105, 181},
  {22, 26, 53},
  {23, 75, 53},
  {24, 12, 53},
  {22, 1, 182},
  {24, 50, 54},
  {24, 83, 182},
  {26, 20, 54},
  {26, 53, 182},
  {28, 102, 54},
  {29, 39, 182},
  {1, 73, 54},
  {2, 10, 182},
  {3, 43, 54},
  {4, 92, 54},
  {5, 17, 183},
  {4, 18, 55},
  {5, 67, 55},
  {5, 100, 183},
  {7, 37, 55},
  {7, 70, 183},
  {9, 6, 55},
  {10, 55, 183},
  {11, 88, 183},
  {13, 25, 55},
  {13, 58, 183},
  {15, 107, 55},
  {16, 44, 183},
  {16, 49, 56},
  {17, 98, 56},
  {17, 19, 184},
  {19, 68, 56},
  {19, 101, 56},
  {20, 38, 184},
  {22, 87, 56},
  {22, 8, 184},
  {24, 57, 184},
  {25, 90, 56},
  {26, 27, 184},
  {28, 76, 56},
  {26, 65, 185},
  {28, 2, 57},
  {28, 35, 185},
  {30, 84, 57},
  {30, 5, 185},
  {2, 55, 57},
  {3, 104, 185},
  {4, 25, 57},
  {5, 74, 185},
  {6, 107, 57},
  {7, 44, 185},
  {9, 81, 58},
  {7, 82, 186},
  {9, 19, 58},
  {9, 52, 186},
  {11, 100, 58},
  {11, 21, 186},
  {13, 70, 58},
  {14, 7, 58},
  {14, 40, 186},
  {16, 89, 58},
  {16, 10, 186},
  {18, 59, 58},
  {19, 108, 186},
  {18, 97, 59},
  {19, 34, 187},
  {20, 67, 59},
  {21, 4, 187},
  {22, 37, 59},
  {23, 86, 187},
  {25, 23, 59},
  {25, 56, 187},
  {27, 105, 59},
  {27, 26, 59},
};

#endif