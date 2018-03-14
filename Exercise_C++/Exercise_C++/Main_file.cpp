#include <iostream>
#include <string>
#include <set>
#include <stack>
#include <map>
#include <vector>
#include <queue>
#include <deque>
#include <iomanip>  //cout<<setiosflags(ios::fixed)<<setprecision(2)<<rs<<endl;
#include <algorithm>
#include "BinaryTree.h"
#include "some.h"
#include "classical_algm.h"
using namespace std;

int isvalid(string s){
	stack<char> st;
	for(int i=0;i<s.length();i++){
		if(s[i]=='(')
			st.push('(');
		if(s[i]==')'){
			if(!st.empty())
				st.pop();
			else
			{cout<<"0"<<endl;return false;}
		}
	}
	if(st.empty())
	{  cout<<"1"<<endl;return true;}
	else 
	{cout<<"0"<<endl;return false;}
}
void parentise(){
	int i,j;
	string s="(((())))",tmp,t;
	set<string> res;
	int len=s.length();
	for(i=0;i<len;i++){
		tmp=s;
		tmp=tmp.erase(i,1);cout<<tmp<<endl;
		for(j=0;j<len;j++){
			if(j==0)
				t=s[i]+tmp;
			else if(j==len-1)
				t=tmp+s[i];
			else
				t=tmp.substr(0,j)+s[i]+tmp.substr(j);cout<<t<<" ";
			if(isvalid(t))
				res.insert(t);
		}
		cout<<endl;
	}
	cout<<res.size()-1;
}
void sing(int v[23],int n){     //not understand
	vector<vector<int > >dp(n+1,vector<int >(n+1));
	for(int i=n-1;i>=0;i--)
		for(int j=n-1;j>=0;j--){
			int cur=max(i,j)+1;
			dp[i][j]=(int)0x7fffffff;
			//上一个音符也是由当前人唱的
			dp[i][j]=min(dp[i][j],dp[cur][j]+(i==0?0:abs(v[cur-1]-v[i-1])));
			//上一个由对方唱的
			dp[i][j]=min(dp[i][j],dp[i][cur]+(j==0?0:abs(v[cur-1]-v[j-1])));
			cout<<dp[i][j]<<endl;
		}
	cout<<dp[0][0]<<endl;
}
void monster(){
	int n,i,j,k,m,rs=0;cin>>n;
	vector<int> x,y;
	for(i=0;i<n;i++){
		int t;cin>>t;
		x.push_back(t);
	}
	for(i=0;i<n;i++){
		int t;cin>>t;
		y.push_back(t);
	}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			if(i==j)continue;
			for(k=0;k<n;k++){
				if(k==j||k==i)continue;
				int num=0;
				//三点计算坐标轴
				//遍历看有多少点在坐标轴上
				for(m=0;m<n;m++){
					if(m==k||m==j||m==i)continue;
					if((y[m]-y[i])*(x[j]-x[m])==(y[j]-y[m])*(x[m]-x[i]))num++;
					else if((y[m]-y[k])*(y[j]-y[i])==(x[m]-x[k])*(x[i]-x[j]))
						num++;
				}
				rs=rs>num?rs:num;
			}
		}
	cout<<rs+3;
}
int getHeight(vector<int> w, vector<int> l, vector<int> h, int n){
	int i,j,tem,cur,maxh;//一堆木箱，下面的长宽必须大于上面的，最大堆到的高度，先排序再最大严格上升子序列
	vector<int> rs(n,0);
	for(i=0;i<n;i++)
		for(j=0;j<n-i-1;j++){
			if(w[j]<w[j+1]){
				swap(w[j],w[j+1]);
				swap(l[j],l[j+1]);
				swap(h[j],h[j+1]);
			}
		}
	rs[0]=h[0];maxh=rs[0];
	for(i=1;i<n;i++){
		rs[i]=h[i];
		cur=0;
		for(j=0;j<=i-1;j++){
			if(l[i]<l[j]&&w[i]<w[j])
				cur=max(cur,rs[j]);
		}
		rs[i]=rs[i]+cur;cout<<rs[i]<<endl;
		maxh=max(maxh,rs[i]);
	}
	return maxh;
}


