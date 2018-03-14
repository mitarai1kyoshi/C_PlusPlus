#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include <algorithm>
using namespace std;
//n皇后问题（回溯）
class Queens{
public:
  int check(int j,int *Q){//判断每一步是否能放
	for(int i=1;i<j;i++){
		if((Q[i]==Q[j])||(abs(Q[i]-Q[j])==abs(i-j)))
			return 0;
	}
	return 1;
  }
  void findQ(int *Q,int i,int n,int &rs){//回溯，放满n个返回，某步不能放就回溯
	if(i>n)
	{ rs++;return;}
	for(int j=1;j<=n;j++){
		Q[i]=j;
		if(check(i,Q))
		    findQ(Q,i+1,n,rs);
	}
  }
  void nQueens(int n){
	int rs=0;
	int *Q=new int[n+1];
	findQ(Q,1,n,rs);
	cout<<rs;
  }
};
class Sudoku{
int sudk[9][9];
bool check_sudoku(int row, int col, int v){
	int i,j;
	for(i=0;i<9;i++)
		if(sudk[row][i] == v)return false;
	for(i=0;i<9;i++)
		if(sudk[i][col] == v)return false;
	for(i=row/3 * 3;i< row/3 * 3 + 3; i++)
		for(j= col/3 * 3; j< col/3 * 3 + 3; j++)
			if(sudk[i][j] == v)return false;
	return true;
  }
bool sudoku(int n){
	if(n == 81)return true;
	int row = n / 9;
	int col = n % 9;
	if(sudk[row][col] != 0)return sudoku(n+1);
	for(int val=1;val<=9;val++)
		if(check_sudoku(row,col,val)){
			sudk[row][col] = val;
			if(sudoku(n+1))return true;
			sudk[row][col] = 0;//回溯完要恢复原来的值
		}
	return false;
  }
};

//各种排序
// 堆排
void heap_adjust(int k[],int i,int n)//每个节点均大于子节点
{
	int j=2*i;int tem=k[i];
    while(j<=n)
	{
		if(j<n&&k[j]>k[j+1])
			j++;      //j为i孩子中最小的
		if(tem<=k[j])break;
		k[j/2]=k[j];
		j=2*j;
	}
	k[j/2]=tem;
}
void heap(int k[],int n)
{
	int i,tem;
	for(i=n/2;i>=0;i--)
		heap_adjust(k,i,n);
	for(i=n-1;i>=0;i--)
	{
		tem=k[i+1];
		k[i+1]=k[0];
		k[0]=tem;
		heap_adjust(k,1,i);
	}
}
//计数排序
vector<int > countsort(int A[],int n,int k){
	int i,j;
	vector<int> C(k),B(n);
	for(i=0;i<k;i++)C[i]=0;
	for(j=0;j<n;j++)
		C[A[j]]=C[A[j]]+1;//第i个数为i的个数
	
	for(i=1;i<k;i++)
		C[i]=C[i]+C[i-1];  //第i个数小于等于i的个数
	
	for(j=n-1;j>=0;j--){
		B[C[A[j]]-1]=A[j];
		C[A[j]]=C[A[j]]-1;
	}
	for(j=0;j<n;j++)
cout<<B[j]<<endl;
	return B;
}
//字符串全排列，按字典顺序
void perm(string A,unsigned long now){
        if(now==A.length()-1){
            res.push_back(A);
            return;
        }
        for(unsigned long i=now;i<A.length();i++){
            swap(A[i],A[now]);cout<<A<<endl;
            perm(A,now+1);
            //swap(A[i],A[now]);
        }
    }
    vector<string> getPermutation(string A) {
        
        perm(A,0);
        sort(res.begin(),res.end(),greater<string>());
        return res;
    }
//最大公共子序列LCS（动态规划）
int MaxComLen(string s,string t){
	int len1=s.length(),len2=t.length(),i,j;
	vector<vector<int> >LCS(len2+1,vector<int>(len1+1));
	for(i=0;i<=len1;i++)
		LCS[i][0]=0;
	for(j=0;j<=len2;j++)
		LCS[0][j]=0;
	for(i=1;i<=len1;i++)
		for(j=1;j<=len2;j++){
			if(s[i-1]==t[j-1])
				LCS[i][j]=LCS[i-1][j-1]+1;
			else
				LCS[i][j]=max(LCS[i-1][j],LCS[i][j-1]);
			
		}
	return LCS[len1][len2];
}

void knuth(int n, int m)
{ 
    srand((unsigned int)time(0)); //产生n到m的随机数
    for (int i = 0; i < n; i++) { 
        if ( rand()%(n-i)<m) { 
            cout << i << endl;
            m--;
        }
     }
}
int gcd(int n,int m){
	int N=max(n,m),M=min(n,m),t;
	while(M!=0){
		t=N;
		N=M;
		M=t%M;
	}
	return N;
}