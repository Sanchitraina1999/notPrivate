#include<iostream>

template<class T>
class StackNode{
    T data;
    StackNode<T> *link;
public:
    StackNode();
    StackNode(T);

    template<class U>
    friend class Stack;
};

template<typename T>
StackNode<T>::StackNode(){
    link=NULL;
}

template<typename T>
StackNode<T>::StackNode(T data){
    this->data=data;
    link=NULL;
}

/**************************************************************************************************/

template<class T>
class Stack{
    StackNode<T> *start;
public:
    Stack();
    void push(T);
    void pop();
    T top();
    bool empty();
};

template<typename T>
Stack<T>::Stack(){
    start=NULL;
}

template<typename T>
void Stack<T>::push(T data){
    StackNode<T> *temp=new StackNode<T>(data);
    if(start==NULL){
        start=temp;
        return;
    }
    temp->link=start;
    start=temp;
}

template<typename T>
void Stack<T>::pop(){
    StackNode<T> *temp;
    if(start==NULL) return;
    temp=start;
    start=start->link;
    temp->link=NULL;
    delete temp;
}

template<typename T>
T Stack<T>::top(){
    return start->data;
}

template<typename T>
bool Stack<T>::empty(){
    return start==NULL;
}
