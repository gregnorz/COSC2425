#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <sstream>

// ----------------------------------------------------------------------------

using namespace std;

// Use the following website to test this program:
// https://www.unitconverters.net/numbers-converter.html

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
	input = static_cast<char>( std::toupper(input) );
	return ('Y' == input);
}

// ----------------------------------------------------------------------------

inline bool isPalindrome( const string& testString )
{
	string reversedString( testString );

	// I will always use built-in functionality before rolling my own. Prove that
	// this is slow via profiling; if positive, I will see how I can optimize the code.
	reverse( reversedString.begin(), reversedString.end() );

	return ( testString == reversedString);
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

		stringstream basesStream;
		for ( unsigned int baseNum = 2; baseNum <= 20; ++baseNum )
		{
			string convertedNum( convertDecimalToBase(decimalNumber, baseNum) );

			// Uncomment below for testing each base in our range
			// cout << decimalNumber << " converted to base " << baseNum << " = " << convertedNum << endl;

			if ( isPalindrome( convertedNum ) )
			{
				// cout << "The number " << decimalNumber << " is a palindrome in base(s): " << baseNum << endl;
				basesStream << baseNum << " ";
			}
		}

		if ( basesStream.str().length() == 0 )
		{
			basesStream << "NONE";
		}

		cout << "The number " << decimalNumber << " is a palindrome in base(s): " 
			 << basesStream.str() 
			 << endl;

		cout << "\nRun again? (Y/N): ";
		cin >> yesOrNo;
		cout << endl;
	}
	while ( yesNoToBool(yesOrNo) );

	return 0;
}