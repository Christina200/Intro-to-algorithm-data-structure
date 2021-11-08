#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "Dlist.h"
#include "Instr.h"
#include <fstream>

//OVERVIEW: class Stack derived from DList.
template<class T>
class Stack : public Dlist<T> {
public:
    void push(T op);
//    MODIFIES: this
//    EFFECTS: add op to the top of Stack.
    T pop();
//    MODIFIES: this.
//    EFFECTS: return the top element of Stack and remove it.
    Stack();
//    EFFECTS: construct an empty Stack.
    Stack(int n,std::istream& is);
//    EFFECTS: construct a Stack has n elements from is.
};
//OVERVIEW: class Queue derived from DList.
template<class T>
class Queue : public Dlist<T>{
public:
    void push_in(T op);
//    MODIFIES: this.
//    EFFECTS: add op tp the end of Queue.
    T pop_out();
//    MODIFIES: this.
//    EFFECTS: return the first element of Stack and remove it.
    Queue();
//    EFFECTS: construct an empty Queue.
    Queue(int m,std::istream& is);
//    EFFECTS: construct a Queue has n elements from is.
};

template<class T>
void Stack<T>::push(T op) {
    T * ptr = new T(op);
    this->insertBack(ptr);
}
template<class T>
T Stack<T>::pop() {
    T * del = this->removeBack();
    T res = * del;
    delete del;
    return res;
}
template<class T>
Stack<T>::Stack() : Dlist<T>(){}
template<class T>
Stack<T>::Stack(int n, std::istream &is) : Dlist<T>(){
    T curr;
    for (int i = 0; i < n; ++i) {
        is >> curr;
        push(curr);
    }
}

template<class T>
void Queue<T>::push_in(T op) {
    T * ptr = new T(op);
    this->insertBack(ptr);
}
template<class T>
T Queue<T>::pop_out() {
    T * del = this->removeFront();
    T res = * del;
    delete del;
    return res;
}
template<class T>
Queue<T>::Queue() : Dlist<T>(){}
template<class T>
Queue<T>::Queue(int m, std::istream &is) : Dlist<T>(){
    T curr{};
    for (int i = 0; i < m; ++i) {
        is >> curr;
        push_in(curr);
    }
}

template<class T>
void ADD(Stack<T> &stack){
//    MODIFIES: this
//    EFFECTS: pop the top two elements and push their sum.
    T a,b,res;
    a = stack.pop();
    b = stack.pop();
    res = a + b;
    stack.push(res);
}

void NOR(Stack<int32_t> &stack){
//    MODIFIES: this
//    EFFECTS: pop the top two elements and push their NOR.
    int32_t a,b,res;
    a = stack.pop();
    b = stack.pop();
    res = ~(a|b);
    stack.push(res);
}

void HALT(Queue<Instr> &queue, Stack<int32_t> &stack,int32_t *memory){
//    EFFECTS: print queue and stack. End the program.
    std::cout<<stack<<std::endl;
    std::cout<<queue<<std::endl;
    for (int i = 0; i < 16; ++i) {
        std::cout<<memory[i]<<" ";
    }
    std::cout<<std::endl;
    exit(0);
}

void IFZ(Queue<Instr> &queue, Stack<int32_t> &stack,int num){
//    MODIFIES: this
//    EFFECTS: When the front of the queue is IFZ n, we first pop up the first element in the stack.
//    If this element is zero, we pop up the following n instructions in the queue.
//    If this element is not zero, we continue executing the next instruction.
    int32_t deter = stack.pop();
    if (deter == 0){
        for (int i = 0; i < num; ++i) {
            queue.pop_out();
        }
    }
}

template<class T>
void LOAD(Stack<T> &stack,T *memory){
//MODIFIES: this.
//EFFECTS: first pop up an element from the stack. This first element is the address.
// Then, we find the value stored at this address and push it into the stack.
    T index = stack.pop();
    T into = memory[index];
    stack.push(into);
}

template<class T>
void STORE(Stack<T> &stack,T *memory){
//    MODIFIES: this.
//    EFFECTS: first pop up two elements. The first element is the address and the second is the value
    T address = stack.pop();
    T info = stack.pop();
    memory[address] = info;
}

template<class T>
void POP(Stack<T> &stack){
//    MODIFIES: this.
//    EFFECTS: pop an element.
    stack.pop();
}

template<class T>
void PUSHI(Stack<T> &stack,T n){
//    MODIFIES: this.
//    EFFECTS: push a constant n into the stack
    stack.push(n);
}

void Operation(Instr &command,Queue<Instr> &queue,Stack<int32_t> &stack,int32_t *memory){
    //EFFECTS: execute corresponding function for each instruction in the queue.
    switch (command.name) {
        case InstrName::ADD:ADD(stack);
            break;
        case InstrName::NOR:NOR(stack);
            break;
        case InstrName::IFZ:IFZ(queue,stack,command.parameter);
            break;
        case InstrName::HALT:HALT(queue,stack,memory);
            break;
        case InstrName::LOAD:LOAD(stack,memory);
            break;
        case InstrName::STORE:STORE(stack,memory);
            break;
        case InstrName::POP:POP(stack);
            break;
        case InstrName::PUSHI:PUSHI(stack,command.parameter);
            break;
        case InstrName::NOOP:
            break;
    }
}

int main(int argc, char *argv[])
{
    //TODO:write your code here.
    //initialize stack, queue, memory array.
    int n,m;
    std::cin>>n>>m;
    Stack<int32_t> stack = Stack<int32_t>(n,std::cin);
    Queue<Instr> queue = Queue<Instr>(m,std::cin);
    auto * memory = new int32_t [16];
    for (int i = 0; i < 16; ++i) {
        std::cin>>memory[i];
    }
    if (!argv[1]){
        //the argument doesn't have "-s".
        while  (!queue.isEmpty()) {
            Instr operation = queue.pop_out();
            std::cout<<operation<<std::endl;
            Operation(operation,queue,stack,memory);
            std::cout<<stack<<std::endl;
            std::cout<<queue<<std::endl;
            for (int i = 0; i < 16; ++i) {
                std::cout<<memory[i]<<" ";
            }
            std::cout<<std::endl;
        }
    }
    else {
        //the argument has "-s".
        while  (!queue.isEmpty()) {
            Instr operation = queue.pop_out();
            if (operation.name != InstrName::HALT)
                Operation(operation,queue,stack,memory);
            else break;
        }
        std::cout<<stack<<std::endl;
        for (int i = 0; i < 16; ++i) {
                std::cout<<memory[i]<<" ";
            }
            std::cout<<std::endl;
    }
    delete [] memory;
    return 0;
}