#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<ctime>
#include <algorithm>
using namespace std;
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
//上楼梯 一次1,2,3
int fun(vector<int>ways,int n){
        if(n==1){
            ways[0]=1;
            return 1;
        }
        else if(n==2){
            ways[1]=2;
            return 2;
        }
        else if(n==3){
            ways[2]=4;
            return 4;
        }
        else{ 
            if(ways[n-1]!=0)return ways[n-1];
            else return (fun(ways,n-1)+fun(ways,n-2)+fun(ways,n-3))%1000000007;
        }
    }
    int countWays1(int n) {
        vector<int>ways(n,0);
        return fun(ways,n);
    }

vector<int> twoStacksSort(vector<int> numbers) {
        stack<int> tmp;  //small to big
        vector<int> rs;
        while(numbers.size()>0){
			int t=numbers.back();
            if(tmp.empty()||tmp.top()<=t){				
                tmp.push(t);				
                numbers.pop_back();
            }
            if(!tmp.empty()&&tmp.top()>t){
                numbers.pop_back();
                while(!tmp.empty()&&tmp.top()>t){
                    numbers.push_back(tmp.top());
                    tmp.pop();
                }
                tmp.push(t);cout<<"!";
            }
			cout<<numbers.size()<<endl;
        }
        while(!tmp.empty()){
            int t=tmp.top();
            tmp.pop();
            rs.push_back(t);
        }
        return rs;
    }
void get(int* root, ListNode* p,int dep,int now){
        if(now>dep)
			return;
        else if(now%2==0){
            ListNode* tmp=new ListNode(root[now]);
            p->next=tmp;
            p=tmp;
        }
		else
			get(root,p,dep,now+1);
    }
//下一个比自己大的数中最小的
vector<int> findNext(int *A, int n) {
        stack<int> s1,s2;
        vector<int> rs;
		//rs.push_back(-1);
      
      for(int i=n-1;i>=0;i--){
            while((!s1.empty())&&A[i]>=s1.top()){
                s2.push(s1.top());
                s1.pop();
            }
            if(!s1.empty())
              rs.push_back(s1.top());
		    else 
              rs.push_back(-1);

             s1.push(A[i]);
             while(!s2.empty()){
                    s1.push(s2.top());
                    s2.pop();
                }
        }
		reverse(rs.begin(),rs.end());
        return rs;
    }
int jsf(int n,int m) {
    if(n/m==0)return 1;
    int n2;
	if(n%m==0)n2=n/m;
	else n2=n/m+1;
    if(n2<=m+1)return (n2-1)*m+1;
	int location=jsf(n2,m+1);
	return (location-2)*m+1;
}

//和原数二进制1个数相同，最接近的数
void fuc(int x){
	int c1=0,c0=0,c01=0,c11=0,t=1;
   while((t&x)!=0){
            t<<=1;c1++;
        }
   while((t&x)==0){
        t=t<<1;c0++;
   }
   
   int a=x-(1<<c1)-(1<<(c0-1))+1;
   cout<<a<<endl;t=1;
   while((t&x)==0){
	   t=t<<1;c01++;
   }
   while((t&x)!=0){
      t=t<<1;c11++;
   }
   cout<<c0<<" "<<c1<<endl;
   int b=x+(1<<(c11-1))+(1<<(c01))-1;cout<<b<<endl;
}
//15,10,5,1硬币表示
    int countWays(int n) {
		int rs[100001]={0};
		rs[0]=1;
        int coins[]={1,5,10,25};
        for(int i=0;i<4;i++)
			for(int j=coins[i];j<=n;j++)
				rs[j]=(rs[j]+rs[j-coins[i]])%1000000007;
        return rs[n];
    }


//从p到r找出第i小的数
 int find(vector<int > A,int p,int r,int i){
        if(p==r)
			return A[p];
    }
    vector<int> getMiddle1(vector<int> A, int n) {
        vector<int > rs;
        int i;
		for(i=0;i<n;i++){
            rs.push_back(find(A,0,i,i/2));
        }
		return rs;
    }
	vector<string > res;

