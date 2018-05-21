#include<iostream>
#include<algorithm>
#include<vector>
using namespace std; //Uses C++11 Standard
int binarysearch(vector <int> v,int beg,int end,int k)
{
	int mid=(beg+end)/2;
	if(v[mid]==k)
	{
		return mid;
	}
	else if(v[mid]>k)
	{
		end=mid-1;
		return binarysearch(v,beg,end,k);
	}
	else if(v[mid]<k)
	{
		beg=mid+1;
		return binarysearch(v,beg,end,k);
	}
	return -1;
}
int main()
{
	vector <int> v;
	int x,k;
	cout<<"Enter the floor to start from \t";
	cin>>k;
	cout<<"\nStart Entering floors to be visited from "<<k<<". Enter 'n' to stop entering Inputs. \t";
	while(cin>>x && x!='n')
	v.push_back(x);
	v.push_back(k);
	sort(v.begin(),v.end());
	int n=v.size();	
	int beg=0;
	int end=n-1;
	int pos=binarysearch(v,beg,end,k);//returns position of k in sorted vector 
	int d1=2*(*max_element(v.begin(),v.end()))-*min_element(v.begin(),v.end())-k;//upwards first.total distance=(max-min)+(max-k)
	int d2=*max_element(v.begin(),v.end())+k-2*(*min_element(v.begin(),v.end()));//downwards first.total distance=(k-min)+(max-min)
	cout<<"\nPossibility 1 (Upwards First) \n";
	for(int i=pos;i<n;++i)
	cout<<v[i]<<"\t";
	for(int i=pos-1;i>=0;--i)
	cout<<v[i]<<"\t";
	cout<<"\nTotal Distance = \t"<<d1;
	cout<<"\nPossibility 2 (Downwards First) \n";
	for(int i=pos;i>=0;--i)
	cout<<v[i]<<"\t";
	for(int i=pos+1;i<n;++i)
	cout<<v[i]<<"\t";
	cout<<"\nTotal Distance = \t"<<d2;
	return 0;
}
