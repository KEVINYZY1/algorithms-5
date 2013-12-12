/*
 * author:	luo feng
 * date:	2013/12/11
 * source:	LeetCode OJ
 * title:	Binary Tree Preorder Traversal
 *              Binary Tree Postorder Traversal
 * language:	C++
 */

#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>
#include <stack>
using namespace std;

typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
} TreeNode;

void tree_create(TreeNode *&root, vector<int> vec)
{
    int i = 0;
    root = NULL;

    if(vec.empty())
        return;
    TreeNode *pnode = new TreeNode(vec.at(0));
    root = pnode;
    queue<TreeNode *> que;
    que.push(pnode); 
    
    for(i =1; i < vec.size(); i++) {
        TreeNode *qnode = que.front();
        que.pop();
        if(vec.at(i) == 0)
            qnode->left = NULL;
        else {
            pnode = new TreeNode(vec.at(i));
            qnode->left = pnode;
            que.push(pnode);
        }
        i++;
        if(i >= vec.size())
            break;
        if(vec.at(i) == 0)
            qnode->right = NULL;
        else {
            pnode = new TreeNode(vec.at(i));
            qnode->right = pnode;
            que.push(pnode);
        }
    }
}

void tree_traverse(TreeNode *root)
{
    if(root == NULL)
        return;

    if(root->left)
        tree_traverse(root->left);

    cout<<root->val<<"\t";

    if(root->right)
        tree_traverse(root->right);
}

void tree_destory(TreeNode *&root)
{
    if(root == NULL)
        return;

    if(root->left)
        tree_destory(root->left);

    if(root->right)
        tree_destory(root->right);

    delete root;
}

class Solution {
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        stack<TreeNode *> sta;
        TreeNode *pnode = root;
        vector<int> vec;

        while(pnode || !sta.empty()) {
            while(pnode) {
                vec.push_back(pnode->val);
                sta.push(pnode);
                pnode = pnode->left;
            }
            if(!sta.empty()) {
                pnode = sta.top();
                sta.pop();
                pnode = pnode->right;
            }
        }
        return vec;
    }

    vector<int> postorderTraversal(TreeNode *root)
    {
        stack<pair<TreeNode *, int> > sta;
        TreeNode *pnode = root;
        vector<int> vec;
        pair<TreeNode *, int> ptnode;

        //�Ӹ��ڵ㿪ʼ�������·��ߣ�һֱ�ߵ�ͷ����·���ϵ�ÿ���ڵ���ջ
        while(pnode) {
            sta.push(make_pair(pnode, 0)); //ѹ��ջ����������Ϣ��һ�ǽڵ�ָ�룬�������ҽڵ��Ƿ񱻷��ʹ�
            pnode = pnode->left;
        }

        while(!sta.empty()) { //��ջ�ǿ�ʱ
            ptnode = sta.top(); //��ȡջ��Ԫ��

            //�����Һ����Ѿ������ʹ������Ǹ�Ԫ��û���Һ��ӣ����ɺ�������Ķ��壬��ʱ�Ϳ��Է�������ڵ���
            if(!ptnode.first->right || ptnode.second) {
                ptnode = sta.top();
                sta.pop();
                vec.push_back(ptnode.first->val);
            }
            else { //�����Һ��Ӵ����������Һ���û�б����ʹ�����ȥ�������Һ���
                ptnode.second = 1;
                sta.pop();
                sta.push(ptnode);
                pnode = ptnode.first->right;
                while(pnode) {
                    sta.push(make_pair(pnode, 0));
                    pnode = pnode->left;
                }
            }
        }
        return vec;
    }
};

void print_res(int x)
{
    cout << x << "\t";
}

int main(int argc, char *argv[])
{
    TreeNode *tree;
    int arr[] = {1, 0, 2, 3};
    int len = sizeof(arr) / sizeof(arr[0]);
    vector<int> vec(arr, arr + len);
    tree_create(tree, vec);
    //tree_traverse(tree);
    cout<<endl;
    Solution sol;
    cout << "Preorder Traversal:" << endl;
    vec = sol.preorderTraversal(tree);
    for_each(vec.begin(), vec.end(), print_res);
    cout << endl;
    vec.clear();
    cout << "Postorder Traversal:" << endl;
    vec = sol.postorderTraversal(tree);
    for_each(vec.begin(), vec.end(), print_res);
    cout<<endl;
    tree_destory(tree);

    return 0;
}
