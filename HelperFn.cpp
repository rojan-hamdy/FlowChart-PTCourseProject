
#include "HelperFn.h"

bool IsValue(string input)
{
	if (input.empty()) return false;
	bool digit = false;
	bool point = false;
	int i = 0;
	if (input[i] == '-') i++; //increment index if negative sign is present
	for (; i < input.size(); i++) {
		if (input[i] >= '0' && input[i] <= '9') digit = true; // at least one digit must be present
		else if (input[i] == '.') { // check for decimal point
			if (point) return false; // more than one decimal point is not allowed
			point = true;
		}
		else return false;
	}

	return digit; // return true only if at least one digit is present
}

bool IsVariable(string input)
{
	if (input.empty()) return false;
	else if ((input[0] == '_') || ((input[0] >= 'a') && (input[0] <= 'z')) || ((input[0] >= 'A') && (input[0] <= 'Z')))  //check if the first index in varaible name is valid 
	{
		int i = 1;
		for (; i < input.size(); i++)     // Loop checks the validity of the remaining indices
		{
			if ((input[i] == '_') || ((input[i] >= 'a') && (input[i] <= 'z')) || ((input[i] >= 'A') && (input[i] <= 'Z')) || ((input[i] >= '0') && (input[i] <= '9')))
			{
				continue;
			}
			else return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

OpType ValueOrVariable(string input)
{
	if (IsValue(input)) return VALUE_OP; // Check if the input is a valid value
	else if (IsVariable(input)) return VARIABLE_OP; // Check if the input is a valid variable
	else
		return INVALID_OP; // Return INVALID_OP if neither
}

double string_to_double(string str)
{
    double num1 = 0;
    int digitcount = str.size();
    int placevalue = 1;
    double afterpointplace = 0.1;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            digitcount = i; break;
        }
    }
    for (int i = digitcount - 1; i >= 0; i--)
    {
        switch (str[i])
        {
        case '0':
            break;
        case '1':
            num1 += placevalue; break;
        case '2':
            num1 += 2 * placevalue; break;
        case '3':
            num1 += 3 * placevalue; break;
        case '4':
            num1 += 4 * placevalue; break;
        case '5':
            num1 += 5 * placevalue; break;
        case '6':
            num1 += 6 * placevalue; break;
        case '7':
            num1 += 7 * placevalue; break;
        case '8':
            num1 += 8 * placevalue; break;
        case '9':
            num1 += 9 * placevalue; break;
        }
        placevalue *= 10;
    }

    for (int i = digitcount + 1; i < str.size(); i++)
    {
        switch (str[i])
        {
        case '0':
            break;
        case '1':
            num1 += afterpointplace; break;
        case '2':
            num1 += 2 * afterpointplace; break;
        case '3':
            num1 += 3 * afterpointplace; break;
        case '4':
            num1 += 4 * afterpointplace; break;
        case '5':
            num1 += 5 * afterpointplace; break;
        case '6':
            num1 += 6 * afterpointplace; break;
        case '7':
            num1 += 7 * afterpointplace; break;
        case '8':
            num1 += 8 * afterpointplace; break;
        case '9':
            num1 += 9 * afterpointplace; break;
        }
        afterpointplace *= 0.1;
    }
    return num1;
}
