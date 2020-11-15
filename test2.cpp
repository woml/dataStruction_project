#include <iostream>

#define UNVISITED -2
#define VISITED 1
#define INFINITY 1000000

using namespace std;

template <class T>
class Node {
    public:
        T value;
        Node <T> * next;
        
        Node(const T n, Node<T> * nextP = NULL) {
            value = n;
            next = nextP;
        }

};


template <class T>
class Stack {
    private:
        Node <T> * topNode;
        int num;
    public:
        Stack() {
            num = 0;
            topNode = NULL;
        }
        ~Stack() {
            clear();
        }
        void push(const T it);
        bool pop();
        T top();
        bool isEmpty();
        void clear();
};

template <class T>
void Stack<T> :: push(const T it) {
    Node <T> * tep = new Node<T>(it,topNode);
    topNode = tep;
    num++;
}

template <class T>
bool Stack<T> :: pop() {
    Node <T> * tep;
    if(num == 0) return false;
    num--;
    tep = topNode;
    topNode = topNode->next;
    delete tep;

    return true;
}

template <class T>
T Stack<T> :: top() {
    return topNode->value;
}

template <class T>
bool Stack<T> :: isEmpty() {
    if(num == 0) return true;
    return false;
}

template <class T>
void Stack<T> :: clear() {
    Node <T> * tmp;
    while(topNode != NULL) {
        tmp = topNode;
        topNode = topNode->next;
        delete tmp;
    }
    num = 0;
}


class Edge {
    public:
        int from, to, weight;
        Edge() {
            from = to = -1;
            weight = 0;
        }
        Edge(int f, int t, int w) {
            from = f;
            to = t;
            weight = w;
        }
};

class Graph {
    public:
        int numVertex;
        int numEdge;
        int * Mark;
        int * Indegree;
        Graph(int numVert) {
            numVertex = numVert;
            numEdge = 0;
            Indegree = new int[numVertex];
            Mark = new int[numVertex];
            for (int i = 0; i < numVertex; i++) {
                Mark[i] = UNVISITED;
                Indegree[i] = 0;
            }
        }
        ~Graph() {
            delete [] Mark;
            delete [] Indegree;
        }
        int VerticesNum() {
            return numVertex;
        }
        int EdgesNum() {
            return numEdge;
        }
        Edge FirstEdge(int oneVertex);
        Edge NextEdge(Edge preEdge);
        bool setEdge(int fromVertex, int toVertex);
        bool delEdge(int fromVertex, int tovertex);
        bool isEdge(Edge oneEdge);
        int FromVertex(Edge oneEdge) {
            return oneEdge.from;
        }
        int ToVertex(Edge oneEdge) {
            return oneEdge.to;
        }
        int Weight(Edge oneEdge) {
            return oneEdge.weight;
        }
};

bool Graph ::isEdge(Edge oneEdge) {
    if(oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.to >= 0) return true;
    else return false;
}

struct listUnit {
    int vertex;
    int weight;
};

template <class Elem, class T>
class Link {
    private:
        T LinkValue;
    public:
        Elem element;
        Link * next;
        Link(const Elem & elemval, Link * nextval = NULL) {
            element = elemval;
            next = nextval;
        }
        Link(Link * nextval = NULL) {
            next = nextval;
        }
        void SetLinkValue(T v) {
            LinkValue = v;
        }
        T VisitValue() {
            return LinkValue;
        }
};

template <class Elem, class T>
class LList {
    public:
        Link<Elem,T> * head;
        LList() {
            head = new Link<Elem,T>();
        }
};

template <class T>
class GraphList : public Graph {
    private:
        LList <listUnit,T> * graList;
    public:
        GraphList(int numVert):Graph(numVert) {
            graList = new LList <listUnit,T>[numVertex];
        }
        Edge FirstEdge(int oneVertex) {
            Edge myEdge;
            myEdge.from = oneVertex;
            Link<listUnit,T> * temp = graList[oneVertex].head;
            if(temp->next != NULL) {
                myEdge.to = temp->next->element.vertex;
                myEdge.weight = temp->next->element.weight;
            }
            return myEdge;
        }
        Edge NextEdge(Edge preEdge) {
            Edge myEdge;
            myEdge.from = preEdge.from;
            Link <listUnit,T> * temp = graList[preEdge.from].head;
            while(temp->next != NULL && temp->next->element.vertex <= preEdge.to) {
                temp = temp->next;
            }
            if(temp->next != NULL) {
                myEdge.to = temp->next->element.vertex;
                myEdge.weight = temp->next->element.weight;
            }
            return myEdge;
        }
        void setEdge(int from, int to, int weight) {
            Link<listUnit,T> * temp = graList[from].head;
            while(temp->next != NULL && temp->next->element.vertex < to) {
                temp = temp->next;
            }
            if(temp->next == NULL) {
                temp->next = new Link<listUnit,T>;
                temp->next->element.vertex = to;
                temp->next->element.weight = weight;
                numEdge++;
                Indegree[to]++;
                return;
            }
            if(temp->next->element.vertex == to) {
                temp->next->element.weight = weight;
                return;
            }
            if(temp->next->element.vertex > to) {
                Link<listUnit,T> * other = temp->next;
                temp->next = new Link<listUnit,T>;
                temp->next->element.vertex = to;
                temp->next->element.weight = weight;
                temp->next->next = other;
                numEdge++;
                Indegree[to]++;
                return;
            }
        }
        void delEdge(int from, int to) {
            Link<listUnit,T> * temp = graList[from].head;
            while(temp->next != NULL && temp->next->element.vertex < to) {
                temp = temp->next;
            }
            if(temp->next == NULL) return;
            if(temp->next->element.vertex > to) return;
            if(temp->next->element.vertex == to) {
                Link<listUnit,T> * other = temp->next->next;
                delete temp->next;
                temp->next = other;
                numEdge--;
                Indegree[to]--;
                return;
            }
        }
        void SetNode(int i, T v) {
            graList[i].head->SetLinkValue(v);
        }
        T VisitNode(int i) {
            return graList[i].head->VisitValue();
        }
};