void num(int n){
	int i,j,flag=0,min=0,max=0;
	map<int,int,greater<int>> m;
	for(i=0;i<n;i++){
		int tmp;cin>>tmp;
		if(m.find(tmp)==m.end())//tmp没有重复
			m.insert(pair<int,int>(tmp,1));
		else //有重复
		{ m[tmp]++;flag=1;}
	}
	map<int,int,greater<int>>::iterator it=m.begin(),ite=m.end();
	max=(it->second)*((--ite)->second);//max
	
	int minvalue=(it->first)-((--ite)->first);
	if(flag==1){    //有重复,最小差为0
		for(it;it!=m.end();it++){
			i=it->second;
			min=min+i*(i-1)/2;
		}
	}
	else{
		for(i=0;i<m.size()-1;i++){
			int tmp=(it->first)-((++it)->first);
			if(tmp<minvalue){
				minvalue=tmp;min=0;
			}
			else{
				min++;
			}
		}
	}

	cout<<min<<" "<<max<<endl;
}
void chessplace(){
	int i,j,k,n;
	vector<int> x,y;
	cin>>n;
	vector<int> rs(n,INT_MAX);
	cout<<INT_MAX<<endl;
	for(i=1;i<=n;i++){
		int tmp;cin>>tmp;
		x.push_back(tmp);
	}
	for(i=1;i<=n;i++){
		int tmp;cin>>tmp;
		y.push_back(tmp);
	}
	for(i=0;i<n;i++)//棋盘上任一点(i,j)到k点的距离
		for(j=0;j<n;j++){
			int t=0;vector<int> dist(n,0);
			for(k=0;k<n;k++){
				dist[k]=abs(x[i]-x[k])+abs(y[j]-y[k]);
			}
			sort(dist.begin(),dist.end());
			for(k=0;k<n;k++){
				t+=dist[k];
				rs[k]=min(rs[k],t);
			}
		}
	for(i=0;i<n-1;i++)
		cout<<rs[i]<<" ";
	cout<<rs[n-1]<<endl;
}
int like(int n,int k){
	cout<<"ddd"<<endl;
	int i,j,rs=0,m=1000000007,sum=0;
	int dp[11][100001];
	for(i=1;i<=k;i++){
		dp[1][i]=1;
		sum=(sum+dp[1][i])%m;
	}
	for(i=2;i<=n;i++){
		int now=0;
		for(j=1;j<=k;j++){
			int sum2=0;
			for(int t=2*j;t<=k;t=t+j)
				sum2=(sum2+dp[i-1][t])%m;
			dp[i][j]=(sum-sum2+m)%m;
			now=(now+dp[i][j])%m;
		}
		sum=now;
	}
	for(i=1;i<=k;i++)
		rs=(rs+dp[n][i])%m;

	return rs;
}
void inters(){  //每次取一个数放到末尾，几次操作完成从小到大排列
	int i,j,k,n;
	cin>>n;
	vector<int > s;
	map<int,int> m;
	for(i=1;i<=n;i++){
		int tmp;cin>>tmp;
		s.push_back(tmp);
		m[tmp]=i;
	}
	sort(s.begin(),s.end());
	int rs=0,index=n;
	for(i=0;i<n-1;i++){
		if(m[s[i]]>m[s[i+1]]){
			m[s[i+1]]=index++;
			rs++;
		}
	}
	cout<<rs<<endl;
}
int countWays(string exp, int len, int ret) {
    if(len%2!=1)return 0;
    vector<vector<int> > t(len,vector<int>(len));
    vector<vector<int> > f(len,vector<int>(len));
    int i,j;
	for(i=0;i<len;i++){}
}
int maxSubMatrix(int mat[][5], int n) {
        vector<vector<int> > down(n,vector<int>(n)),right(n,vector<int>(n));
        int i,j,count=1;
        down[n-1][n-1]=1;
        right[n-1][n-1]=1;
        for(i=n-2;i>=0;i--){//最右的边
            if(mat[i][n-1]==mat[i+1][n-1])
                down[i][n-1]=down[i+1][n-1]+1;
            else
                down[i][n-1]=1;
            right[i][n-1]=1;
        }
        for(j=n-2;j>=0;j--){//最下的边
            if(mat[n-1][j]==mat[n-1][j+1])
                right[n-1][j]=right[n-1][j+1]+1;
            else
                right[n-1][j]=1;
            down[n-1][j]=1;
        }
        for(i=n-2;i>=0;i--)//内部
            for(j=n-2;j>=0;j--){
                if(mat[i][j]==mat[i+1][j])
                    down[i][j]=down[i+1][j]+1;
                else 
                    down[i][j]=1;
                if(mat[i][j]==mat[i][j+1])
                    right[i][j]=right[i][j+1]+1;
                else
                    right[i][j]=1;
            }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                int a=1;int c=1;
                while(i+a<n&&j+a<n){
                    if(mat[i][j]==mat[i+a][j]&&mat[i][j]==mat[i][j+a]&&mat[i][j]==mat[i+a][j+a]&&down[i][j]>=a+1&&right[i][j]>=a+1&&down[i][j+a]>=a+1&&right[i+a][j]>=a+1)
                        c=max(1+a,c);
                    
                    a++;
                }
				cout<<i<<"  "<<j<<" "<<c<<endl;
                count=max(count,c);
            }
        return count;
    }
