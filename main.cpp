/* 
Project 01: Ciphers Project
Course: CS 251, Spring 2024, UIC
System: Advanced zyLab, visual studio code
Author: Cuong Phuc Nguyen
*/

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function prototypes at the top of the file for function decomposition
// function encrypt text by using Caesar Cipher method
void Caesar_Cipher();
// function encrypt text by using Vigenere method
void Vigenere();
// return a vector contain Decrypted text 
vector<string> Decrypt_Caesar(vector<string> Text, vector<string>dictionary,string cipherText);
// separate cipher text into vector without space for Decryt_Caesar function
// return a vector contain words only
vector<string> separateWords(string cipherText);
// separate cipher text into vector including spaces
// return vector contain words and spaces
// function used to manage the space between words
vector<string> separateWords_spaces(string cipherText);
// using for search words in dictionary
// return -1 if the word is not found
int binarySearch(vector<string>dictionary,string word);
/**
 * Print instructions for using the program.
 */
void printMenu();
/**
 * Returns the 0-based index in the English alphabet where `c` appears,
 * or -1 if `c` is not an uppercase letter in the alphabet.
 *
 * For example:
 *  - `findIndexInAlphabet('A')` returns 0
 *  - `findIndexInAlphabet('D')` returns 3
 *  - `findIndexInAlphabet('+')` returns -1
 *  - `findIndexInAlphabet('a')` returns -1
 */
int findIndexInAlphabet(char c);
/**
 * Returns `c` rotated by `amount` many characters forward. If we run out
 * of letters in the alphabet, wrap around back to 'A'. This method
 * assumes that `c` is an uppercase letter.
 * For example:
 *  - `rot('A', 0)` returns 'A'
 *  - `rot('A', 1)` returns 'B'
 *  - `rot('Z', 1)` returns 'A'
 *  - `rot('A', 10)` returns 'K'
 *  - `rot('J', 25)` returns 'I'
 */
char rot(char c, int amount);
/**
 * Returns a new string in which every character has been rotated by `amount`
 * letters. Lowercase letters are converted to uppercase and rotated.
 * Non-alphabetic characters are left alone.
 * For example:
 *  `rot("A", 0)` returns "A"
 *  `rot("AA", 3)` returns "DD"
 *  `rot("HELLO", 0)` returns "HELLO"
 *  `rot("HELLO", 1)` returns "IFMMP"
 *  `rot("oh HEL-LO!", 1)` returns "PI IFM-MP!"
 */
string rot( string line, int amount);

int main() {
    string command;

    cout << "Welcome to Ciphers!" << endl;
    cout << "-------------------" << endl;
    cout << endl;

    do {
        printMenu();
        cout << endl
             << "Enter a command (case does not matter): ";

        // Use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        
        getline(cin, command);
        cout<<endl;
        if(command=="c"||command=="C"){
            Caesar_Cipher();
            getline(cin,command);
        }
        else if (command=="v" || command=="V"){
            Vigenere();
        }
        else if (command=="d"||command=="D"){
            string cipherText;
            string word;
            vector<string>Text;
            vector<string>Text_spaces;
            vector <string>dictionary;
            vector<string>Decrypted;
            cout<<"Enter the text to Caesar-cipher decrypt:"<<endl;
            getline(cin,cipherText);
            Text=separateWords(cipherText);
            ifstream file;
            file.open("dictionary.txt");
            while(file.eof()!=true){
                file>>word;
                dictionary.push_back(word);
            }
            Decrypted=Decrypt_Caesar(Text,dictionary, cipherText);
            if (Decrypted.size()==0){
                cout<<"No good decryptions found"<<endl;
            }
            else if (Text.size()==1){
                for (int i=0;i<Decrypted.size();i++){
                    cout<<Decrypted.at(i)<<endl;
                }
            }
            else{
                Text_spaces=separateWords_spaces(cipherText);
                int index=0;
                for (int x=0;x<Text_spaces.size();x++){
                    if (Text_spaces.at(x)==" "){
                        cout<<" ";
                    }
                    else{
                        cout<<Decrypted.at(index);
                        index++;
                    }
                }
                
            }
            
        }        
        else if(command == "x" || command == "X"){
            break;
        }// TODO_STUDENT: Execute non-exit commands

        cout << endl;

    } while (!(command == "x" || command == "X"));

    return 0;
}

void printMenu() {
    cout << "Ciphers Menu" << endl;
    cout << "------------" << endl;
    // Caesar Ciphers
    cout << "C - Encrypt with Caesar Cipher" << endl;
    cout << "D - Decrypt Caesar Cipher" << endl;
    // Vigenere
    cout << "V - Encrypt with Vigenère" << endl;
    // Utility
    cout << "X - Exit Program" << endl;
}

