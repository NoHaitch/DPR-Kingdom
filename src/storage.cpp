#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "header/animal.hpp"
#include "header/plant.hpp"
#include "header/storage.hpp"
#include "header/printColor.hpp"

using namespace std;

template<class T>
Storage<T>::Storage() : Storage(0,0) {}

template<class T>
Storage<T>::Storage(int _numRow, int _numCol) : numRow(_numRow), numCol(_numCol), numElmt(0){
    matrix.resize(numRow, vector<T*>(numCol, nullptr));
}

template<class T>
Storage<T>::~Storage(){}

template<class T>
int Storage<T>::getNumRow(){
    return this->numRow;
}

template<class T>
int Storage<T>::getNumCol(){
    return this->numCol;
}

template<class T>
int Storage<T>::getNumElmt(){
    return this->numElmt;
}

template<class T>
T Storage<T>::getElmt(string positionCode){
    try{
        pair<int, int> position = translatePositionCode(positionCode);
        return *matrix[position.first][position.second];
    } catch (PositionCodeInvalidException e){
        startTextRed();
        cout << e.what() << endl;
        resetTextColor();
    }
}

template<class T>
bool Storage<T>::isStorageFull(){
    return numElmt == numRow * numCol;
}

template<class T>
pair<int, int> Storage<T>::translatePositionCode(string positionCode){
    int row = (stoi(positionCode.substr(1)) - 1);
    int col = (positionCode[0] - 'A');
    if (row >= 0 && row < numRow && col >= 0 && col <numCol){
        return make_pair(row, col);
    } else {
        throw PositionCodeInvalidException("Position Code is out of bounds for this storage");
    }
}

template<class T>
void Storage<T>::insertElmtAtPosition(string positionCode, string codeElmt){
    try {
        if (isStorageFull()){
            throw StorageFullException("No slot available since storage is full");
        } else {
            pair<int, int> position = translatePositionCode(positionCode);
            delete matrix[position.first][position.second];
            matrix[position.first][position.second] = new T(codeElmt);
            numElmt++;
        }
    } catch (PositionCodeInvalidException e){
        startTextRed();
        cout << e.what() << endl;
        resetTextColor();
    }
}

template<class T>
void Storage<T>::insertElmtAtEmptySlot(string codeElmt){
    if (isStorageFull()){
        throw StorageFullException("No slot available since storage is full");
    } else {
        for (int i=0; i<numRow; i++){
            for (int j=0; j<numCol; j++){
                //cout << i << " " << j << " " << matrix[i][j] << endl;
                if (matrix[i][j] == nullptr){
                    matrix[i][j] = new T(codeElmt);
                    numElmt++;
                    return;
                }
            }
        }
    }
}

template<class T>
void Storage<T>::deleteElmtAtPosition(string positionCode){
    try {
        pair<int, int> position = translatePositionCode(positionCode);
        delete matrix[position.first][position.second];
        matrix[position.first][position.second] = nullptr;
        numElmt--;
    } catch (PositionCodeInvalidException e){
        startTextRed();
        cout << e.what() << endl;
        resetTextColor();
    }
}

template<class T>
void Storage<T>::printStorage(){
    resetTextColor();
    cout << "      ";
    for (int i=65; i<65+numCol; i++){
        char c = static_cast<char>(i);
        cout << "  " << c << "   ";
    }
    cout << endl;
    cout << "     ";
    for (int i=0; i<numCol; i++){
        cout << "+-----";
    }
    cout << "+" << endl;
    for (int i=0; i<numRow; i++){
        cout << "  " << setw(2) << setfill('0') << i+1 << " |";
        for (int j=0; j<numCol; j++){
            if (matrix[i][j]==nullptr){
                cout << "     |";
            } else {
                cout << " " << *matrix[i][j] << " |";
            }
        }
        cout << endl;
        cout << "     ";
        for (int j=0; j<numCol; j++){
            cout << "+-----";
        }
        cout << "+" << endl;
    }
}

template<>
void Storage<Animal>::printStorage(){
    resetTextColor();
    cout << "      ";
    for (int i=65; i<65+numCol; i++){
        char c = static_cast<char>(i);
        cout << "  " << c << "   ";
    }
    cout << endl;
    cout << "     ";
    for (int i=0; i<numCol; i++){
        cout << "+-----";
    }
    cout << "+" << endl;
    for (int i=0; i<numRow; i++){
        cout << "  " << setw(2) << setfill('0') << i+1 << " |";
        for (int j=0; j<numCol; j++){
            if (matrix[i][j]==nullptr){
                cout << "     |";
            } else {
                if (matrix[i][j]->getCurrWeight() >= matrix[i][j]->getWeightToHarvest()){
                    startTextGreen();
                } else {
                    startTextRed();
                }
                cout << " " << matrix[i][j]->getCode();
                resetTextColor();
                cout << " |";
            }
        }
        cout << endl;
        cout << "     ";
        for (int j=0; j<numCol; j++){
            cout << "+-----";
        }
        cout << "+" << endl;
    }
}

template<>
void Storage<Plant>::printStorage(){
    resetTextColor();
    cout << "      ";
    for (int i=65; i<65+numCol; i++){
        char c = static_cast<char>(i);
        cout << "  " << c << "   ";
    }
    cout << endl;
    cout << "     ";
    for (int i=0; i<numCol; i++){
        cout << "+-----";
    }
    cout << "+" << endl;
    for (int i=0; i<numRow; i++){
        cout << "  " << setw(2) << setfill('0') << i+1 << " |";
        for (int j=0; j<numCol; j++){
            if (matrix[i][j]==nullptr){
                cout << "     |";
            } else {
                if (matrix[i][j]->getCurrentDuration() >= matrix[i][j]->getHarvestDuration()){
                    startTextGreen();
                } else {
                    startTextRed();
                }
                cout << " " << matrix[i][j]->getCode();
                resetTextColor();
                cout << " |";
            }
        }
        cout << endl;
        cout << "     ";
        for (int j=0; j<numCol; j++){
            cout << "+-----";
        }
        cout << "+" << endl;
    }
}