//Money Splitwise algorithm
//Using string nodes
//Output should also show transactions
#include<iostream>
#include<set>
#include<map>
using namespace std;

class person_compare{
	public:
		bool operator()(pair<string,int> p1, pair<string, int> p2){
			return p1.second < p2.second;
		}
};

int main(){
	//map will store net balance of each person
	
	int no_of_transactions, friends;
	cin>>no_of_transactions>>friends;
	
	string x,y;
	int amount;
	
	map<string, int> net;
	
	while(no_of_transactions--){
		cin>>x>>y>>amount;
		//if key doesn't exist
		if(net.count(x)==0){
			net[x] = 0;
		}
		
		if(net.count(y)==0){
			net[y] = 0;
		}
		net[x] -= amount;
		net[y] += amount;
	}
	
	//Iterate over the persons, add those person in the multiset who have non-zero net
	multiset<pair<string, int>, person_compare> m;
	for(auto p: net){
		string person = p.first;
		int amount = p.second;
		
		//by default, multiset compares based on first parameter.
		//using person_compare comparison class
		if(net[person]!=0){
			m.insert(make_pair(person, amount));
		}
	}
	
	//settlements (start & end)
	int count = 0;
	while(!m.empty()){
		auto low = m.begin();
		auto high = prev(m.end());
		
		int debit = low->second;
		string debit_person = low->first;
		
		int credit = high->second;
		string credit_person = high->first;
		
		//pop them out
		m.erase(low);
		m.erase(high);
		
		int settled_amount = min(-debit, credit);
		
		debit += settled_amount;
		credit -= settled_amount;
		
		//Printing the transaction between people
		cout<<debit_person<<" will pay "<<settled_amount<<" to "<<credit_person<<endl;
		
		if(debit!=0){
			m.insert(make_pair(debit_person, debit));
		}
		if(credit!=0){
			m.insert(make_pair(credit_person, credit));
		}
		count++;
	}
	cout<<count<<endl;
	return 0;
}
