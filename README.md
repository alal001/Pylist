# Pylist
C++中实现Python风格的list:
参照Python的 List 列表的函数常用功能来实现。如+运算直接将两个列表合并，[] 运算赋值、取值。如 ：
```python
a = [1, 2], b = [4, 5]
a[2] = 3
a += b
c + a + b
```
笔者是很喜欢python中列表这种骚操作的，就在C++中实现它:
```cpp
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
    for(auto it=L.begin(); it!=L.end(); it++){
        std::cout << *it << endl;
    }
    for(auto it=L.rbegin(); it!=L.rend(); --it){
        std::cout << *it << endl;
    }
    cout << "len = " << L.length() << endl;
    
    Pylist<char> cl = {'a', 'b', 'c'};
    cout << cl[0] << endl;
}
```
这浓浓的Python风，就不用解释了吧~