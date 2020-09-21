#include "graphlist.h"

template <class T>
GraphList<T> :: GraphList(int numVert):Graph(numVert) {
    graList = new LList <listUnit,T>[numVertex];
}

template <class T>
Edge GraphList<T> :: FirstEdge(int oneVertex) {
    Edge myEdge;
    myEdge.from = oneVertex;
    Link<listUnit,T> * temp = graList[oneVertex].head;
    if(temp->next != NULL) {
        myEdge.to = temp->next->element.vertex;
        myEdge.weight = temp->next->element.weight;
    }
    return myEdge;
}

template <class T>
Edge GraphList<T> :: NextEdge(Edge preEdge) {
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

template <class T>
void GraphList<T> :: setEdge(int from, int to, int weight) {
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

template <class T>
void GraphList<T> :: delEdge(int from, int to) {
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

template <class T>
void GraphList<T> :: SetNode(int i, T v, T n) {
    graList[i].head->SetLinkValue(v, n);
}

template <class T>
T GraphList<T> ::  VisitNode(int i) {
    return graList[i].head->VisitValue();
}
