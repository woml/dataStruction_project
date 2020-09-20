#include "graphlist.h"
#include "stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#define MAX_LINE_NUM 30

using namespace std;

int all_line_num;
int transfer_station_num;
std::string line_arr[MAX_LINE_NUM];

std::ifstream rf("BaseSubWayInfo.txt");

struct tranfer_station_info
{
    string name;
    int transfer_line_num;
    int tranfer_arr[10];
};

tranfer_station_info tranfer_station[100];



int main(void) {

    rf >> all_line_num;
    rf.get();           // 这里要吃掉一个 '\n'

    for (int i = 0; i < all_line_num; i++) {
        getline(rf, line_arr[i]);
    }

    cout << all_line_num << '\n';

    for (int i = 0; i < all_line_num; i++) {
        cout << i << ' ' << line_arr[i] << '\n';
    }

    rf >> transfer_station_num;
    //rf.get();           // 这里要吃掉一个 '\n'

    for (int i = 0; i < all_line_num; i++) {
        rf >> tranfer_station[i].name;
    }

    rf.close();
    return 0;
}