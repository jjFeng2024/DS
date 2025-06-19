#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//计算逆序数
int inversionCount(string a){
    int count = 0;
    for (int i = 0; i < a.length(); i++){
        for (int j = i + 1; j < a.length(); j++){
            if (a[i] > a[j]){
                count++;
            }
        }
    }
    return count;
}

//自定义cmp比较函数
bool cmp(string a, string b){
    int count_a = inversionCount(a);
    int count_b = inversionCount(b);
    //如果逆序数不相等，则直接返回大小关系
    if (count_a != count_b){
        return count_a > count_b; 
    }
    return a < b; //如果逆序数相等，则按字典序排序
}

//通用冒泡排序
void bubbleSort(vector<string>& arr){
    int n = arr.size();
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (cmp(arr[j], arr[j + 1])){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

//主函数
int main(){
    int n, m;
    cin >> n >> m;
    vector<string> dna_list(n);
    for (int i = 0; i < n; i++){
        cin >> dna_list[i];
    }
    cout << "排序后的DNA序列为：" << endl;
    //使用冒泡排序对DNA序列进行排序
    bubbleSort(dna_list);

    //输出排序后的DNA序列
    for (int i = 0; i < n; i++){
        cout << dna_list[i] << endl;
    }
    return 0;
}