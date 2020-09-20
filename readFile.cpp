#include <fstream>
#include <string>
#define MAX_LINE_NUM 30

int all_line_num;
std::string line_arr[MAX_LINE_NUM];

std::ifstream rf("BaseSubWayInfo.txt");

rf >> all_line_num;