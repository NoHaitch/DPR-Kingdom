#ifndef __CATTLEMAN_HPP__
#define __CATTLEMAN_HPP__

#include "player.hpp"

class Cattleman : public Player{
    private:
        Storage<Animal> farm;

    public:
        /**
        * @brief Default Cattleman Ctor
        */
        Cattleman(string _username);

        /**
        * @brief User Defined Cattleman Ctor
        */
        Cattleman(string _username, int _wealth, int _currWeight);

        /**
        * @brief Cattleman dtor
        */
        ~Cattleman();

        /**
        * @brief calculates tax to be paid
        * @return int Tax to be paid
        */
        int calculateTax() override;

        /**
        * @brief function of paying tax, cattlemans's wealth decrease
        * \note uses calculateTax() for the needed value
        */
        void payTax() override;

        /**
        * @brief calculates total wealth including profession storage
        * @return total wealth
        * 
        * \note calling parent's calculate wealth and adds the total from profession storage
        */
        int calculateWealth();

        /**
        * @brief buy specified items with exact amount from the shop item list, then store in itemStorage
        * 
        * \note Override Player's virtual method
        * \note Validize whether the amount of money enough and storage slot sufficient
        * \note called from buy command
        * \note Throw exception if needed 
        * 
        */
        void buy() override;

        /**
         * @brief sell specified items from storage into shops, players weight increase
         * 
         * \note Override Player's virtual method
         * \note Validize whether the item is available
         * \note called from sell command
         * \note Throw exception if needed
         * 
        */
        void sell() override;

        /**
         * @brief farm animals, moving an animal from storage to farm
         * \note Called from farm command
         * \note Validate it's an animal and empty slot in farm (Ask to reinput)
         * \note Function cannot be done if no animal exist or farm is full
         * \note Throw exception for all above cases
        */
        void farming();

        /**
         * @brief feeding animal using a food, animal weight increased based on configuration
         * \note Called from feed command
         * \note Validate if selected slot is not empty and food is suitable for animal (Ask to reinput)
         * \note Function cannot be done if farm empty or no food for animal exist in storage
         * \note Throw exception for all above cases
        */
        void feeding();

        /**
         * @brief count the number of animals of each species, including how many are harvestable
         * @return map with key animal code into number of animals and how many are harvestable
        */
        map<string, pair<int,int>> countAnimalsAndHarvestable();

        /**
         * @brief Harvest animal into a product stored in storage
         * \note Called from harvest command
         * \note Validate if needed (Ask to reinput)
         * \note Throw exception for invalid inputs
        */
        void harvestAnimal();
};

#endif