static bool cmp(pair<string, int> a, pair<string, int> b){
	return a.second > b.second;
}
void counterror(){
	int i,j=0,k=0;
	string s;
	vector<pair<string,int> >rserror;
	while(getline(cin,s)){
		if(s.length()==0)break;
		i=s.rfind('\\');
		string fnli=s.substr(i+1);//把文件名和行号放到一起处理
		rserror.push_back(make_pair(fnli,1));
		for(j=0;j<(rserror.size()-1);j++){
			if(rserror[j].first==fnli){
				rserror[j].second++;
				rserror.pop_back();
				break;
			}
		}
	}
	stable_sort(rserror.begin(),rserror.end(),cmp);
	for(i=0;i<rserror.size()&&i<8;i++){
		j=rserror[i].first.find(' ');//取出文件名判断是否超出16位
		if(j>16)
			rserror[i].first.erase(0, j - 16);
		cout<<rserror[i].first<<" "<<rserror[i].second<<endl;
	}
}
int cardtype(string s){   //炸弹和对王可以与所有种类的牌比较
	if(s.length()==1||s=="joker"||s=="JOKER")return 1;//单张
	else if(s.length()==3)return 2;//对子
	else if(s.length()==5)return 3;//三张
	else if(s.length()==7)return 4;//炸弹
	else if(s.length()==11)return 5;//对王
	else return 6;//连张s.length()==9
}
int cmpcard(char a,char b){
	if(a=='2')return 1;
	else if(a=='A'){
		if(b=='2')return 0;
		else return 1;
	}
	else if(a=='K'){
		if(b=='A' || b=='2')return 0;
		else return 1;
	}
	else if(a=='Q'){
		if(b=='A' || b=='2' || b=='K')return 0;
		else return 1;
	}
	else if(a=='J'){
		if(b=='A' || b=='2' || b=='K' || b=='Q')return 0;
		else return 1;
	}
	else if(a=='0'){
		if(b=='A' || b=='2' || b=='K' || b=='Q' || b=='J')return 0;
		else return 1;
	}
	else {
		if(b<='9' && b>='3'){
			if(a>b)return 1;
			else return 0;
		}
		else return 0;
	}
	return 1;
}
void card(){
	string s,rs;getline(cin,s);
	int f = s.find('-');
	string left = s.substr(0,f),right = s.substr(f + 1);
	int pos = left.find("10");//把10变成0
	while(pos>-1){
		left.erase(pos,1);  
		pos = left.find("10");
	}
	pos = right.find("10");
	while(pos>-1){
		right.erase(pos,1);  
		pos = right.find("10");
	}
	int type1 = cardtype(left),type2 = cardtype(right);
	cout<<type1<<" "<<type2<<endl<<endl;
	if((type1 != type2)&&(type1 != 4)&&(type1 != 5)&&(type2 != 4)&&(type2 != 5)){
		cout<<"ERROR"<<endl;
		return;
	}
	if(type1==1){
		if(type2==4 || type2==5)rs = right;//有炸弹或对王
		else if(left.length()>1)rs = left; //有一个王
		else if(right.length()>1)rs = right;
		else if(cmpcard(left[0],right[0]))rs = left;
		else rs = right;
	}
	else if(type1==2){
		if(type2==4 || type2==5)rs = right;
		if(cmpcard(left[0],right[0]))rs = left;
		else rs = right;
	}
	else if(type1==3){
		if(type2==4 || type2==5)rs = right;
		if(cmpcard(left[0],right[0]))rs = left;
		else rs = right;
	}
	else if(type1==4){ //炸弹
		if(type2 == 5)rs = right;
		//else if(right.length()==11)rs = right;
		else if(type2 == 4){
			if(cmpcard(left[0],right[0]))rs = left;
			else rs = right;
		}
		else rs=left;
	}
	else if(type1==5)rs = left;//对王
	else{ //5连
		if(type2==4 || type2==5)rs = right;
		if(cmpcard(left[0],right[0]))rs = left;
		else rs = right;
	}
	pos=0;
	while(pos<rs.length()){
		if(rs[pos]=='0'){rs.insert(pos,"1");pos++;}
		pos++;
	}
	cout<<rs<<endl;
}
class TrieTree{
};

