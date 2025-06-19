#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;
// 查找三个数组中共同的最小元素
int main()
{
    int aNum, bNum, cNum;
    cout << "请输入a数组的个数：";
    cin >> aNum;
    cout << "请输入b数组的个数：";
    cin >> bNum;
    cout << "请输入c数组的个数：";
    cin >> cNum;

    vector<int> a(aNum), b(bNum), c(cNum);

    cout << "请输入数组a的元素：";
    for (int i = 0; i < aNum; ++i) 
        cin >> a[i];

    cout << "请输入数组b的元素：";
    for (int i = 0; i < bNum; ++i) 
        cin >> b[i];

    cout << "请输入数组c的元素：";
    for (int i = 0; i < cNum; ++i) 
        cin >> c[i];

    // 使用unordered_set存储每个数组的元素
    unordered_set<int> set_a(a.begin(), a.end());
    unordered_set<int> set_b(b.begin(), b.end());
    unordered_set<int> set_c(c.begin(), c.end());

    int result = -1;
    for (int i = 0; i < aNum; ++i) {
        int num = a[i];
        // 检查num是否在b和c中
        if (set_b.count(num) && set_c.count(num)) {
            result = num;
            break;
        }
    }

    if (result != -1) {
        // 查找原数组中的位置（从1开始）
        int pos_a = find(a.begin(), a.end(), result) - a.begin() + 1;
        int pos_b = find(b.begin(), b.end(), result) - b.begin() + 1;
        int pos_c = find(c.begin(), c.end(), result) - c.begin() + 1;
        cout << "四个数字分别对应：最小共同元素；数组a中位置；数组b中位置；数组c中位置" << endl;
        cout << result << " " << pos_a << " " << pos_b << " " << pos_c << endl;
    } 
    else {
        cout << "NOT FOUND" << endl;
    }
    return 0;
}