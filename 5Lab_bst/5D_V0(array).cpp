#include <iostream>
#include <iomanip>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <fstream>
#include <cstring>

using namespace std;

struct Node {
  uint16_t val;
  Node* next;
  Node* prev;
};


void put (uint16_t x, Node* &lastPointer){
    Node* pointerA = new Node;
    lastPointer->next = pointerA;
    pointerA->val = x;
    pointerA->prev = lastPointer;
    pointerA->next = NULL;
    lastPointer = pointerA;

}

uint16_t get (Node* &nodeToGetPointer){
    uint16_t result = nodeToGetPointer->next->val;
    nodeToGetPointer = nodeToGetPointer->next;
    return result;
}

int findNumOfCommand (string inputLabel, int totalCommandsNumber, string commandsArr[]){
    int inputLabelLenght = inputLabel.length();
    for (int i = 0; i < totalCommandsNumber; i++){
        string strToCheck = commandsArr[i];
        bool itIsThisLabel = true;
        if (strToCheck[0] != ':') {continue; }

        for (int j = 1; j < inputLabelLenght; j ++){

            if ((strToCheck[j] != inputLabel[j] )){
                itIsThisLabel = false;
                break;
            }
        }

        if (itIsThisLabel == true) {
            return i;
            break;
        }
    }
    return totalCommandsNumber - 1;
}

int main ()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    //ifstream fin("quackIN.txt");
    //ofstream fout("quackOUT.txt");
    ifstream fin("quack.in");
    ofstream fout("quack.out");

    int totalCommandsNumber = 0;
    int curCommandNumber = 0;
    string curStr;


    //It is for queue
    Node* lastPointer = new Node;
    lastPointer->next = NULL;
    Node* nodeToGetPointer = lastPointer;

    string* commandsArr = new string[100000];
    uint16_t registers[26];

    for (int i = 0; i < 26; i++) registers[i] = 0;

    while (fin>>curStr){
        commandsArr[curCommandNumber] = curStr;
        curCommandNumber++;
        totalCommandsNumber++;
    }

    curCommandNumber = 0;

    while (curCommandNumber < totalCommandsNumber) {
         string curCommand = commandsArr[curCommandNumber];


        if (curCommand[0] == '+'){
            uint16_t x = get(nodeToGetPointer);
            uint16_t y = get(nodeToGetPointer);
            uint16_t result = (x+y);
            put(result, lastPointer);

        } else if (curCommand[0] == '-'){
            uint16_t x = get(nodeToGetPointer);
            uint16_t y = get(nodeToGetPointer);
            uint16_t result = (x-y);
            put(result, lastPointer);

        } else if (curCommand[0] == '*'){
            uint16_t x = get(nodeToGetPointer);
            uint16_t y = get(nodeToGetPointer);
            uint16_t result = (x*y);
            put(result, lastPointer);

        } else if (curCommand[0] == '/'){
            uint16_t x = get(nodeToGetPointer);
            uint16_t y = get(nodeToGetPointer);
            if (y == 0) { put(0, lastPointer); }
            else {
                uint16_t result = (x/y);
                put(result, lastPointer);
            }


        } else if (curCommand[0] == '%'){
            uint16_t x = get(nodeToGetPointer);
            uint16_t y = get(nodeToGetPointer);
            if (y == 0) { put(0, lastPointer); }
            else {
                uint16_t result = (x%y);
                put(result, lastPointer);
            }

        } else if (curCommand[0] == '>'){
            char registerChar = curCommand[1];
            uint16_t x = get(nodeToGetPointer);
            registers[registerChar - 'a'] = x;

        } else if (curCommand[0] == '<'){
            char registerChar = curCommand[1];
            uint16_t x = registers[registerChar - 'a'];
            put(x, lastPointer);

        } else if (curCommand[0] == 'P'){

            if (islower(curCommand[1])){
                char registerChar = curCommand[1];
                uint16_t x = registers[registerChar - 'a'];
                fout<<x<<endl;
            } else {

                uint16_t x = get(nodeToGetPointer);
                fout<<x<<endl;
            }

        } else if (curCommand[0] == 'C'){

            if (islower(curCommand[1])){
                char registerChar = curCommand[1];
                uint16_t x = registers[registerChar - 'a'];
                x = x%256;
                char ch = (char) x;
                fout<<ch;

            } else {
                uint16_t x = get(nodeToGetPointer);
                x = x%256;
                char ch = (char) x;
                fout<<ch;

            }

        } else if (curCommand[0] == ':'){ //no action

        } else if (curCommand[0] == 'J'){

            curCommandNumber = findNumOfCommand(curCommand, totalCommandsNumber, commandsArr) - 1;


        } else if (curCommand[0] == 'Z'){
            char registerChar = curCommand[1];
            uint16_t x = registers[registerChar - 'a'];

            if (x == 0) {
                string inputLabel_A = curCommand;
                inputLabel_A[0] = 'A';
                for (int i = 2; i < curCommand.length(); i ++) {inputLabel_A[i-1] = curCommand[i];}
                inputLabel_A[curCommand.length()-1]='\0';

                curCommandNumber = findNumOfCommand(inputLabel_A, totalCommandsNumber, commandsArr)-1;
            }


        } else if (curCommand[0] == 'E'){
            char registerChar1 = curCommand[1];
            char registerChar2 = curCommand[2];
            uint16_t x = registers[registerChar1 - 'a'];
            uint16_t y = registers[registerChar2 - 'a'];

            if (x == y){

                string inputLabel_A (curCommand.length() - 2, 'A');
                inputLabel_A[0] = 'A';
                for (int i = 3; i < curCommand.length(); i ++) {inputLabel_A[i-2] = curCommand[i];}
                inputLabel_A[curCommand.length()-2]='\0';
                curCommandNumber = findNumOfCommand(inputLabel_A, totalCommandsNumber, commandsArr)-1;
            }

        } else if (curCommand[0] == 'G'){

            char registerChar1 = curCommand[1];
            char registerChar2 = curCommand[2];
            uint16_t x = registers[registerChar1 - 'a'];
            uint16_t y = registers[registerChar2 - 'a'];

            if (x > y){
                string inputLabel_A (curCommand.length() - 2, 'A');
                inputLabel_A[0] = 'A';
                for (int i = 3; i < curCommand.length(); i ++) {inputLabel_A[i-2] = curCommand[i];}
                inputLabel_A[curCommand.length()-2]='\0';
                curCommandNumber = findNumOfCommand(inputLabel_A, totalCommandsNumber, commandsArr)-1;
            }

        } else if (curCommand[0] == 'Q'){
            break;

        } else { //it is a number
            int number = 0;
            for (char chr: curCommand){
                if (chr>= '0' && chr<= '9') {
                    number = number * 10 + (chr - '0');
                }

            }
            uint16_t x = number % 65536;
            put (x, lastPointer);

        }

        curCommandNumber++;

    }

   return 0;
}
