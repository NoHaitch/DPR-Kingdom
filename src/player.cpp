#include <iostream>
#include <iomanip>
#include <string>

#include "header/player.hpp"
#include "header/storage.hpp"
#include "header/product.hpp"
#include "header/playerException.hpp"

using namespace std;

int Player::numPlayer = 0;

Player::Player(string _userName) : Player(_userName, DefaultPlayerStartingWealth, DefaultPlayerStartingWeight){}

Player::Player(string _username, int _wealth, int _currWeight) :
    id(numPlayer),
    username(_username),
    wealth(_wealth),
    currWeight(_currWeight),
    ItemStorage()
    {
        Player::numPlayer++;
    }

Player::~Player(){}

int Player::getId() const{
    return this->id;
}

string Player::getUsername() const{
    return this->username;
}

int Player::getWealth() const{
    return this->wealth;
}

int Player::getCurrWeight() const{
    return this->currWeight;
}

void Player::setWealth(int _wealth){
    this->wealth = _wealth;
}

void Player::setCurrWeight(int _currWeight){
    this->currWeight = _currWeight;
}

void Player::printItemStorage(){
    this->ItemStorage.printStorage();
}

void Player::eatFromStorage(){
    cout << "Select a food from storage" << endl;
    cout << endl;
    printItemStorage();
    bool valid = false;
    string inputCode, selectedItem;
    while (!valid){
        try {
            cout << "Slot: ";
            cin >> inputCode;
            if (ItemStorage.isEmpty(inputCode)){
                throw StorageSlotException("Selected slot is Empty! Input a filed slot instead");
            } else {
                selectedItem = ItemStorage.getElmt(inputCode);
                if (itemType(inputCode)=="Product"){
                    Product selectedProduct(selectedItem);
                    if (isEdible(selectedProduct)){
                        ItemStorage.deleteElmtAtPosition(inputCode);
                        currWeight += selectedProduct.getAddedWeight();
                        valid = true;
                    } else {
                        throw InedibleProductException("Selected product is Indedible! Input a slot with food instead");
                    }
                } else {
                    throw NotProductException("Selected Item is not a product! Input a slot with food product");
                }
            }
        } catch (exception e){
            cout << e.what() << endl;
        }
    }
}

void Player::buy(){}

void Player::sell(){}

string Player::itemType(string positionCode) {
    string itemCode = this->ItemStorage.getElmt(positionCode);
    vector <string>::iterator it;

    // Find in Plant
    it = find(Plant::getPlantCodeListConfig().begin(), Plant::Plant::getPlantCodeListConfig().end(), itemCode);
    if (it != Plant::Plant::getPlantCodeListConfig().end()) {
        return "Plant";
    } else {
        // Find in Animal
        it = find(Animal::getAnimalCodeConfig().begin(), Animal::Animal::getAnimalCodeConfig().end(), itemCode);
        if (it != Animal::Animal::getAnimalCodeConfig().end()) {
            return "Animal";
        } else {
            it = find(Product::getProductCodeListConfig().begin(), Product::Product::getProductCodeListConfig().end(), itemCode);
            if (it != Product::Product::getProductCodeListConfig().end()) {
                return "Product";
            } else {
                // TODO : implement search building
                return "";
            }
        }
    }
}

string Player::itemType(int y, int x) {
    string itemCode = this->ItemStorage.getElmt(y, x);
    vector <string>::iterator it;

    // Find in Plant
    it = find(Plant::getPlantCodeListConfig().begin(), Plant::Plant::getPlantCodeListConfig().end(), itemCode);
    if (it != Plant::Plant::getPlantCodeListConfig().end()) {
        return "Plant";
    } else {
        // Find in Animal
        it = find(Animal::getAnimalCodeConfig().begin(), Animal::Animal::getAnimalCodeConfig().end(), itemCode);
        if (it != Animal::Animal::getAnimalCodeConfig().end()) {
            return "Animal";
        } else {
            it = find(Product::getProductCodeListConfig().begin(), Product::Product::getProductCodeListConfig().end(), itemCode);
            if (it != Product::Product::getProductCodeListConfig().end()) {
                return "Product";
            } else {
                // TODO : implement search building
                return "";
            }
        }
    }
}

int Player::calculateTax(){}

void Player::payTax(){}