/*
Name: Marlon Alejandro, 5002573038, 1002, Assignment 2
Description: Use of recursion to optimial pathway through a 2D array 
that satisfies our given conditions
Input: Text file containing our given array, and user start and end indecies
Output: A modified version of the array that contains the pathway we program has determined 
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

char path[7][7];                                    // array we well read in and write to 
int MaxSteps;                                       // # of unoccupied items in our given array
bool findPath(int, int, int, int, int);             // recursive funtion that detemined our pathway
void readFile(fstream &, int&, int&, int&, int&);   // file read in and user iput funtion
void printPath();                                   // prints array
char intToAscii(int);                               // converts our ints to Ascii characters
void findMax();                                     // determines our MaxSteps

int main(){   
    int startX , startY, endX , endY;               // start and end coordiates
    int stepCount = 1;                              // initial step counter
    fstream inFile; 

    readFile(inFile, startX, startY, endX , endY);      
    findMax();
    findPath(startX, startY, endX, endY, stepCount); 
    printPath();
    
    return 0;  
}

void findMax(){
    MaxSteps = 0; 
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(path[i][j]==' '){
                MaxSteps++; 
            }
        }
    }
}

void printPath(){   
    for(int i = 0; i < 7; i++){
        for(int j= 0; j< 7; j++){
            cout<<path[i][j] << " "; 
        }
        cout<< endl; 
    } 
}

void readFile(fstream& inFile, int& startX ,int& startY,int& endX ,int& endY){
    string input;
    string fileName; 

    while(!inFile.is_open()){
        cout<<"Enter config file : "; 
        cin >> fileName; 
        inFile.open(fileName); 
        if(inFile.is_open()){
            break;
        }
        inFile.clear(); 
        cout<< "Error, retry\n";
    }
 
    int k=0;

    while(!inFile.eof()){
        getline(inFile, input);
        for(int i=0; i<7; i++){
            path[k][i]=input[i];
        }
        k++;
    }

    cout<<"\nPlease enter starting coordinates : ";
    cin >> startX >> startY; 

    cout<<"\nPlease enter end coordinates : ";
    cin >> endX >> endY;
    cout << endl; 
}

char intToAscii(int num){
    if(num >= 0 && num <10) 
        return '0' + num; 
    else 
        return '0' + num +7;
}


bool findPath(int startX, int startY, int endX, int endY, int stepCount){
    char temp = intToAscii(stepCount-1);                        //convert our step counter to Ascii

    if(path[startX][startY] != ' ')                             //validates if space is empty
        return false; 

    if(startX < 0|| startX >= 7 || startY < 0|| startY >= 7)    //Bound Check    
        return false; 

    path[startX][startY] = temp;                                // writes into space if valid

    if(startX == endX && startY == endY && MaxSteps == stepCount) { // valdates if all conditions are true 
        return true;                                                // We are at out end cordinates are all spaces are filled
    }

    //checks left, right, up, and down
    
    if(startX >= 0){
        if(findPath(startX-1, startY, endX, endY,stepCount+1)){
            return true; 
        } 
    }

    if(startX < 7){
        if(findPath(startX+1, startY, endX, endY, stepCount+1)){
            return true; 
        } 
    }

    if(startY >= 0){
        if(findPath(startX, startY-1, endX, endY,stepCount+1))
        {
            return true; 
        } 
    }

    if(startY < 7){
        if(findPath(startX, startY+1, endX, endY,stepCount+1)){
            return true; 
        } 
    }
    
    path[startX][startY] = ' ';                                 // clears index if returned as false

    return false; 
}