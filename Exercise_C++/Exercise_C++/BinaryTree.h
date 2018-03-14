#include<iostream>
#include<stack>
#include<vector>
#include<string>
using namespace std;
struct TreeNode {  //树节点定义
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
//非递归中序遍历
vector<int> inorderTraversal(TreeNode *root){
	stack<TreeNode*> s;
	vector<int> rs;
	TreeNode *node = root;
	while(s.size() > 0 || node != NULL){
		while(node){
			s.push(node);
			node = node -> left;
		}
		node = s.top();s.pop();
		rs.push_back(node->val);
		node = node -> right;
	}
	return rs;
}
//递归中序遍历
void inorderTraversal_Recursive(TreeNode *root, vector<int> &result) {
	if (root == NULL) return; 
	inorderTraversal_Recursive(root->left, result);
	result.push_back(root->val);
	inorderTraversal_Recursive(root->right, result);
}
//序列化二叉树
string help1(TreeNode* root){
        if(root == NULL)return "#!";
        string s = to_string(long long(root->val)) + "!";
        s += help1(root->left);
        s += help1(root->right);
        return s;
    }
char* Serialize(TreeNode *root) {    
        string tt = help1(root);
		cout<<tt<<endl;
        char* str=new char[tt.length()+1];
		int i;
		for(i=0;i<tt.length();i++)
			str[i]=tt[i];
		str[i]='\0';
        return str;
    }
//反序列化二叉树
int strtoint(string str){//
	int len = str.length(),i,end,b=1,sum=0;
	if(len <= 0)return 0;
	if(str[0] == '+' || str[0] == '-')end = 1;
	else if(str[0] <= '9' || str[0] >= '0')end = 0;
	else return 0;
	for(i = len-1; i >= end; i--){
		if(str[i] >= '0' && str[i] <= '9')
		    sum = sum + b * (str[i] - '0');
		else return 0;
		b *= 10;
	}
	if(str[0] == '-')return 0 - sum;
	else return sum;
}
TreeNode* help2(queue<string>& ob){
        string v = ob.front();ob.pop();
        if(v=="#")return NULL;
        TreeNode* root = new TreeNode(strtoint(v));
        root->left=help2(ob);
        root->right=help2(ob);
        return root;
    }
TreeNode* Deserialize(char *str) {
    string s = str,tmp="";
    queue<string> ob;int i = 0;
    while( i < s.length()){
        if(i < s.length() && s[i]!='!'){
            tmp += s[i];
        }
        else{
            ob.push(tmp);cout<<tmp<<endl;
            tmp = "";
        }
        i++;
        }
    return help2(ob);
}
//二叉搜索树的第k小的节点，中序遍历找到第k小个数
TreeNode* KthNode(TreeNode* root, int k){
    if(root){
        TreeNode* node = KthNode(root -> left, k);
        if(node)return node; //注意返回条件
        // index++;
        //if(index == k)return root;
       node = KthNode(root -> right, k);
       if(node)return node;
       }
        return NULL;
    }
//在二叉树中寻找和为定值的路径
class findPath{
    vector<vector<int> > rs;
    vector<int > tmp;
public:
    void finds(TreeNode* root,int ex){
        if(root==NULL){
            if(ex==0){
				if(tmp.size()>0)
				{ rs.push_back(tmp);
				  for(int i=0;i<tmp.size();i++)
					  cout<<tmp[i]<<"+";}
				cout<<endl;
				while(tmp.size()>1)
                   tmp.pop_back();
				return;
            }
             if(ex!=0){cout<<tmp.back()<<endl;
                tmp.pop_back();
				return;
            }
        }
        if(root->val > ex)
            return;
        if(root->val <= ex){
            tmp.push_back(root->val);cout<<root->val<<endl;
			if(root->left==NULL&&root->right==NULL)
                finds(root->left,ex-(root->val));
			else{
				finds(root->left,ex-(root->val));
                finds(root->right,ex-(root->val));
			}
        }
    }
};