#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include "City.h"

std::vector<City *> citiesDatabase;      
std::vector<std::string> strings;
void printData();
void addCity();
void findCity();
void editCity();
void deleteCity();
int menu();
void printDistance();

int main()
{
    std::ifstream data("cities.txt");
    std::string item;
    while (std::getline(data, item, ',')) {
        strings.push_back(item);
    }

    for (int i = 0; i < strings.size(); i+=4) {
        citiesDatabase.push_back(new City(strings[i], strings[i+1], std::stod(strings[i+2]), std::stod(strings[i+3])));
    }
//_____________________________________DATABASE CREATED______________________________________

//_____________________________________MENU__________________________________________________    
    int choice = 1;
    
    while (choice != 0) {
        choice = menu();
        switch (choice) {
             case 1:
                 printData();
                 break;
             case 2:
                 findCity();
                 break;
             case 3:
                 printDistance();
                 break;
             case 4:
                 addCity();
                 break;
             case 5:
                 editCity();
                 break;
             case 6:
                 deleteCity();
                 break;
             case 0:
                 std::cout << "Goodbye!" << std::endl;
                 break;
        }
    }
    
//_______________________________CLEAN THE MEMORY______________________________________________
    for (int i = 0; i < citiesDatabase.size(); i++) {
        delete citiesDatabase[i];
        citiesDatabase.erase(citiesDatabase.begin() + i);
    }
    return 0;
}

int menu() {
    int option;
    std::cout << "-------------MENU-------------"<< std::endl;
    std::cout << "1. Display all cities" << std::endl;
    std::cout << "2. Find city by its name and country" << std::endl;
    std::cout << "3. Find a distance between two cities" << std::endl;
    std::cout << "4. Add the city" << std::endl;
    std::cout << "5. Modify the city" << std::endl;
    std::cout << "6. Delete the city" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cin >> option;
    return option;
}

//_________________________CHOICE 1_____________________________

void printData() {
    for (City *pCity : citiesDatabase) {
        std::cout << "City: " << pCity->getCity() << " in " << pCity->getCountry() << ", coordinates: " << pCity->getLatitude() << ", " << pCity->getLongitude() << std::endl;
    }
}

//_________________________CHOICE 2_____________________________

void findCity() {
    std::string citySearch, countrySearch = "";
    std::cout << "City: " << std::endl;
    std::cin >> citySearch;

    std::cout << "Country: " << std::endl;
    std::cin >> countrySearch;
    
    bool found = false; //boolean variable to check if city exists
    int index = 0; //remember the index of it

    for (int x = 0; x < citiesDatabase.size(); x++) {  
        if (citySearch == citiesDatabase[x]->getCity() && countrySearch == citiesDatabase[x]->getCountry()) {
            found = true;
            index = x;
        }
    }
    if (found) {
        std::cout << "Found: " << std::endl;
        std::cout << citiesDatabase[index]->getCity() << " in " << citiesDatabase[index]->getCountry() << ", coordinates: " << citiesDatabase[index]->getLatitude() << ", " << citiesDatabase[index]->getLongitude() << std::endl;
    }
    else std::cout << "Not found" << std::endl;
}

//_________________________CHOICE 3_____________________________

void printDistance() {
    //MAKE SOME INPUT
    std::string city1, country1, city2, country2 = "";
    std::cout << "First city: " << std::endl;
    std::cin >> city1;

    std::cout << "In country: " << std::endl;
    std::cin >> country1;

    std::cout << "Second city: " << std::endl;
    std::cin >> city2;

    std::cout << "In country: " << std::endl;
    std::cin >> country2;

    int index1 = 0;
    int index2 = 0;
    bool found1 = false;
    bool found2 = false;

    //FIND BOTH CITIES IN VECTOR
    for (int x = 0; x < citiesDatabase.size(); x++) {  
        if (city1 == citiesDatabase[x]->getCity() && country1 == citiesDatabase[x]->getCountry()) {
            found1 = true;
            index1 = x;
        }
        else if (city2 == citiesDatabase[x]->getCity() && country2 == citiesDatabase[x]->getCountry()) {
            found2 = true;
            index2 = x;
        }
    }
    
    if (found1 && found2) {
        std::cout << "Distance between them is: " << citiesDatabase[index1]->distance(*citiesDatabase[index2]) << std::endl;
    }
    else 
        std::cout << "One or both cities not found" << std::endl;
}

