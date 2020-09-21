#include <string>

using std::string;

//地铁线路相关数据结构体声明
struct line_info
{
    string line_name;               //线路名称
    int line_station_num;           //线路含站总数
    string station_name_arr[50];    //各站名称
    double distance_arr[50];        //各站之间距离
};

//换乘车站信息结构体声明
struct tranfer_station_info
{
    string station_name;        //该换乘车站名称
    int transfer_line_num;      //该换乘车站可以换乘的线路总数
    int tranfer_arr[10];        //储存可换乘线路标号
};

class subway {
    private:
        tranfer_station_info * tranfer_station;
        line_info * line_arr;
        int all_line_num;
        int transfer_station_num;
    public:
        subway(int line_n, int tranfer_station_n);      //需要输入最大线路数，最大换乘总数，创建结构体数组
        ~subway();
        void readFile(string s);
        int all_Line_Num();
        int line_Station_Num(int i);
        string line_name(int i);
        string line_station_name(int i, int j);
        double line_two_station_distance(int line, string n1, string n2);
        void print_all_line_info();
        void print_all_transfer_info();
};