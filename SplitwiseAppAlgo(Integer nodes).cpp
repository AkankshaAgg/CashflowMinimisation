//Money Splitwise algorithm
//Using integer nodes
#include<iostream>
#include<set>
using namespace std;

int main(){
	
	int no_of_transactions, friends;
	cin>>no_of_transactions>>friends;
	
	int x,y,amount;
	
	//1-D array to store the net amount that each person will have to take at the end
	int net[10000] = {0};
	while(no_of_transactions--){
		cin>>x>>y>>amount;
		net[x] -= amount;
		net[y] += amount;
	}
	
	//multiple transactions or net balance of same value are possible
	multiset<int> m;
	
	//Init a list and sort it using multiset
	for(int i=0;i<friends;i++){
		//if some transactions are there
		if(net[i]!=0){
			m.insert(net[i]);
		}
	}
	
	//Applying greedy approach
	//Person with the highest debt will give money to person with highest crediter
	//Pop out two person (Left & Right) and try to settle them
	int count = 0;
	while(!m.empty()){
		auto low = m.begin();
		auto high = prev(m.end());
		
		int debit = *low;
		int credit = *high;
		
		//Remove these elements
		m.erase(low);
		m.erase(high);
		
		//settlement
		int settlement_amount = min(-debit, credit);
		count++;
		
		//settlement_amount will be either equal to debit or credit
		//so it will make sure at least one of them is 0.
		//settlement_amount from debiter to crediter
		debit += settlement_amount;
		credit -= settlement_amount;
		
		if(debit!=0){
			m.insert(debit);
		}
		if(credit!=0){
			m.insert(credit);
		}
	}
	
	cout<<count<<endl;
	
	return 0;
}
