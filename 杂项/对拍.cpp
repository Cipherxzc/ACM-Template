#include<iostream>
using namespace std;

int main(){
    int cnt=0;
    while (1){ //一直循环，直到找到不一样的数据
        system("data.exe > in");
        system("test.exe < in > A.txt");
        system("std.exe < in > B.txt");
        cnt++;
        if (system("fc A.txt B.txt")){ //当 fc 返回 1 时，说明这时数据不一样
            cout<<"test "<<cnt<<" WA\n"; //不一样就跳出循环
            break;
        }                       
        else cout<<"test "<<cnt<<" AC\n";
    }
    return 0;
}