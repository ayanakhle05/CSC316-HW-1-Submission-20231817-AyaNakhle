#include <iostream>
#include <string>
#include <ctime>
#include "picosha2.h"

using namespace std;

string sha256(string text)
{
    return picosha2::hash256_hex_string(text);
}

int main()
{
    string username1, password1;
    string username2, password2;
    string userID1, userID2;
    string hash1, hash2;
    string salt1, salt2;
    string saltedHash1, saltedHash2;

    cout << "       PASSWORD PROTECTION SYSTEM\n";

    cout << "===== REGISTER USER 1 =====\n\n";

    cout << "Enter username: ";
    cin >> username1;

    cout << "Enter password: ";
    cin >> password1;

    string timestamp1 = to_string(time(0));//generate timestamp for user 1

    userID1 = sha256(username1 + timestamp1).substr(0, 8);//generate user id

    hash1 = sha256(password1);//table 2: hash pass


    salt1 = sha256(username1 + userID1 + timestamp1);//generate salt

    saltedHash1 = sha256(salt1 + password1);//table 3: hash salt and pass

    cout << "\n===== REGISTER USER 2 =====\n\n";

    while (true)
    {
        cout << "Enter username: ";
        cin >> username2;

        if (username2 == username1)
        {
            cout << "\nUsername already exists!";
            cout << "\nPlease enter a different username.\n\n";
        }
        else
        {
            break;
        }
    }

    cout << "Enter password: ";
    cin >> password2;
    
    string timestamp2 = to_string(time(0));

    userID2 = sha256(username2 + timestamp2).substr(0, 8);

    hash2 = sha256(password2);

    salt2 = sha256(username2 + userID2 + timestamp2);

    saltedHash2 = sha256(salt2 + password2);

    cout << "\n\n-------------------------\n";
    cout << "TABLE 1 - PLAIN PASSWORD\n";
    cout << "-------------------------\n";

    cout << "\nUser ID: " << userID1;
    cout << "\nUsername: " << username1;
    cout << "\nPassword: " << password1;

    cout << "\n\nUser ID: " << userID2;
    cout << "\nUsername: " << username2;
    cout << "\nPassword: " << password2;

    cout << "\n\n-------------------------\n";
    cout << "TABLE 2 - HASHED PASSWORD\n";
    cout << "-------------------------\n";

    cout << "\nUser ID: " << userID1;
    cout << "\nUsername: " << username1;
    cout << "\nPassword Hash: " << hash1;

    cout << "\n\nUser ID: " << userID2;
    cout << "\nUsername: " << username2;
    cout << "\nPassword Hash: " << hash2;

    cout << "\n\n-------------------------\n";
    cout << "TABLE 3 - SALTED PASSWORD\n";
    cout << "-------------------------\n";

    cout << "\nUser ID: " << userID1;
    cout << "\nUsername: " << username1;
    cout << "\nSalt: " << salt1;
    cout << "\nSalted Hash: " << saltedHash1;

    cout << "\n\nUser ID: " << userID2;
    cout << "\nUsername: " << username2;
    cout << "\nSalt: " << salt2;
    cout << "\nSalted Hash: " << saltedHash2;

    //login
    cout << "               \n\nLOGIN\n";


    string loginUsername;
    string loginPassword;

    cout << "\nEnter username: ";
    cin >> loginUsername;

    cout << "Enter password: ";
    cin >> loginPassword;

    //find user
    bool userFound = false;

    string correctPassword;
    string correctHash;
    string correctSalt;
    string correctSaltedHash;

    if (loginUsername == username1)
    {
        userFound = true;

        correctPassword = password1;
        correctHash = hash1;
        correctSalt = salt1;
        correctSaltedHash = saltedHash1;
    }
    else if (loginUsername == username2)
    {
        userFound = true;

        correctPassword = password2;
        correctHash = hash2;
        correctSalt = salt2;
        correctSaltedHash = saltedHash2;
    }

    if (userFound == false)
    {
        cout << "\nUsername not found.";
        cout << "\nLogin failed!\n";

        return 0;
    }
    //verify first table
    bool table1Match = false;

    if (loginPassword == correctPassword)
    {
        table1Match = true;
    }
    //verify second table
    bool table2Match = false;

    if (sha256(loginPassword) == correctHash)
    {
        table2Match = true;
    }
    //verify third table
    bool table3Match = false;

    if (sha256(correctSalt + loginPassword) == correctSaltedHash)
    {
        table3Match = true;
    }

    cout << "      \n\nLOGIN VERIFICATION RESULTS\n";

    cout << "\nTable 1 - Plain Password: ";

    if (table1Match)
        cout << "PASSWORD MATCHES";
    else
        cout << "PASSWORD DOES NOT MATCH";

    cout << "\nTable 2 - Hashed Password: ";

    if (table2Match)
        cout << "PASSWORD MATCHES";
    else
        cout << "PASSWORD DOES NOT MATCH";

    cout << "\nTable 3 - Salted Password: ";

    if (table3Match)
        cout << "PASSWORD MATCHES";
    else
        cout << "PASSWORD DOES NOT MATCH";

    cout << "          \n\nFINAL LOGIN RESULT\n";

    if (table1Match && table2Match && table3Match)
    {
        cout << "Login successful!\n";
    }
    else
    {
        cout << "Login failed!\n";
    }

    return 0;
}

