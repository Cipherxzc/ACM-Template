#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // 各种类的定义 必须引用
#include <ext/pb_ds/hash_policy.hpp> // 哈希表
#include <ext/pb_ds/priority_queue.hpp> // 堆
#include <ext/pb_ds/tree_policy.hpp> // 红黑树
using namespace __gnu_pbds;
using namespace std;
#define LL long long

int n;
gp_hash_table<LL, int> mp;
__gnu_pbds::priority_queue<int> que;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> rbt;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    cout << n << endl;

    return 0;
}