class Dist {
    public:
        int index;
        int length;
        int pre;
};

template <class T>
class MinHeap {
    private:
        T * heapArray;
        int CurrentSize;
        int MaxSize;
        void swap(int pos_x,int pos_y) {
            T temp = heapArray[pos_x];
            heapArray[pos_x] = heapArray[pos_y];
            heapArray[pos_y] = temp;
        }
        void BuildHeap() {
            for (int i = CurrentSize/2 - 1; i >= 0; i--) {
                SiftDown(i);
            }
        }
    public:
        MinHeap(const int n) {
            if(n < 0) return;
            CurrentSize = 0;
            MaxSize = n;
            heapArray = new T[MaxSize];
            BuildHeap();
        }
        MinHeap(const int n, T * arr) {
            if(n < 0) return;
            CurrentSize = n;
            MaxSize = n;
            heapArray = new T[MaxSize];
            for (int i = 0; i < n; i++) heapArray[i] = arr[i];
            BuildHeap();
        }
        ~MinHeap() {delete []heapArray;}
        bool isEmpty() {
            return CurrentSize == 0;
        }
        bool isLeaf(int pos) const {
            return (pos >= CurrentSize/2) && (pos < CurrentSize);
        }
        int LeftChild(int pos) const {
            return 2*pos+1;
        }
        int RightChild(int pos) const {
            return 2*pos+2;
        }
        int Parent(int pos) const {
            return (pos-1)/2;
        }
        void Insert(const T & newNode) {
            heapArray[CurrentSize] = newNode;
            SiftUp(CurrentSize);
            CurrentSize++;
        }
        T & RemoveMin() {
            swap(0,--CurrentSize);
            if(CurrentSize > 1) SiftDown(0);
            return heapArray[CurrentSize];
        }
        bool Remove(int pos, T & node) {
            if((pos < 0) || (pos >= CurrentSize)) return false;
            node = heapArray[pos];
            heapArray[pos] = heapArray[--CurrentSize];
            if(heapArray[Parent(pos)] > heapArray[pos]) SiftUp(pos);
            else SiftDown(pos);
            return true;
        }
        void SiftUp(int pos) {
            int temppos = pos;
            T temp = heapArray[temppos];
            while((temppos > 0) && (heapArray[Parent(temppos)] > temp)) {
                heapArray[temppos] = heapArray[Parent(temppos)];
                temppos = Parent(temppos);
            }
            heapArray[temppos] = temp;
        }
        void SiftDown(int pos) {
            int i = pos;
            int j = LeftChild(i);
            T temp = heapArray[i];
            while(j < CurrentSize) {
                if((j < CurrentSize - 1) && (heapArray[j] > heapArray[j+1])) j++;
                if(temp > heapArray[j]) {
                    heapArray[i] = heapArray[j];
                    i = j;
                    j = LeftChild(i);
                }
                else break;
            }
            heapArray[i] = temp;
        }
};

bool operator < (Dist& m1, Dist const &m2) {
    if(m1.length < m2.length) return true;
    else return false;
}
bool operator > (Dist& m1, Dist const &m2) {
    if(m1.length > m2.length) return true;
    else return false;
}


void Dijkstra(GraphList<char> * & G, int s, Dist * & D) {
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

void initial(GraphList<char> * & G) {
    G->SetNode(0,'0');
    G->SetNode(1,'1');
    G->SetNode(2,'2');
    G->SetNode(3,'3');
    G->SetNode(4,'4');
    G->SetNode(5,'5');
    G->setEdge(0,2,10);
    G->setEdge(0,4,30);
    G->setEdge(0,5,100);
    G->setEdge(1,2,5);
    G->setEdge(2,3,50);
    G->setEdge(3,5,10);
    G->setEdge(4,3,20);
    G->setEdge(4,5,60);
}

void print(GraphList<char> * & G, int s, Dist * & D) {
    Stack<int> myStack;
    for (int i = 0; i < G->VerticesNum(); i++) {
        //cout << 'v' << i << ' ' << D[i].pre << endl;
        if(i == s) continue;
        if(D[i].length == INFINITY) {
            cout << 'v' << i << ": 到达不了" << endl;
        }
        else {
            int j = i;
            while(D[j].pre != s) {
                myStack.push(D[j].pre);
                j = D[j].pre;
            }
            cout << 'v' << s << " -> ";
            while(!myStack.isEmpty()) {
                j = myStack.top(); myStack.pop();
                cout << 'v' << j << " -> ";
            }
            cout << 'v' << i << " length = " << D[i].length << endl;
        }
    }
}

int main(void) {
    GraphList<char> * G = new GraphList<char>(6);
    Dist * D = new Dist[G->VerticesNum()];
    initial(G);
    Dijkstra (G,0,D);
    print(G,0,D);
    return 0;
}