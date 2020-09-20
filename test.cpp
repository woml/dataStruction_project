#include <iostream>

#define UNVISITED -2
#define VISITED 1
#define INFINITY 1000000

using namespace std;

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
        int EdgesNum();
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

void Visit(GraphList<char>* G, int v);

void dfs_visit(GraphList<char> * G, int v) {
    G->Mark[v] = VISITED;
    Visit(G,v);
    for (Edge e = G->FirstEdge(v); G->isEdge(e); e = G->NextEdge(e)) {
        if(G->Mark[G->ToVertex(e)] == UNVISITED) {
            dfs_visit(G, G->ToVertex(e));
        }
    }
}

void Visit(GraphList<char> * G, int v) {
    cout << G->VisitNode(v) << endl;
    return;
}

void initial(GraphList<char> * G) {
    G->SetNode(0,'a');
    G->SetNode(1,'c');
    G->SetNode(2,'d');
    G->SetNode(3,'e');
    G->SetNode(4,'f');
    G->SetNode(5,'h');
    G->SetNode(6,'k');
    G->setEdge(0,1,1);
    G->setEdge(0,2,1);
    G->setEdge(0,3,1);
    G->setEdge(0,4,1);
    G->setEdge(1,0,1);
    G->setEdge(1,5,1);
    G->setEdge(2,0,1);
    G->setEdge(2,5,1);
    G->setEdge(3,0,1);
    G->setEdge(3,6,1);
    G->setEdge(4,0,1);
    G->setEdge(4,5,1);
    G->setEdge(4,6,1);
    G->setEdge(5,1,1);
    G->setEdge(5,2,1);
    G->setEdge(5,4,1);
    G->setEdge(5,6,1);
    G->setEdge(6,3,1);
    G->setEdge(6,4,1);
    G->setEdge(6,5,1);
}

int main(void) {
    GraphList<char> * G = new GraphList<char>(7);
    initial(G);
    dfs_visit(G,0);

    return 0;
}