//_________________________CHOICE 4_____________________________

void addCity() {
        std::ofstream data_file("cities.txt");
        float longitudeVal, latitudeVal;
        std::string cityStr, countryStr = "";
        std::cout << "No spaces! Use abbreviations(for instance, European Union == EU)" << std::endl;
        std::cout << "City: ";
        std::cin >> cityStr;
        std::cout << "Country: ";
        std::cin >> countryStr;
        std::cout << "Latitude: ";
        std::cin >> latitudeVal;
        std::cout << "Longitude: ";
        std::cin >> longitudeVal;
        
	//add a city to vector
        citiesDatabase.push_back(new City(cityStr, countryStr, latitudeVal, longitudeVal));
        
	//override the file
	for (City *pCity : citiesDatabase) {
        	std::string line = pCity->getCity() + "," + pCity->getCountry() + "," + std::to_string(pCity->getLatitude()) + "," + std::to_string(pCity->getLongitude()) + ",";
        	data_file << line;
    	}
        data_file.close();
}

//_________________________CHOICE 5_____________________________

void editCity() {
    std::ofstream data_file("cities.txt");
    std::string citySearch, countrySearch = "";
    std::cout << "City: ";
    std::cin >> citySearch;
    std::cout << "Country: ";
    std::cin >> countrySearch;
    bool found = false;
    int index = 0;

    for (int x = 0; x < citiesDatabase.size(); x++) {  
        if (citySearch == citiesDatabase[x]->getCity() && countrySearch == citiesDatabase[x]->getCountry()) {
            found = true;
            index = x;
        }
    }
    if (found) {
        //rewrite the city. If you want to remain smth not changed - write the same thing
        float latitudeVal, longitudeVal;
        std::cout << "Found: " << std::endl;
        std::cout << citiesDatabase[index]->getCity() << " in " << citiesDatabase[index]->getCountry() << ", coordinates: " << citiesDatabase[index]->getLatitude() << ", " << citiesDatabase[index]->getLongitude() << std::endl;
        std::cout << "_____________________" << std::endl;
	std::cout << "Edit mode activated. No spaces! Use abbreviations(for instance, European Union == EU)" << std::endl;
        std::cout << "City: ";
        std::cin >> citySearch;
        std::cout << "Country: ";
        std::cin >> countrySearch;
        std::cout << "Latitude: ";
        std::cin >> latitudeVal;
        std::cout << "Longitude: ";
        std::cin >> longitudeVal;  

        citiesDatabase[index]->setCity(citySearch);
        citiesDatabase[index]->setCountry(countrySearch);
        citiesDatabase[index]->setCoordinates(latitudeVal, longitudeVal);
    }
    else std::cout << "One or both cities not found" << std::endl;
    for (City *pCity : citiesDatabase) {
        std::string line = pCity->getCity() + "," + pCity->getCountry() + "," + std::to_string(pCity->getLatitude()) + "," + std::to_string(pCity->getLongitude()) + ",";
        data_file << line;
    }
    data_file.close();
}

//_________________________CHOICE 6_____________________________

void deleteCity() {
    std::ofstream data_file("cities.txt");
    std::cout << "DELETE! DELETE! DELETE!" << std::endl;
    std::string citySearch, countrySearch = "";
    std::cout << "City: ";
    std::cin >> citySearch;
    std::cout << "Country: ";
    std::cin >> countrySearch;
    bool found = false;
    int index = 0;

    for (int x = 0; x < citiesDatabase.size(); x++) {  
        if (citySearch == citiesDatabase[x]->getCity() && countrySearch == citiesDatabase[x]->getCountry()) {
            found = true;
            index = x;
        }
    }
    if (found) {
        delete citiesDatabase[index];
        citiesDatabase.erase(citiesDatabase.begin() + index);
        std::cout << "DELETED!!!" << std::endl;
    }
    else std::cout << "One or both cities not found" << std::endl;

    for (City *pCity : citiesDatabase) {
        std::string line = pCity->getCity() + "," + pCity->getCountry() + "," + std::to_string(pCity->getLatitude()) + "," + std::to_string(pCity->getLongitude()) + ",";
        data_file << line;
    }
    data_file.close();
}