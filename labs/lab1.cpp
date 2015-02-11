#include <iostream>

using namespace std;

int main (int argc, char * argv[]){
	int number, sum;
	sum = 0;
	
	cout << "x" << "\t" << "x^2" << "	" << "Current Sum"<< endl;
	cout << "=" << "\t" << "===" << "	" << "===========" << endl;

	//get numbers from somewhere
	while (cin >> number) {
		sum = sum + number;
		cout<< number <<"	"<< number*number << "	"<< sum << endl;
	}
	return 0;
}