int findIndexInAlphabet(char c) {
    // TODO_STUDENT
    if(ALPHABET.find(c)>=0){
        return ALPHABET.find(c);
    }
    else{
        return -1;
    }
}

char rot(char c, int amount) {
    // TODO_STUDENT
    int currentChar=findIndexInAlphabet(c);
    for (int i =0; i<amount;i++){
        currentChar+=1;
    }
    while (currentChar>25){
        currentChar-=26;
    }
    currentChar+=65;
    c=currentChar;
    return c;
}
string rot(string line, int amount) {
    // TODO_STUDENT
    string newline;
    for (int i=0;i<line.size();i++){
        if (isalpha(line[i])){
            newline=newline+rot(toupper(line[i]),amount);
        }
        else{
            newline=newline+line[i];
        }
    }
    line=newline;
    return line;
}
void Caesar_Cipher(){
    int amount;
    string PlainText;
    string cipherText;
    cout<<"Enter the text to encrypt:"<<endl;
    getline(cin,PlainText);
    cout<<"Enter the number of characters to rotate by:"<<endl;
    cin>>amount;
    cipherText=rot(PlainText,amount);
    cout<<endl;
    cout<<cipherText;
    cout<<endl;
}
void Vigenere(){
    string PlainText;
    string cipherText="";
    string key;
    int indexKey=0;
    cout<<"Enter text to encrypt:"<<endl;
    getline(cin,PlainText);
    cout<<"Enter the Vigenère key:"<<endl;
    getline(cin,key);
    for (int i=0;i<PlainText.size();i++){
        if (PlainText[i]==' '){
            cipherText+=' ';
        }
        else if (!isalpha(PlainText[i])){
            cipherText+=PlainText[i];
        }
        else{
            if (key[indexKey]==' '){
                indexKey++;
            }
            cipherText=cipherText+rot(toupper(PlainText[i]),findIndexInAlphabet(toupper(key[indexKey])));
            if (indexKey==key.size()-1){
            indexKey=0;
        }
            else{
                indexKey++;
            }
        }
        
    }
    cout<<cipherText;
    cout<<endl;
}
vector<string> separateWords(string cipherText){
    vector<string>Text;
    string word="";
    for (int i=0;i<cipherText.size();i++){
        if (cipherText[i]==' '){
            if (word!=""){
                Text.push_back(word);
                word="";
            }
        }
        else if (!isalpha(cipherText[i])){
            Text.push_back(word);
            word="";
        }
        else if (i==cipherText.size()-1){
            word += toupper(cipherText[i]);
            Text.push_back(word);
            word="";
        }
        else{
            word+=toupper(cipherText[i]);
        }
    }
    return Text;
}
vector<string> separateWords_spaces(string cipherText){
    vector<string>Text;
    string word="";
    for (int i=0;i<cipherText.size();i++){
        if (cipherText[i]==' '){
            if (word!=""){
                Text.push_back(word);
                Text.push_back(" ");
                word="";
            }
            else{
                Text.push_back(" ");
            }
        }
        else if (!isalpha(cipherText[i])){
            Text.push_back(word);
            word="";
        }
        else if (i==cipherText.size()-1){
            word += toupper(cipherText[i]);
            Text.push_back(word);
            word="";
        }
        else{
            word+=toupper(cipherText[i]);
        }
    }
    return Text;
}
int binarySearch(vector<string>dictionary,string word){
    int low=0;
    int mid;
    int high=dictionary.size()-1;
    while (high >= low) {
        mid = (low + high) / 2;
        if (word > dictionary.at(mid)) {
            low = mid + 1;
        }
        else if (word < dictionary.at(mid)) {
            high = mid - 1;
        }
        else {
            return mid;
        }
    }
    return -1;

}
vector<string> Decrypt_Caesar(vector<string> TextVector, vector<string>dictionary,string cipherText){
    vector<string>Decrypted;
    int count=0;
    if (TextVector.size()==1){
        for (int i=0;i<26;i++){
            if (binarySearch(dictionary,rot(TextVector.at(0),i))!=-1){
                Decrypted.push_back(rot(TextVector.at(0),i));
            }
        }
    }
    else{
        for (int x=0;x<26;x++){
            for (int y=0;y<TextVector.size();y++){
                if(binarySearch(dictionary,rot(TextVector.at(y),x))!=-1){
                    count++;
                    if (count==(TextVector.size()/2)+1){
                        for (int z=0;z<TextVector.size();z++){
                            if (TextVector.at(z)==" "){
                                Decrypted.push_back(" ");
                            }
                            else{
                                Decrypted.push_back(rot(TextVector.at(z),x));
                            }
                            
                        }
                        return Decrypted;
                    }
                    else{
                        continue;
                    }
                }
                else{
                    continue;
                }
                
            }
            Decrypted.clear();
            count=0;
        }
    }
    return Decrypted;
}