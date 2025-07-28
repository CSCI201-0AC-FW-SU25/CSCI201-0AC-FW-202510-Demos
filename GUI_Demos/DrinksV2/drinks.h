#pragma once
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <set>

enum baseType
{
	COFFEE,
	TEA,
	CREAM
};
enum tempType
{
	HOT,
	ICE,
	BLEND
};
enum sizeType
{
	SMALL,
	MED,
	LARGE
};

enum flavType
{
	HAZELNUT,
	APPLE,
	BUTTERPECAN,
	BLUEBERRY,
	CARAMEL,
	PEACH,
	MOCHA,
	RASPBERRY,
	FRENCHVANILLA,
	STRAWBERRY,
	PEPPERMINT,
	MANGO


};
const int NUM_DAIRY = 6;
const int NUM_FLAV = 12;
const std::string baseStr[] = {"Coffee", "Tea", "Cream"};
const std::string tempStr[] = {"Hot", "Iced", "Blended"};
const std::string sizeStr[] = {"Small", "Medium", "Large"};
const baseType bases[] = {COFFEE, TEA, CREAM};
const tempType temps[] = {HOT, ICE, BLEND};
const sizeType sizes[] = {SMALL, MED, LARGE};
const std::string flavStr[] = {"Hazelnut",
							   "Apple",
							   "Butter Pecan",
							   "Blueberry",
							   "Caramel",
							   "Peach",
							   "Mocha",
							   "Raspberry",
							   "French Vanilla",
							   "Strawberry",
							   "Peppermint",
							   "Mango"
							   };
const flavType flavs[] = {
	HAZELNUT,
	APPLE,
	BUTTERPECAN,
	BLUEBERRY,
	CARAMEL,
	PEACH,
	MOCHA,
	RASPBERRY,
	FRENCHVANILLA,
	STRAWBERRY,
	PEPPERMINT,
	MANGO

};

const std::string dairyStr[] = {"None",
"Skim Milk",
"Whole Milk",
"Oat Milk",
"Cream",
"Almond Milk"};

class drink
{
public:
	drink(baseType = CREAM, tempType = HOT, sizeType = SMALL, std::string dairy = "None");
	
	std::string getBaseStr() const;
	std::string getTemperature() const;
	std::string getSize() const;
	std::string getDairy() const;
	std::string getFlavor() const;
	double getPrice() const;
	void setBase(baseType);
	void setTemperature(tempType);
	void setSize(sizeType);
	void setDairy(std::string);
	void addFlavor(flavType);
	void removeFlavor(flavType);
	void removeAllFlavor();
	friend std::ostream &operator<<(std::ostream &, const drink &);

private:
	baseType base;
	tempType temperature;
	sizeType size;
	std::string dairy;
	std::set<flavType> flavors;
	std::string tostring() const;
};
