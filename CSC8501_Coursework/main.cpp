#include "Term.h"

using namespace std;

int main()
{
	cout << "Enter the Expression: ";
	string polyStr("");
	cin >> polyStr;

	cout << "Your Expression is: " << polyStr << endl;

	polyStr.erase(remove_if(polyStr.begin(), polyStr.end(), isspace), polyStr.end());

	Term term = Term();
	term.tryParsing(polyStr.c_str());

	cout << term;
}