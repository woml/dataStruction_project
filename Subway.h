//
// Created by 党鸿博 on 2020-09-22.
//

#ifndef DATASTRUCTION_SUBWAY_H
#define DATASTRUCTION_SUBWAY_H


#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::ifstream;

//地铁线路相关数据结构体声明
struct line_info
{
    string line_name;               //线路名称
    int line_station_num;           //线路含站总数   含线总数为 line_station_num-1
    string station_name_arr[50];    //各站名称
    double distance_arr[50];        //各站之间距离
};


//换乘车站信息结构体声明
struct transfer_station_info
{
    string station_name;        //该换乘车站名称
    int transfer_line_num;      //该换乘车站可以换乘的线路总数
    int transfer_arr[10];        //储存可换乘线路标号
};

class subway {
private:
    transfer_station_info * transfer_station;
    line_info * line_arr;
    int all_line_num;
    int transfer_station_num;
public:
    subway(int line_n, int transfer_station_n);      //需要输入最大线路数，最大换乘总数，创建结构体数组
    ~subway();
    void readFile();                                                    //从文件读取地铁信息，作为文件和图的接口
    int all_Line_Num();                                                 //返回共有多少号线
    int line_Station_Num(int i);                                        //返回i号线的站总数
    int transfer_Station_Num();                                         //返回可换乘站总数
    int transfer_num_one_station(int i);                                //返回单个站可换乘线路总数
    int transfer_num_one_station_line(int i, int j);                    //返回i站第j个可换乘线路名称（编号）
    int ticket_cost_ret(double length);                                 //返回该长度需要花费多少RMB
    string transfer_station_name_ret(int i);                            //返回第i个可换乘站的名称
    string line_name(int i);                                            //返回编号为i的线路名称
    string line_station_name(int i, int j);                             //返回i号线的第j站名称
    double line_two_station_distance(int line, string n1, string n2);   //返回line号线的名称为n1和n2的距离
    double distance_ret(int i, int j);                                  //返回i号线第j站和第j+1站之间的距离
    void print_all_line_info();                                         //打印所有线路信息，检验是否存入
    void print_all_transfer_info();                                     //打印所有换乘车站信息，检验是否存入

};

subway :: subway(int line_n, int transfer_station_n) {
    transfer_station = new transfer_station_info[transfer_station_n];
    line_arr = new line_info[line_n];
}

subway :: ~subway() {
    delete [] transfer_station;
    delete [] line_arr;
}

void subway :: readFile() {
    ifstream rf("../BaseSubWayInfo.txt");       //注意clion生成的可执行文件是在cmake-build-debug目录下的，所以要找到该文件 得向上一层

    rf >> all_line_num;

    for (int i = 0; i < all_line_num; i++) {
        rf >> line_arr[i].line_name >> line_arr[i].line_station_num;        //读入线路名称和线路含有车站总数
        for (int j = 0; j < line_arr[i].line_station_num - 1; j++) rf >> line_arr[i].station_name_arr[j] >> line_arr[i].distance_arr[j];    //j的跳出条件-1 因为车站之间距离数比车站数少1
        rf >> line_arr[i].station_name_arr[line_arr[i].line_station_num - 1];     //多读一个车站名称
    }

    rf >> transfer_station_num;

    for (int i = 0; i < transfer_station_num; i++) {
        rf >> transfer_station[i].station_name >> transfer_station[i].transfer_line_num;      //读入换乘车站名称和可换乘线路总数
        for (int j = 0; j < transfer_station[i].transfer_line_num; j++) rf >> transfer_station[i].transfer_arr[j]; //根据可换乘线路总数 读入数组
    }

    rf.close();
}

int subway :: all_Line_Num() {
    return all_line_num;
}

int subway :: line_Station_Num(int i) {
    return line_arr[i].line_station_num;
}

int subway :: transfer_Station_Num() {
    return transfer_station_num;
}

int subway :: transfer_num_one_station(int i) {
    return transfer_station[i].transfer_line_num;
}

int subway ::transfer_num_one_station_line(int i, int j) {
    return  transfer_station[i].transfer_arr[j];
}

int subway :: ticket_cost_ret(double length) {       //返回该长度需要花费多少RMB
    if(0.0 < length && length < 6.0) return 3;
    else if(length < 12.0) return 4;
    else if(length < 22.0) return 5;
    else if(length < 32.0) return 6;
    else if(length < 52.0) return 7;
    else if(length < 72.0) return 8;
    else if(length < 92.0) return 9;
    else return -1;
}

string subway :: line_name(int i) {
    return line_arr[i].line_name;
}

string subway :: line_station_name(int i, int j) {
    return line_arr[i].station_name_arr[j];
}

string subway ::transfer_station_name_ret(int i) {
    return transfer_station[i].station_name;
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

double subway :: distance_ret(int i, int j) {
    return line_arr[i].distance_arr[j];
}

void subway :: print_all_line_info() {
    //检验是否存入 transfer_station 结构体
    cout << all_line_num << '\n';

    for (int i = 0; i < all_line_num; i++) {
        cout << line_arr[i].line_name << ' ' << line_arr[i].line_station_num;
        for (int j = 0; j < line_arr[i].line_station_num - 1; j++) cout << ' ' <<  line_arr[i].station_name_arr[j] << ' ' << line_arr[i].distance_arr[j];
        cout << ' ' << line_arr[i].station_name_arr[line_arr[i].line_station_num - 1] << '\n';
    }
}

void subway :: print_all_transfer_info() {
    //检验是否存入 transfer_station 结构体
    cout << transfer_station_num <<'\n';

    for (int i = 0; i < transfer_station_num; i++) {
        cout << transfer_station[i].station_name << ' ' << transfer_station[i].transfer_line_num;
        for (int j = 0; j < transfer_station[i].transfer_line_num; j++) cout << ' ' << transfer_station[i].transfer_arr[j];
        cout << '\n';
    }
}

#endif //DATASTRUCTION_SUBWAY_H
