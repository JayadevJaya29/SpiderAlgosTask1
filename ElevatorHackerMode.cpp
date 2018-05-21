#include<vector>
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;
struct elevator
{
	int fno,ent,ex;
};
elevator input(int x,int y, int z)
{
	elevator e;
	e.fno=x;
	e.ent=y;
	e.ex=z;
	return e;
}
bool compare(elevator e1,elevator e2)
{
	return(e1.fno<e2.fno);
}
int binarysearch(vector <elevator> v,int beg,int end,int k)
{
	int mid=(beg+end)/2;
	if(v[mid].fno==k)
	{
		return mid;
	}
	else if(v[mid].fno>k)
	{
		end=mid-1;
		return binarysearch(v,beg,end,k);
	}
	else if(v[mid].fno<k)
	{
		beg=mid+1;
		return binarysearch(v,beg,end,k);
	}
	return -1;
}
bool check(vector<elevator> v)
{
	bool flag=true; 
	for(int i=0;i<v.size();++i)
	{
		if(v[i].ex!=0 || v[i].ent!=0)
		{
			flag=true;
			break;
		}
		else
		flag=false;
	}
	return flag;
}
void checkcount(vector <elevator> v)
{
	int s1=0;
	int s2=0;
	for(int i=0;i<v.size();++i)
	{
		s1+=v[i].ent;
		s2+=v[i].ex;
	}
	if(s1!=s2)
	{
		cout<<"\nERROR! PEOPLE ENTERING NOT EQUAL TO PEOPLE LEAVING!\n";
		exit(1);
	}
}
int main()
{
	vector<elevator> v,v1;
	vector<elevator>::iterator ptr;
	elevator r;
	int i,j,k,n,x,y,z,cmax,c,l,e;
	cout<<"Enter the floor to start from \t";
	cin>>k;
	cout<<"\nEnter max lift capacity \t";
	cin>>cmax;
	cout<<"\nEnter floor number,number of people entering at floor,number of people leaving at floor in order (Include the starting floor). Enter 3 0s to stop accepting input. Note that total people entering lift should be = total people leaving lift.\n";
	while(cin>>x>>y>>z)
	{
		if(x==0)
		break;
		if(y>cmax||z>cmax)
		{
			cout<<"Error! People entering or exiting cannot be more than max capacity "<<k;
			continue;
		}
		v.push_back(input(x,y,z));
	}
	sort(v.begin(),v.end(),compare);
	for(i=0;i<v.size();++i)
	{
		v1.push_back(v[i]); //duplicate the vector
	}
	n=v.size();
	int beg=0;
	int end=n-1;
	int pos=binarysearch(v,beg,end,k);
	if(pos==-1)
    exit(1);
 	cout<<"\n\nPossibility 1 (Upwards First) (Ignoring Lift Capacity)\n";
 	for(int i=pos;i<n;++i)
	{
		cout<<"\n";
		cout<<v[i].fno<<" "<<v[i].ent<<" "<<v[i].ex;
	}
	for(int i=pos-1;i>=0;--i)
	{
		cout<<"\n";
		cout<<v[i].fno<<" "<<v[i].ent<<" "<<v[i].ex;
	}
	cout<<"\n\nPossibility 2 (Downwards First) (Ignoring Lift Capacity) \n";
		for(int i=pos;i>=0;--i)
	{
		cout<<"\n";
		cout<<v[i].fno<<" "<<v[i].ent<<" "<<v[i].ex;
	}
	for(int i=pos+1;i<n;++i)
	{
		cout<<"\n";
		cout<<v[i].fno<<" "<<v[i].ent<<" "<<v[i].ex;
	}
	c=0;
	checkcount(v);  //Assuming after completion, nobody stays in lift. i.e. people entering=people leaving.
	cout<<"\n\nPossibility 1 (Upwards first) (Considering Lift Capacity) \n\n";
	while(check(v)) //Assuming People inside leave first and then people get in.
	{
		for(i=pos;i<n-1;++i)
		{
			if(v[i].ent!=0 || v[i].ex!=0)
			{
				if(v[i].ex>=c)
				{
					l=c;
					v[i].ex=v[i].ex-l;
					c=0;
				}
				else
				{
					l=v[i].ex;
					c=c-l;
					v[i].ex=0;
				}
				if((v[i].ent+c)>=cmax)
				{
					e=(cmax-c);
					v[i].ent=v[i].ent-e;
					c=cmax;				
				}
				else
				{
					e=v[i].ent;
					c=c+e;
					v[i].ent=0;
				}
				if(l==0&&e==0)
				cout<<" ";
				else
				cout<<"\n visit floor "<<v[i].fno<<"\t\t people leaving: "<<l<<"\t people entering: "<<e<<"\t people in lift: "<<c<<"\t yet to enter from this floor: "<<v[i].ent<<"\t yet to leave to this floor: "<<v[i].ex;
			}
		}
		for(i=n-1;i>0;--i)
		{
			if(v[i].ent!=0 || v[i].ex!=0)
			{
				if(v[i].ex>=c)
				{
					l=c;
					v[i].ex=v[i].ex-l;
					c=0;
				}
				else
				{
					l=v[i].ex;
					c=c-l;
					v[i].ex=0;
				}
				if((v[i].ent+c)>=cmax)
				{
					e=(cmax-c);
					v[i].ent=v[i].ent-e;
					c=cmax;				
				}
				else
				{
					e=v[i].ent;
					c=c+e;
					v[i].ent=0;
				}
				if(l==0&&e==0)
				cout<<" ";
				else
				cout<<"\n visit floor "<<v[i].fno<<"\t\t people leaving: "<<l<<"\t people entering: "<<e<<"\t people in lift: "<<c<<"\t yet to enter from this floor: "<<v[i].ent<<"\t yet to leave to this floor: "<<v[i].ex;
			}
		}
		for(i=0;i<pos;++i)
		{
			if(v[i].ent!=0 || v[i].ex!=0)
			{
				if(v[i].ex>=c)
				{
					l=c;
					v[i].ex=v[i].ex-l;
					c=0;
				}
				else
				{
					l=v[i].ex;
					c=c-l;
					v[i].ex=0;
				}
				if((v[i].ent+c)>=cmax)
				{
					e=(cmax-c);
					v[i].ent=v[i].ent-e;
					c=cmax;				
				}
				else
				{
					e=v[i].ent;
					c=c+e;
					v[i].ent=0;
				}
				if(l==0&&e==0)
				cout<<" ";
				else
				cout<<"\n visit floor "<<v[i].fno<<"\t\t people leaving: "<<l<<"\t people entering: "<<e<<"\t people in lift: "<<c<<"\t yet to enter from this floor: "<<v[i].ent<<"\t yet to leave to this floor: "<<v[i].ex;
			}
		}
	}
	cout<<"\n\nPossibility 2 (Downwards first) (Considering Lift Capacity) \n\n";	
	c=0;
	while(check(v1))
	{
		for(i=pos;i>0;--i)
		{
			if(v1[i].ent!=0 || v1[i].ex!=0)
			{
				if(v1[i].ex>=c)
				{
					l=c;
					v1[i].ex=v1[i].ex-l;
					c=0;
				}
				else
				{
					l=v1[i].ex;
					c=c-l;
					v1[i].ex=0;
				}
				if((v1[i].ent+c)>=cmax)
				{
					e=(cmax-c);
					v1[i].ent=v1[i].ent-e;
					c=cmax;				
				}
				else
				{
					e=v1[i].ent;
					c=c+e;
					v1[i].ent=0;
				}
				if(l==0&&e==0)
				cout<<" ";
				else
				cout<<"\n visit floor "<<v1[i].fno<<"\t\t people leaving: "<<l<<"\t people entering: "<<e<<"\t people in lift: "<<c<<"\t yet to enter from this floor: "<<v1[i].ent<<"\t yet to leave to this floor: "<<v1[i].ex;
			}
		}
		for(i=0;i<n-1;++i)
		{
			if(v1[i].ent!=0 || v1[i].ex!=0)
			{
				if(v1[i].ex>=c)
				{
					l=c;
					v1[i].ex=v1[i].ex-l;
					c=0;
				}
				else
				{
					l=v1[i].ex;
					c=c-l;
					v1[i].ex=0;
				}
				if((v1[i].ent+c)>=cmax)
				{
					e=(cmax-c);
					v1[i].ent=v1[i].ent-e;
					c=cmax;				
				}
				else
				{
					e=v1[i].ent;
					c=c+e;
					v1[i].ent=0;
				}
				if(l==0&&e==0)
				cout<<" ";
				else
				cout<<"\n visit floor "<<v1[i].fno<<"\t\t people leaving: "<<l<<"\t people entering: "<<e<<"\t people in lift: "<<c<<"\t yet to enter from this floor: "<<v1[i].ent<<"\t yet to leave to this floor: "<<v1[i].ex;
			}
		}
		for(i=n-1;i>pos;--i)
		{
			if(v1[i].ent!=0 || v1[i].ex!=0)
			{
				if(v1[i].ex>=c)
				{
					l=c;
					v1[i].ex=v1[i].ex-l;
					c=0;
				}
				else
				{
					l=v1[i].ex;
					c=c-l;
					v1[i].ex=0;
				}
				if((v1[i].ent+c)>=cmax)
				{
					e=(cmax-c);
					v1[i].ent=v1[i].ent-e;
					c=cmax;				
				}
				else
				{
					e=v1[i].ent;
					c=c+e;
					v1[i].ent=0;
				}
				if(l==0&&e==0)
				cout<<" ";
				else
				cout<<"\n visit floor "<<v1[i].fno<<"\t\t people leaving: "<<l<<"\t people entering: "<<e<<"\t people in lift: "<<c<<"\t yet to enter from this floor: "<<v1[i].ent<<"\t yet to leave to this floor: "<<v1[i].ex;
			}
		}	
	}	
}
