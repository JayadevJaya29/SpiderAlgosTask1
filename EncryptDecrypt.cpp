#include<iostream>
#include<cctype>
#include<vector>
#include<bits/stdc++.h>
#include<cstring>
using namespace std;
string encrypt(string s,int k)
{
	for(int i=0;s[i]!='\0';++i)
	{
		if(isupper(s[i]))
		{
			if(s[i]<=char(90-k))
			s[i]+=k;
			else
			s[i]+=(k-26);
		}
		if(islower(s[i]))
		{
			if(s[i]<=char(122-k))
			s[i]+=k;
			else
			s[i]+=(k-26);
		}
	}
	return s;
}
string decrypt(string s,int k)
{
	for(int i=0;s[i]!='\0';++i)
	{
		if(isupper(s[i]))
		{
			if(s[i]>=char(65+k))
			s[i]+=-k;
			else
			s[i]+=(26-k);
		}
		if(islower(s[i]))
		{
			if(s[i]>=char(97+k))
			s[i]+=-k;
			else
			s[i]+=(26-k);
		}
	}
	return s;
}
int main()
{
	vector <string> v;
	int n,k,i=0;
	string x;
	cout<<"\nenter number of test cases (n) and key(k) for all test cases\n";
	cin>>n>>k;
	cout<<"\nenter "<<n<<" cases to be encrypted first and then enter "<<n<<" cases to be decrypted \n";
	while(i<2*n)
	{
		cin>>x;
		v.push_back(x);
		++i;
	}
	for(i=0;i<n;++i)
	{
		cout<<"\nCipherText#"<<i+1<<": "<<encrypt(v[i],k);
	}
	for(i=n;i<2*n;++i)
	{
		cout<<"\nPlainText#"<<i-n+1<<":  "<<decrypt(v[i],k);
	}
    return 0;
}
