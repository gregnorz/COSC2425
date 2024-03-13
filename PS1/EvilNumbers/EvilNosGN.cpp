// EvilNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

// ----------------------------------------------------------------------------
//
// Handles the conversion of y/n for us. We don't do much checking thus converting
// anything not 'y' or 'Y' to "false" 
//

inline bool yesNoToBool( char input )
{
	input = static_cast<char>(std::toupper( input ));
	return ('Y' == input);
}

// ----------------------------------------------------------------------------

int main()
{
	char yesOrNo = 'y';
	do
	{
		int decimalNumber = -1;
		while ( decimalNumber < 0 || decimalNumber > 1000 )
		{
			cout << "Enter a number [0 - 1000]: ";
			cin >> decimalNumber;
		}

		cout << "\nRun again? (Y/N): ";
		cin >> yesOrNo;
		cout << endl;
	}
	while ( yesNoToBool( yesOrNo ) );
}