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
void schedule(int fno,int *ent,int *ex,int cmax,int *c)
{ 
	int l,e;
	if(*ent!=0 || *ex!=0)
			{
				if(*ex>=*c)
				{
					l=*c;
					*ex=*ex-l;
					*c=0;
				}
				else
				{
					l=*ex;
					*c=*c-l;
					*ex=0;
				}
				if((*ent+*c)>=cmax)
				{
					e=(cmax-*c);
					*ent=*ent-e;
					*c=cmax;				
				}
				else
				{
					e=*ent;
					*c=*c+e;
					*ent=0;
				}
				if(l==0&&e==0)
				cout<<" ";
				else
				cout<<"\n visit floor "<<fno<<"\t\t people leaving: "<<l<<"\t people entering: "<<e<<"\t people in lift: "<<*c<<"\t yet to enter from this floor: "<<*ent<<"\t yet to leave to this floor: "<<*ex;
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
	cout<<"\nEnter maximum lift capacity (if you want to schedule without considering maximum lift capacity, enter 0) \t";
	cin>>cmax;
	cout<<"\nEnter floor number,number of people entering at floor,number of people leaving at floor in order (Include the starting floor). Enter 3 0s to stop accepting input. Note that total people entering lift should be equal to total people leaving lift.\n\n";
	while(cin>>x>>y>>z)
	{
		if(x==0)
		break;
		v.push_back(input(x,y,z));
	}
	sort(v.begin(),v.end(),compare);
	checkcount(v);  //Assuming after completion, nobody stays in lift. i.e. people entering=people leaving.
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
	c=0;
	if(cmax==0)
	{
		for(i=0;i<n;++i)
		cmax=cmax+v[i].ent;
		++cmax;
	}//if you make cmax more than all people entering lift, then v[i].ent+c is always> cmax, so all v[i].ent people can enter at a floor the first time it is visited and it effectively reduces to the case where max lift capacity is ignored.
	
	if(v[0].fno==k)
	{
		cout<<"\n\nOnly Possibility (Upwards first) \n\n";
	}
	if(k==v[n-1].fno)
	{
		cout<<"\n\nOnly Possibility (Downwards first) \n\n";
	}
	if(k!=v[0].fno&&k!=v[n-1].fno)
	{
		cout<<"\n\nPossibility 1 (Upwards first) \n\n";
	}
	while(check(v)) //Assuming People inside leave first and then people get in.
	{
		if(k==v[n-1].fno)
		break;
		for(i=pos;i<n-1;++i)
		{
			schedule(v[i].fno,&v[i].ent,&v[i].ex,cmax,&c);
		}
		for(i=n-1;i>0;--i)
		{
			schedule(v[i].fno,&v[i].ent,&v[i].ex,cmax,&c);
		}
		for(i=0;i<pos;++i)
		{
			schedule(v[i].fno,&v[i].ent,&v[i].ex,cmax,&c);
		}
	}
	if(k!=v[0].fno&&k!=v[n-1].fno)
	{
		cout<<"\n\nPossibility 2 (Downwards first) \n\n";		
	}
	c=0;
	while(check(v1))
	{
		if(k==v1[0].fno)
		break;
		for(i=pos;i>0;--i)
		{
			schedule(v1[i].fno,&v1[i].ent,&v1[i].ex,cmax,&c);
		}
		for(i=0;i<n-1;++i)
		{
			schedule(v1[i].fno,&v1[i].ent,&v1[i].ex,cmax,&c);
		}
		for(i=n-1;i>pos;--i)
		{
			schedule(v1[i].fno,&v1[i].ent,&v1[i].ex,cmax,&c);
		}	
	}	
}
