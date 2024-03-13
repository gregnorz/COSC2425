// BasePalindromes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// ----------------------------------------------------------------------------
//
// The assignment locks us to bases 2-20, and this vector represents the
// alphanumeric values for this range.
//

const vector<char> digitVec{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

// ----------------------------------------------------------------------------
//
// Handles the conversion of y/n for us. We don't do much checking thus converting
// anything not 'y' or 'Y' to "false" 
//

inline bool yesNoToBool( char input )
{
	input = std::toupper( input );
	return ('Y' == input);
}

// ----------------------------------------------------------------------------

string convertDecimalToBase( unsigned int decimalNum, unsigned int baseNum )
{
	// Range check for the lazy
	// 
	if ( baseNum < 2 || baseNum > 20 )
	{
		return "The base must be between 2 and 20.";
	}

	string returnNumber; // Don't init to empty string or the append gets thrown off by 1
	while ( decimalNum > 0 )
	{
		unsigned int remainder = decimalNum % baseNum;
		returnNumber = digitVec[remainder] + returnNumber;
		decimalNum /= baseNum;
	}

	return returnNumber;
}

// ----------------------------------------------------------------------------

int main()
{
	char yesOrNo = 'y';
	do
	{
		unsigned int decimalNumber = 0;
		cout << "Enter a number [1 - 1000000]: ";
		cin >> decimalNumber;

		// Basic error checking where we bail out instead of trying to loop. A bit lazy, I know.
		if ( decimalNumber < 1 || decimalNumber > 1000000 )
		{
			cerr << "Try again! Please enter a number between 1 and 1000000." << endl;
			return 1;
		}

		for ( unsigned int baseNum = 2; baseNum <= 20; ++baseNum )
		{
			string convertedNum( convertDecimalToBase(decimalNumber, baseNum) );

			// Uncomment below for testing each base in our range
			cout << decimalNumber << " converted to base " << baseNum << " = " << convertedNum << endl;
		}
		cout << "The number " << decimalNumber << " is a palindrome in base(s): " << endl;

		cout << "\nRun again? (Y/N): ";
		cin >> yesOrNo;
		cout << endl;
	}
	while ( yesNoToBool(yesOrNo) );

	return 0;
}