void CPU(){
	int i,j,k=0,N,M=0;
	cin>>N;vector<int> cpu;
	
	for(i = 1; i <= N; i++){
		cin>>k;cpu.push_back(k/1024);
		M = M + k/1024;
	}
	vector<int > rs(M / 2 + 1, 0);
	for(i = 0; i < N; i++)
		for(j = M/2; j >= cpu[i]; j--)
			rs[j] = max(rs[j - cpu[i]]+cpu[i],rs[j]);//01背包问题
	cout<<(M- rs[M / 2]) * 1024<<endl;
}
vector<vector<int> > mulMatrix(vector<vector<int> >& rs, vector<vector<int> >& ini, int n){
	vector<vector<int> > ss(n,vector<int>(n,0));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			for (int k = 0; k<n; k++) {  
                ss[i][j] += rs[i][k]*ini[k][j];
            }
            ss[i][j] %= 100; 
		}
	return ss;
	/*while (k != 0) {  //rs为单位阵，ini为底数，k为指数
        if (k % 2 == 1) {  
            rs = mulMatrix(rs, ini, n);  
        }  
        ini = mulMatrix(ini, ini, n);  
        k = k >> 1;  
    } */
}
void dfs(vector<vector<int> >& v,int flag[],int& rs,int i,int n){
	if(i==n){rs++;return;}//n个人都分配好了就返回递归
	//for(int k=0;k<n;k++)cout<<flag[k];
	for(int j=0;j<6;j++){
		if(flag[j]==0&&v[j][i]==1){
			flag[j]=1;
			dfs(v,flag,rs,i+1,n);
			flag[j]=0;
		}
	}
}
void FindContinuousSequence(int sum){//和为sum的连续整数，至少两个
	int i=1,j=2,s=1;
        while(j <= sum){
            if(s < sum){
                s += j;j++;cout<<i<<" "<<j<<" "<<s<<endl;
            }
            else if(s > sum){
                s -= i;i++;cout<<i<<" "<<j<<" "<<s<<endl;
            }
            else{
                cout<<i<<" "<<j-1<<endl;
				s = s + j - i;cout<<s<<endl;
				i++;j++;
            }
        }
}
void ReverseSentence(string str){
	int i, len = str.length();//"i am  a student." to  "students. a  am i"
	for(i = 0;i < len/2; i++){
		char c = str[i];
		str[i] = str[len-1-i];
		str[len-i-1] = c;
	}
	cout<<str<<endl;
	int start=0,end=0;
	i = 0;
	while( i < len){
		while(i<len && str[i] == ' ')i++;
		start = i;
		end = i;
		while(i<len && str[i] != ' '){end++;i++;}
		cout<<start<<" "<<end<<endl;
		int j = start,k=end-1;
		while(j<=k){
			char c=str[j];str[j]=str[k];str[k]=c;
			j++;k--;
		}
	}
	cout<<str<<endl;
}
void FindNumsAppearOnce(int data[],int* num1,int *num2) {
    //数组中所有数字都出现了两次，除了两个数，找出它们，利用异或
	int i,t=data[0],a = 0,b = 0;
	for(i=1;i<8;i++)
		t = t^data[i];
	int k = 1;
	while(k <= t){
		if((t & k) !=0 )break;
		else k = (k<<1);    //所有数异或后，找到结果的第一个1的位置
	}
	cout<<k<<endl;
	for(i=0;i<8;i++){//按照k位是否为0分开两组异或，得到两个结果
		//cout<<((data[i] ^ k)&k)<<endl;
		if(((data[i] ^ k)&k) == 0){
			if(a == 0){*num1 = data[i];a=1;}
			else (*num1) ^= data[i];
			cout<<"num1: "<<(*num1)<<endl;
		}
		else{
			if(b == 0){*num2 = data[i];b=1;}
			else (*num2) ^= data[i];
			cout<<"num2: "<<(*num2)<<endl;
		}
	}
}
vector<int>& MaxWindow(int data[],int len,int w){
	deque<int> d;//双端队列存储下标，并保证从队头一直单调递减
	vector<int> rs(len-w+1);
	int i,index = 0;
	for(i = 0; i < len; i ++){
		while(!d.empty() && data[i] >= data[d.back()])
			d.pop_back();
		d.push_back(i);
		if(d.front() == i - w)d.pop_front();//队头过期
		if(i >= w - 1)rs[index++] = data[d.front()];
	}
	for(i=0;i<rs.size();i++)
		cout<<rs[i]<<" ";
	return rs;
}


   
bool isNumeric(string str)
    {
		int len = str.length();
        if(len == 0)return false;
        bool hase = false, dot = false, sign = false;
        for(int i = 0; i < len; i++){
			cout<<i<<endl;
            if(str[i] == 'e' || str[i] == 'E'){
                if(i == len-1)return false;
                if(hase)return false;
                hase = true;
            }
            else if(str[i] == '+' || str[i] == '-'){
                if(sign && str[i-1] != 'E' && str[i-1] != 'e')return false;
                if(!sign && i > 0 && str[i-1] != 'E' && str[i-1] != 'e')return false;
                sign = true;
            }
            else if(str[i] == '.'){
				cout<<"hase="<<hase<<endl;
                if(hase || dot)return false;
                dot = true;
            }
            else if(str[i] < '0' || str[i] > '9')return false;
        }
        return true;
    }


