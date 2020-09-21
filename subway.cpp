#include "subway.h"

#include <iostream>
#include <fstream>
#include <cstring>

using std::cout;
using std::ifstream;

subway :: subway(int line_n, int tranfer_station_n) {
    tranfer_station = new tranfer_station_info[tranfer_station_n];
    line_arr = new line_info[line_n];
}

subway :: ~subway() {
    delete [] tranfer_station;
    delete [] line_arr;
}

void subway :: readFile(string s) {
    ifstream rf;
    rf.open(s);

    rf >> all_line_num;

    for (int i = 0; i < all_line_num; i++) {
        rf >> line_arr[i].line_name >> line_arr[i].line_station_num;        //读入线路名称和线路含有车站总数
        for (int j = 0; j < line_arr[i].line_station_num - 1; j++) rf >> line_arr[i].station_name_arr[j] >> line_arr[i].distance_arr[j];    //j的跳出条件-1 因为车站之间距离数比车站数少1
        rf >> line_arr[i].station_name_arr[line_arr[i].line_station_num - 1];     //多读一个车站名称
    }

    rf >> transfer_station_num;

    for (int i = 0; i < transfer_station_num; i++) {
        rf >> tranfer_station[i].station_name >> tranfer_station[i].transfer_line_num;      //读入换乘车站名称和可换乘线路总数
        for (int j = 0; j < tranfer_station[i].transfer_line_num; j++) rf >> tranfer_station[i].tranfer_arr[j]; //根据可换乘线路总数 读入数组
    }

    rf.close();
}

int subway :: all_Line_Num() {
    return all_line_num;
}

int subway :: line_Station_Num(int i) {
    return line_arr[i].line_station_num;
}

string subway :: line_name(int i) {
    return line_arr[i].line_name;
}

string subway :: line_station_name(int i, int j) {
    return line_arr[i].station_name_arr[j];
}

double subway :: line_two_station_distance(int line, string n1, string n2) {
    for (int i = 0; i < line_arr[line].line_station_num - 1; i++) {     
        //可能n1,n2顺序与存入时的顺序相反，所以正反都要检查
        if((line_arr[line].station_name_arr[i].compare(n1) == 0) && (line_arr[line].station_name_arr[i + 1].compare(n2) == 0)) {
            return line_arr[line].distance_arr[i];
        }
        if((line_arr[line].station_name_arr[i].compare(n2) == 0) && (line_arr[line].station_name_arr[i + 1].compare(n1) == 0)) {
            return line_arr[line].distance_arr[i];
        }
    }
    return 0.0; //0.0 代表没找到
}

void subway :: print_all_line_info() {
    //检验是否存入 tranfer_station 结构体
    cout << all_line_num << '\n';

    for (int i = 0; i < all_line_num; i++) {
        cout << line_arr[i].line_name << ' ' << line_arr[i].line_station_num;        
        for (int j = 0; j < line_arr[i].line_station_num - 1; j++) cout << ' ' <<  line_arr[i].station_name_arr[j] << ' ' << line_arr[i].distance_arr[j];    
        cout << ' ' << line_arr[i].station_name_arr[line_arr[i].line_station_num - 1] << '\n';     
    }
}

void subway :: print_all_transfer_info() {
    //检验是否存入 tranfer_station 结构体
    cout << transfer_station_num;
    
    for (int i = 0; i < transfer_station_num; i++) {
        cout << tranfer_station[i].station_name << ' ' << tranfer_station[i].transfer_line_num;
        for (int j = 0; j < tranfer_station[i].transfer_line_num; j++) cout << ' ' << tranfer_station[i].tranfer_arr[j];
        cout << '\n';
    }
}