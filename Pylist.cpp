#include <iostream>
using namespace std;


template <typename T> class Node{
public:
    T data;
    Node<T>* next;
    Node<T>* pre;
};

template <typename T> class Pylist{
private:
    Node<T>* head;
    Node<T>* tail;
    int len;
public:
    Pylist(){                //tail和head必须先定义
        tail = new Node<T>;
        head = new Node<T>;
        tail->next = NULL;
        tail->pre = head;
        head->next = tail;
        head->pre = NULL;
        len = 0;
    }

    Pylist(initializer_list<T> vlist){     //不定数量节点构造
    tail = new Node<T>;
    head = new Node<T>;
    head->next = tail;
    head->pre = NULL;
    tail->next = NULL;
    tail->pre = head;
    len = 0;
    Node<T>* p = head;
    for (T v :vlist){
        while (p->next != tail){
            p = p->next;
        }
        Node<T>* q = new Node<T>;
        q->data = v;
        q->next = tail;
        tail->pre = q;
        q->pre = p;
        p->next = q;
        len++;
        }
    }

    Pylist(Pylist& other){    //复制构造函数，重载运算+需要，默认重载是二进制拷贝
        tail = new Node<T>;
        head = new Node<T>;
        head->next = tail;
        head->pre = NULL;
        tail->next = NULL;
        tail->pre = head;
        len = 0;
        for (auto v : other){
            append(v);
        }
    }

    ~Pylist(){
        Node<T>* p = head;
        while (p != tail){
            Node<T>* q = p->next;
            delete p;
            p = q;
        }
    }

    class Iterator{
        private:
        Node<T>* node_;

        public:
        Iterator(Node<T>* node): node_(node){}     //初始化

        Iterator& operator++(){
            node_ = node_->next;
            return *this;
        }

        Iterator operator++(int){   //后置递增运算，int不会被使用，只是一个标记表示后增
            Iterator tmp = *this;
            node_ = node_->next;
            return tmp;
        }

        Iterator& operator--(){
            node_ = node_->pre;
            return *this;
        }

        Iterator operator--(int){     //后置递减运算
            Iterator tmp = *this;
            node_ = node_->pre;
            return tmp;
        }

        T& operator*() const{      //解引用迭代器
            return node_->data;
        }

        bool operator==(const Iterator& other) const{    //比较两个迭代器
            return node_ == other.node_;
        }

        bool operator!=(const Iterator& other) const{
            return !(*this == other);
        }
    };

    Iterator begin(){
        return Iterator(head->next);
    }
    Iterator begin() const{
        return Iterator(head->next);
    }

    Iterator end(){
        return Iterator(tail);
    }

    Iterator end() const{
        return Iterator(tail);
    }

    Iterator rbegin(){
        return Iterator(tail->pre);
    }

    Iterator rbegin() const{
        return Iterator(tail->pre);
    }

    Iterator rend(){
        return Iterator(head);
    }

    Iterator rend() const{
        return Iterator(head);
    }

    bool insert(int i, T data){
        if (i < 0 || i > len){
            return false;
        }
        Node<T>* p = head;
        for (int j = 0; j < i; j++){
            p = p->next;
        }
        Node<T>* q = new Node<T>;
        q->data = data;
        q->next = p->next;
        p->next->pre = q;
        q->pre = p;
        p->next = q;
        len++;
        return true;
    }

    bool append(T data){
        Node<T>* p = head;
        while(p->next != tail){
            p = p->next;
        }
        Node<T>* q = new Node<T>;
        q->data = data;
        q->next = tail;
        tail->pre = q;
        q->pre = p;
        p->next = q;
        len++;
        return true;
    }

    T& operator[](int index){             //运算符[]重载
        if (index < 0 || index >= len){
            throw std::out_of_range("Index out of range");
        }
        Node<T>* p = head->next;
        for (int i = 0; i < index; i++){
            p = p->next;
        }
        return p->data;
    }

    const T& operator[](int index) const{
        if (index < 0 || index >= len){
            throw std::out_of_range("Index out of range");
        }
        Node<T>* p = head->next;
        for (int i = 0; i < index; i++){
            p = p->next;
        }
        return p->data;
    }

    Pylist operator+(const Pylist& other){    //运算符+重载，需要赋值=重载
        Pylist res = *this;
        for (auto v :other){
            res.append(v);
        }
        return res;
    }

    Pylist& operator+=(const Pylist& other){
        for (auto v : other){
            append(v);
        }
        return *this;
    }


    Pylist& operator=(const Pylist& other){   //必须是const
        if (this != &other){
            Node<T>* p = head->next;    //不能删除头节点
            while (p != tail){
                Node<T>* q = p->next;
                delete p;
                p = q;
            }
            head->next = tail;
            tail->pre = head;
            len = 0;
            for (auto v : other){
                append(v);
            }
        }
        return *this;
    }

    T pop(){
        Node<T>* p = tail->pre;
        Node<T>* tmp = p->pre;
        T q;
        q = p->data;
        tmp->next = tail;
        tail->pre = tmp;
        delete p;
        len--;
        return q;
    }

    T pop(int i){
        Node<T>* p = head;
        T tmp = (T)NULL;
        if (i < 0 || i>= len){
            throw std::out_of_range("Index out of range");
        }else{
            for (int j = 0; j <= i; j++){
                p = p->next;
            }
            tmp = p->data;
            Node<T>* q = p->next;
            q->pre = p->pre;
            p->pre->next = q;
            len--;
        }
        return tmp;
    }

    bool remove(int i){
        if (i < 0 || i >= len){
            return false;
        }
        Node<T>* p = head;
        for (int j = 0; j < i; j++){
            p = p->next;
        }
        Node<T>* q = p->next;
        p->next = q->next;
        q->next->pre = p;
        delete q;
        len--;
        return true;
    }

    size_t length() const{
        return len;
    }

    T get(int i) const{
        if (i < 0 || i >= len) {
            return false;
        }
        Node<T>* p = head->next;
        for (int j = 0; j < i; j++){
            p = p->next;
        }
        T data = p->data;
        return data;
    }
    
};

int main(){
    Pylist<int> a = {1, 2}, b = {3, 4}, c;
    c = a + b;
    cout << c[0] << endl;
    for (auto it=c.rbegin(); it!=c.rend(); --it) std::cout << *it << " ";
    a += b;
    for (auto it=a.begin(); it!=a.end(); it++) std::cout << *it << " ";
}


/*
int main(){

    Pylist<int> L;
    int f;
    for (int i=0; i<3; ++i) L.append(i+1);
    Pylist<int> oth = {4, 5};
    L = L + oth;
    L += {6, 7};
    L[6] = 8;
    L.insert(6, 7);
    L.append(9);
    f = L.pop();
    cout << f <<endl;
    L += {9, 10};
    L.pop(9);
    for(auto it=L.begin();it!=L.end();it++){
        std::cout << *it << endl;
    }
    for(auto it=L.rbegin();it!=L.rend();--it){
        std::cout << *it << endl;
    }
    Pylist<char> cl = {'a', 'b', 'c'};
    cout << cl[0] << endl;
    cout << "len = " << L.length() << endl;
}
*/