#include <iostream>

#include "Graphlist.h"
#include "Stack.h"
#include "Subway.h"
#include "Dist.h"
#include "MinHeap.h"

#define VISITED 1
#define UNVISITED -2
#define INFINITY 1000000.0

using namespace std;

void Dijkstra(GraphList<string> * &G, int s, Dist * & D);
void my_print(GraphList<string> * &G, int s, Dist * & D, subway * & mySubway);
void initial(GraphList<string> * &G, subway * &mySubway);

//构造图的初始函数
void initial(GraphList<string> * &G, subway * &mySubway) {
    int all_Node_Num = 0;
    //构建所有结点，换乘站信息没加入
    for (int i = 0; i < mySubway->all_Line_Num(); i++) {                                            //遍历整个地铁所有站，为图初始化
        for (int j = 0; j < mySubway->line_Station_Num(i); j++) {                                   //可能会有换乘站点被重复设置, 但是没关系，要把它同线的相邻边设置好
            if(!G->is_Station_Repeat(all_Node_Num, mySubway->line_station_name(i, j))) {            //只有没重复的结点才会加入，重复结点不加入
                G->SetNode(all_Node_Num, mySubway->line_station_name(i, j), i);                     //设置节点信息，包括 编号->1 站点名称->2 线路编号->3
                all_Node_Num++;
            }
        }
    }

/*    cout << all_Node_Num << '\n';
    for (int i = 0; i < all_Node_Num; i++) {
        cout << G->VisitNode(i) << '\n';
    }*/

    //现在将各线路的边加入到图中
    for (int i = 0; i < mySubway->all_Line_Num(); i++) {
        for (int j = 0; j < mySubway->line_Station_Num(i) - 1; j++) {
            //返回要插入边两边结点的编号值
            int from = G->node_rank_ret(mySubway->line_station_name(i,j), all_Node_Num);
            int to = G->node_rank_ret(mySubway->line_station_name(i,j+1), all_Node_Num);
            G->setEdge(from, to, mySubway->distance_ret(i,j));
            G->setEdge(to, from, mySubway->distance_ret(i,j));                      //无向图 所以两个方向都要加进去
        }
    }
    //现在将所有换乘站信息加入到图中
    for (int i = 0; i < mySubway->transfer_Station_Num(); i++) {
        if(mySubway->transfer_num_one_station(i) == 2) {
            // 先通过第i个换乘站得到换乘站名称，在通过换乘站名称得到换乘站的编号
            G->SetNode(G->node_rank_ret(mySubway->transfer_station_name_ret(i), all_Node_Num), 2,mySubway->transfer_num_one_station_line(i,0), mySubway->transfer_num_one_station_line(i, 1));
        }
        else if(mySubway->transfer_num_one_station(i) == 3) {
            G->SetNode(G->node_rank_ret(mySubway->transfer_station_name_ret(i), all_Node_Num), 3, mySubway->transfer_num_one_station_line(i,0), mySubway->transfer_num_one_station_line(i, 1), mySubway->transfer_num_one_station_line(i, 2));
        }
    }

    G->SetNumVertex(all_Node_Num);              //将结点数设置到图中
}


//Dijkstra算法，求两点之间的最短路径
void Dijkstra(GraphList<string> * &G, int s, Dist * & D) {
    for (int i = 0; i < G->VerticesNum(); i++) {
        G->Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = INFINITY;
        D[i].pre = s;
    }
    D[s].length = 0;
    MinHeap<Dist> *H = new MinHeap<Dist>(G->EdgesNum());
    H->Insert(D[s]);
    for (int i = 0; i < G->VerticesNum(); i++) {
        bool FOUND = false;
        Dist d;
        while(!H->isEmpty()) {
            d = H->RemoveMin();
            if(G->Mark[d.index] == UNVISITED) {
                FOUND = true;
                break;
            }
        }
        if(!FOUND) break;
        int v = d.index;
        G->Mark[v] = VISITED;
        for (Edge e = G->FirstEdge(v); G->isEdge(e); e = G->NextEdge(e)) {
            if(D[G->ToVertex(e)].length > (D[v].length + G->Weight(e))) {
                D[G->ToVertex(e)].pre = v;
                D[G->ToVertex(e)].length = D[v].length + G->Weight(e);
                H->Insert(D[G->ToVertex(e)]);
            }
        }
    }
}

void search(int from, int to, Dist * & D, subway * & mySubway, GraphList<string> * &G) {
    Stack<int> my_stack;
    int temp = to;
    while(D[temp].pre != from) {
        my_stack.push(D[temp].pre);
        temp = D[temp].pre;
    }
    cout << G->VisitNode(from) << " -> ";
    while(!my_stack.isEmpty()) {
        temp = my_stack.top(); my_stack.pop();
        cout << G->VisitNode(temp) << " -> ";
    }
    cout << G->VisitNode(to)<< " length = " << D[to].length << " money: " <<mySubway->ticket_cost_ret(D[to].length) << endl;
}
//打印某一站点到其他站点的最短length以及路线
void my_print(GraphList<string> * &G, int s, Dist * & D, subway * & mySubway) {
    Stack<int> myStack;
    for (int i = 0; i < G->VerticesNum(); i++) {
        //cout << 'v' << i << ' ' << D[i].pre << endl;
        if(i == s) continue;
       // if(D[i].length == INFINITY) {
        //      cout << G->node_rank_ret(i) << i << ": 到达不了" << endl;
       // }

        if(D[i].length != INFINITY){
            int j = i;
            while(D[j].pre != s) {
                myStack.push(D[j].pre);
                j = D[j].pre;
            }
            cout << G->VisitNode(s) << " -> ";
            while(!myStack.isEmpty()) {
                j = myStack.top(); myStack.pop();
                cout << G->VisitNode(j) << " -> ";
            }
            cout << G->VisitNode(i)<< " length = " << D[i].length  << " money: " <<mySubway->ticket_cost_ret(D[i].length) << endl;
        }
    }
}


bool operator < (Dist& m1, Dist const &m2) {
    if(m1.length < m2.length) return true;
    else return false;
}           //重载运算符
bool operator > (Dist& m1, Dist const &m2) {
    if(m1.length > m2.length) return true;
    else return false;
}           //重载运算符



int main() {
    auto * G = new GraphList<string>(500);
    auto * mySubway = new subway(20,50);

    mySubway->readFile();               //将文件内的信息读入到subway类内，方便以后操作
//    mySubway->print_all_line_info();
//    mySubway->print_all_transfer_info();
    string s, end;
    int rank1, rank2;
    cin >> s >> end;

    initial(G, mySubway);
    rank1 = G->node_rank_ret(s,G->VerticesNum());
    rank2 = G->node_rank_ret(end,G->VerticesNum());
    if(rank1 == -1) {
        cout << "没有此站" << endl;
    }
    else {
        auto * D = new Dist[G->VerticesNum()];
        Dijkstra(G, rank1 , D);
        search(rank1, rank2, D, mySubway, G);
        my_print(G, rank1, D, mySubway);
    }


    return 0;
}