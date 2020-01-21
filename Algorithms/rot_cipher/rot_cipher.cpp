#include <iostream>
#include <string>
#include <cassert>

using namespace std;

string rotationalCipher(string input, int rotationFactor) {
    // Write your code here
    // A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    string ret(input.size(), '\0');
    for (int i = 0; i < input.size(); ++i)
    {
        if ('A' <= input[i] && input[i] <= 'Z')
        {
            int index = (input[i] - 'A' + rotationFactor) % 26;
            ret[i] = 'A' + index;
        }
        else if ('a' <= input[i] && input[i] <= 'z')
        {
            int index = (input[i] - 'a' + rotationFactor) % 26;
            ret[i] = 'a' + index;
        }
        else if ('0' <= input[i] && input[i] <= '9')
        {
            int index = (input[i] - '0' + rotationFactor) % 10;
            ret[i] = '0' + index;
        }
        else
        {
            ret[i] = input[i];
        }
    }

    return ret;
}

int main()
{
    string input_1 = "All-convoYs-9-be:Alert1.";
    int rotationFactor_1 = 4;
    string expected_1 = "Epp-gsrzsCw-3-fi:Epivx5.";
    string output_1 = rotationalCipher(input_1, rotationFactor_1);
    assert(output_1 == expected_1);

    string input_2 = "abcdZXYzxy-999.@";
    int rotationFactor_2 = 200;
    string expected_2 = "stuvRPQrpq-999.@";
    string output_2 = rotationalCipher(input_2, rotationFactor_2);
    assert(output_2 == expected_2);
}
