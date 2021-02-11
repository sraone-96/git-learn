#include<bits/stdc++.h>
using namespace std;
//testing tracking with git------> simple case
class wallet
{
private:

public:
	string name;
	double bal;
	static int id;

};

int wallet::id=0;

class user: public wallet
{

private:
	vector<string> trans;
public:
	static map<string,user*> m;
	static map<int,user*> m2;
	
	string name;
	double bal;
	int idn;

	user(string acct_name, double amount)
	{
		if(m.find(acct_name)!=m.end())
		{
			cout<<"user exists"<<endl;
			this->~user();		// call destructor
			return;
		}

		name = acct_name;
		bal = amount + 0.00099;
		m[name] = this;
		idn = id;
		m2[idn] = this;
		id++;
	}



void credit(user& ac2, double amt)					// transfer amount from ac1 to ac2
{
	// for adding amount
	bal+= amt;
	string report = ac2.name;
	report += " credit "+to_string(amt);
	trans.push_back(report);
}


void debit(user& ac2, double amt)
{
	bal-= amt;				// amount from sravans accnt; registring transaction is on Osama
	string report = ac2.name;
	report += " debit "+to_string(amt);
	trans.push_back(report);

}

void transfer(user& ac2, double amt)
{

	if(bal<amt || bal<0)
		{cout<<"insufficient balance. Transaction failed"<<endl;return;}

	debit(ac2,amt);					// from instance of sravan (osama,100)
	ac2.credit(*this,amt);			// sravan -> osama 100

	if(this->bal==ac2.bal)				// offer 1
		{
			// credit(*this,10);
			// ac2.credit(ac2,10);
			bal+=10;
			ac2.bal+=10;
		}

}


void statement()				// for statement
{

	cout<<"statement "<<name<<endl;
	for(int i=0;i<trans.size();i++)
		cout<<trans[i]<<endl;
}

void overview()
	{

	for(auto it:m)
	{
		if(it.second==NULL)
			continue;

		cout<<it.second->name<<" "<<it.second->bal<<endl;
	}

	}
// ------------------------------------------------------------------------------------------------

static bool cmpfunc(const vector<double> a, const vector<double> b)
{
	//a[0]= number of trasactions
	//a[1]= balance of a
	//a[2]= id
	
	if(a[0]<b[0])
		return false;
	else if(a[0]>b[0])
		return true;
	else
	{
		if(a[1]<b[1])
			return false;
		else if(a[1]>b[1])
			return true;
		else
		{
			return a[2]<b[2];
		}
	}

	return true;
}

void offer2()
{
	vector<vector<double>> t;				// transactions, total bal, id
	for(auto it:m)
	{
		if(it.second==NULL)
			continue;

		vector<double> temp;

		temp.push_back(it.second->trans.size());
		temp.push_back(it.second->bal);
		temp.push_back(it.second->idn);

		t.push_back(temp);	
	}

	sort(t.begin(),t.end(),cmpfunc);
	return update_balances(t);
}

void update_balances(vector<vector<double>> &t)
{
for(int i=0;i<t.size() && i<3;i++)
	{
		int amt;
		if(i==0)amt=10;
		else if(i==1)amt=5;
		else if(i==2)amt=2;

		int id = t[i][2];
		// cout<<m2[id]->name<<" "<<m2[id]->trans.size()<<endl;
		m2[id]->credit(*m2[id],amt);

	}

}

};

map<string,user*> user::m = {{"NULL",NULL}};
map<int,user*> user::m2 = {{-1, NULL}};


int main()
{

	// wallet w;
	// user a("a",100);
	// user b("b",100);
	// user c("c",100);
	
	// // cout<<a.idn<<endl;
	// // cout<<b.idn<<endl;
	// // cout<<c.idn<<endl;

	// a.transfer(b,100);
	// a.transfer(b,100);
	// c.transfer(b,100);
	// a.overview();

	// cout<<"later"<<endl;
	// a.offer2();
	// a.overview();
		
user Harry("Harry",100);
user Ron("Ron",95.7);
user Hermione("Hermione",104);
user Albus("Albus", 200);
user Draco("Draco",500);

Harry.overview();

 Albus.transfer(Draco,30);
 Hermione.transfer(Harry,2);
 Albus.transfer(Ron,5);
 cout<<endl;

Harry.overview();
Harry.offer2();
cout<<endl;
Harry.overview();


Harry.statement();
Ron.statement();



	//cretae wallet
	// statement
	// transfer
	// offeer1
	// overview

	//offer2

	return 0;
}


