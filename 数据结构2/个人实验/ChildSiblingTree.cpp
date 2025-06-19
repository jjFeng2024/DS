/*任务：基于树的孩子-兄弟存储结构，编写函数求树的叶子结点个数、树的度。*/

#include <iostream>
using namespace std;

// 结点结构定义
struct TreeNode {
    int data;     // 结点数据
    TreeNode* firstChild;  // 第一个孩子指针
    TreeNode* nextSibling; // 右兄弟指针

    TreeNode(int val) : data(val), firstChild(nullptr), nextSibling(nullptr) {}
};

// 递归计算叶子结点个数
int countLeaves(TreeNode* root) {
    if (!root) return 0;  // 空树，返回0
    if (!root->firstChild) return 1;  // 没有孩子，说明是叶子结点
    return countLeaves(root->firstChild) + countLeaves(root->nextSibling);
}

// 递归计算树的度
int getDegree(TreeNode* root) {
    if (!root) return 0;  // 空树，返回0
    int count = 0; 
    TreeNode* temp = root->firstChild;
    
    while (temp) {  // 统计当前结点的子节点个数
        count++;
        temp = temp->nextSibling;
    }

    // 递归计算所有子树的度，并取最大值
    int childMax = getDegree(root->firstChild);
    int siblingMax = getDegree(root->nextSibling);

    return max(count, max(childMax, siblingMax));
}


// 测试
int main() {
    // 构造树结构
    TreeNode* root = new TreeNode(1);
    
    // 第一层孩子
    root->firstChild = new TreeNode(2);
    root->firstChild->nextSibling = new TreeNode(3);
    root->firstChild->nextSibling->nextSibling = new TreeNode(4);

    // 第二层孩子
    root->firstChild->firstChild = new TreeNode(5);
    root->firstChild->firstChild->nextSibling = new TreeNode(6);
    root->firstChild->firstChild->nextSibling->nextSibling = new TreeNode(7);

    root->firstChild->nextSibling->firstChild = new TreeNode(8);
    root->firstChild->nextSibling->firstChild->nextSibling = new TreeNode(9);

    root->firstChild->nextSibling->nextSibling->firstChild = new TreeNode(10);

    // 第三层孩子
    root->firstChild->firstChild->firstChild = new TreeNode(11);
    root->firstChild->firstChild->firstChild->nextSibling = new TreeNode(12);

    root->firstChild->nextSibling->firstChild->firstChild = new TreeNode(13);

    // 打印测试结果
    cout << "叶子结点个数: " << countLeaves(root) << endl;
    cout << "树的度: " << getDegree(root) << endl;

    return 0;
}