vector<int> findSegment(int A[],int n){
	vector<int > rs(2,0);
	int i,left=0,right=0,max,min;
	for(i=0;i<n-1;i++)
		if(A[i]>A[i+1]){
			left=i;break;
		}
	for(i=n-1;i>0;i--)
		if(A[i]<A[i-1]){
			right=i;break;
		}
	cout<<left<<" "<<right<<endl;
	max=A[left];min=A[right];
	for(i=left;i<=right;i++){
		if(A[i]<min)min=A[i];
		if(A[i]>max)max=A[i];
	}
    for(i=0;i<=left;i++)
		if(A[i]>min)left=i;
		int flag=1;
	for(i=right;i<=n-1;i++)
		if(A[i]<max){right=i;flag=0;}
	rs[0]=left;rs[1]=right;
	return rs;
}
string hunderd(int x){
	string rs="";
	string num1[]={"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",};
	string num2[]={"Ten","Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen","Nineteen","Twenty"};
	string num3[]={"","Ten","Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
		if(x<10)
			rs=rs+num1[x];
		else if(x<=20)
			rs=rs+num2[x-10];
		else if(x<100)
			rs=rs+num3[x/10]+" "+num1[x%10];
		else if(x<1000)
			rs=rs+hunderd(x/100)+" Hundred "+hunderd(x%100);
		else if(x<1000000)
			rs=rs+hunderd(x/1000)+" Thousand"+(x % 1000 > 0 ? "," : " ")+ hunderd(x%1000);
		else if(x<1000000000)
			rs=rs+hunderd(x/1000000)+" Million"+(x % 1000000 > 0 ? "," : " ")+hunderd(x%1000000);
		else
			rs=rs+hunderd(x/1000000000)+" Billion"+hunderd(x%1000000000);
        //要记得去除末尾空格
		return rs;
}
string toString(int x) {
		if(x==0)return "Zero";
		else return hunderd(x);

    }
void getMiddleNum(vector<int> A, int n) {   //实时中位数
        vector<int> max,min,rs(n);
        rs[0]=A[0];
        if(n==1)return;
        if(A[0]>A[1]){
            max.push_back(A[1]);
            min.push_back(A[0]);
        }
        else{
            max.push_back(A[0]);
            min.push_back(A[1]);
        }
        rs[1]=max[0];
        for(int i=2;i<n;i++){
			int num=A[i];
            if(i%2==1){
				if(A[i]>min[0]){
					min.push_back(A[i]);
					push_heap(min.begin(),min.end(),greater<int>());
					num=min[0];
					pop_heap(min.begin(),min.end(),greater<int>());
					min.pop_back();
				}
                max.push_back(num);
                push_heap(max.begin(),max.end());
                rs[i]=max[0];
            }
            else{
				if(A[i]<max[0]){
					max.push_back(A[i]);
					push_heap(max.begin(),max.end());
					num=max[0];
					pop_heap(max.begin(),max.end());
					max.pop_back();
				}
                min.push_back(num);
                push_heap(min.begin(),min.end(),greater<int>());
                rs[i]=min[0];
            }
            
        }
		
    }
int countNumberOf2s(int n) {  
	 if(n==0)return 0;
	 int count=0;
	 for(int i=1;i<=n;i=i*10){
		 int a=n/i,b=n%i;
		 count=count+(a+7)/10*i+((a % 10 == 2) ? b + 1 : 0);
	 }
	 return count;
}/*
void main(){ 
	vector<int> c(5);
	for(int i=0;i<5;i++)
		c[i]=i+1;
	for(i=c.size()-1;i)
time_t begin,end; 
begin=clock(); 
int test=1523;
cout<<countNumberOf2s(test)<<endl;
end=clock(); 
cout<<"runtime: "<<double(end-begin)/CLOCKS_PER_SEC<<endl; 

int A[]={47945,90932,291547,23509,234737,204045,39427,675,72800,196768,92527,201090,51551,153337,143322,
197200,271044,172056,12793,90836,97548,261459,204946,259709,286228,115650,54793,112090,216259,295835,182772,
222705,276350,186722,269784,289673,68433,232029,229895,209586,204078,77736,57076,265863,50799,79859,15537,
150903,53329,275591,149409,101038,56781,125914,9521,205145,65916,80096,109558,187681,209854,116756,49188,90209,
163847,84814,64921,242402,123891,35581,223842,233485,8584,135035,295509,193877,218776,77490,58744,13792,233100,
33737,100301,137212,286467,94787,224802,73037,85841,263437,278174,158784,68645,9723,117205,250417,133358,225257,
110166,143810,127664,225666,228957,4512,251922,72114,124949,107794,206500,72637,146990,272545,20138,234661,291309,
203634,253319,129225,147364,139053,207111,226902,54011,130790,216496,172599,73400,59492,94185,160253,150074,11538,
164734,43826,273098,289432,228553,8017,286779,170249,104145,76611,139490,216723,195431,135020,16486,208129,166476,
200934,76005,26075,64972,202174,89593,146178,197809,262913,168123,250751,134388,125564,217131,82129,172181,221270,
288709,225915,45785,152838,266713,45476,240374,35676,130179,137278,99089,197892,246419,5594,37902,134481,41025,172466,
212640,136431,208506,56288,172329,115576,256931,99738,222269,137181,217187,7345,11218,179539,95337,284738,292232,165257,
297185,288980,29682,235932,140937,30376,97679,300827,126512,134756,258222,65449,86450,72864,260356,162962,283923,291181,
287701,57215,8743,47407,300287,38378,22270,138905,143693,151516,71261,61923,69694,123854,159884,57108,65745,266453,33358,
56460,9152,189843,228715,245499,218103,38287,240368,110792,148572,94350,161021,90060,63746,40772,46653,53514,38536,285029,
238958,130398,206102,251065,171217,182670,238814,48670,7774,89423,163291,281147,204776,66408,181401,114983,292589,16219,
95644,43398,241382,68428,282183,92826,51130,90328,63463,276879,89878,204832,129680,26711,33897,139789,284307,20050,86565,
136593,98719,76861,107970,138484,293738,109092,104328,127683,243320,44266,34415,129683,145062,91869,85718,106391,84390,
46486,168286,174149,67958,208186,54552,32992,77707,7894,44815,230480,24507,121514,48875,137187,266141,272667,70453,225501,
227471,138868,68282,63016,289004,114138,116310,65090,83097,278381,13090,273970,206714,49092,152596,299368,100824,132348,
75213,151668,214245,40341,35347,46934,11776,59222,122202,178273,18083,24909,74338,185600,211993,38038,108136,211739,51973,
104446,235450,292891,84232,282617,65667,104432,298568,122893,136815,46392,93201,186305,211836,174441,287051,251043,298826,
180376,270008,157763,110799,148025,261501,138530,260812,165904,3949,266804,279464,104066,212296,237716,239007,84414,241548,
210135,60934,184644,300634,3347,103677,72965,250935,130467,268053,247391,70759,258294,137576,137962,222966,107571,287532,
223921,62727,162055,80137,67634,251812,289220,209236,14489,272314,267427,253776,291393,3130,57421,55566,18091,60562,23306,
83940,235752,218113,43925,143099,183893,168518,286534,3133,18202,123779,1653,33291,177786,144397,27033,59389,260605,49097,
176373,54528,24689,70453,69788,76083,152142,189654,54781,258579,282760,180642,242768,124145,20442,148351,131061,79751,
218373,103307,102465,130682,152977,62323,16729,154193,29197,213852,271337,52764,84370,131249,239159,249144,28232,6106,
157812,48140,251320,90003,35023,287360,35753,74093,287182,270587,113935,42257,102246,45878,36062,132262,181933,123561,
242341,291815,46819,121600,232204,139926,85990,31211,200054,52112,86208,56620,85142,39200,28589,264158,107096,171941,
225946,133427,3581,135931,163815,155481,40686,72994,256312,87354,5327,253169,61947,89591,59423,129412,256005,12908,76777,
213737,183803,87249,3288,14259,203411,248780,292378,165692,84006,47320,215619,250124,169096,285149,294579,88232,35130};
vector<int > skdjs=findNext(A,570);
//for(i=0;i<skdjs.size();i++)
  // cout<<skdjs[i]<<" ";


}*/
string mod4(vector<int> A,int n){
	int i,one=0,two=0,four=0;
	cout<<A[1]<<endl;
	for(i=0;i<n;i++){
		if(A[i]%2==0&&A[i]%4!=0)
			two++;
		if(A[i]%4==0)
			four++;
		if(A[i]%2==1)
			one++;
	}
	cout<<one<<" "<<two<<" "<<four<<endl;
	if(two==0){
		if(four>=one-1)
			return "Yes";
	}
	else{
		if(four>=one)
			return "Yes";
	}
	return "No";
}

/*int main(){
    int i,j;
	string s,tmp,t;cin>>s;
	map<string> res;
	int len=s.length();
	for(i=0;i<len;i++){
		tmp=s;
		tmp=tmp.erase(i,1);cout<<tmp<<endl;
		for(j=0;j<len-1;j++){
			if(j==0)
				t=s[i]+tmp;
			else if(j==len-2)
				t=tmp+s[i];
			else
				t=tmp.substr(0,j)+s[i]+tmp.substr(j);cout<<t<<endl;
			if(isvalid(t)&&t!=s)
				res.insert(t);
		}
		cout<<endl;
	}
    cout<<res.size();
    return 0;
}*/
