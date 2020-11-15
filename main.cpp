#include "graphlist.h"
#include "stack.h"
#include "subway.h"
#include <iostream>

using namespace std;

void initial(GraphList<string> * &G, subway * &mySubway) {
    int all_Node_Num = 0;
    for (int i = 0; i < mySubway->all_Line_Num(); i++) {                                            //遍历整个地铁所有站，为图初始化
        for (int j = 0; j < mySubway->line_Station_Num(i); j++) {                                   //可能会有换乘站点被重复设置, 但是没关系，要把它同线的相邻边设置好
            G->SetNode(all_Node_Num, mySubway->line_station_name(i,j), mySubway->line_name(i));     //设置节点信息，包括 编号->1 站点名称->2 线路名称->3
        }
    }

}

int main(void) {

    GraphList<string> * G = new GraphList<string>(500);
    subway * mySubway = new subway(20,50);

    mySubway->readFile("BaseSubWayInfo.txt");               //将文件内的信息读入到subway类内，方便以后操作

    initial(G, mySubway);

    return 0;
}