void MaxProfit(){//最多两次股票交易，必须卖出之后才能再次交易，求最大收益
	int buy1 = INT_MIN, sell1 = 0, buy2 = INT_MIN, sell2 = 0;
	int prices[]={2,1,3,4,6,2,9,5};
	for(int i = 0; i < 8; i++) {
		buy1 = max(buy1, -prices[i]);
		sell1 = max(sell1, buy1 + prices[i]);
		buy2 = max(buy2, sell1 - prices[i]);
		sell2 = max(sell2, buy2 + prices[i]);
		cout<<buy1<<" "<<sell1<<" "<<buy2<<" "<<sell2<<endl;
	}
}
int main(){
	int i,j,k,n=0,m=0;
	//int v[23]={24,13,2,4,54,23,12,53,12,23,42,13,53,12,24,12,11,24,42,52,12,32,42};
	//sing(v,23);
	
	int T;cin>>T;
	while(T > 0){
		cin>>n; k = 1; i = 0;
		int index = 0;
	    vector<int> out(n,-1);
		while(k <= n){
			i = index;
			while(out[i%n] != -1)i++;
			while(out[(i+1) % n] != -1)i++;
			index = (i+1) % n;
			out[index] = k;
		    k++;
		}
		for(i = 0; i < n-1; i++)
			cout<<out[i]<<" ";
		cout<<out[i]<<endl;
		T--;
	}
	getchar();getchar();
	return 0;
}
