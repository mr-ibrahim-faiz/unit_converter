#include "unit.h"

#include<stdexcept>
using std::runtime_error;

const Prefix_Unit PREFIX_IDENTITY { "", "", 1 }; // identity prefix

// constructor taking a prefix and a base unit as arguments
Unit::Unit(Prefix_Unit prefix, Base_Unit base)
	: prefix { prefix }, base { base }
{
	name = prefix.Name() + base.Name();
	symbol = prefix.Symbol() + base.Symbol();

	if(!is_valid()){
		const string error_message = "unable to create the unit (" + name + "/" + symbol + ").";
		throw runtime_error(error_message);
	}
}	

// destructor
Unit::~Unit(){}

// checks if the unit is valid
bool Unit::is_valid()
// a unit with a base unit that cannot be preceded must have the identity prefix as prefix
{
	bool A = !base.Can_be_preceded();
	bool B = prefix != PREFIX_IDENTITY;

	if(A && B) return false;
	return true;
}

// retrieves the prefix
Prefix_Unit Unit::Prefix() const noexcept {
	return prefix;
}
	
// retrieves the base unit
Base_Unit Unit::Base() const noexcept {
	return base;
}
	
// retrieves the name
string Unit::Name() const noexcept {
	return name;
}
	
// retrieves the symbol
string Unit::Symbol() const noexcept {
	return symbol;
}
	
// overloading copy operator==
bool operator==(const Unit& lunit, const Unit& runit){
	bool A = lunit.name != runit.name;
	bool B = lunit.symbol != runit.symbol;
	bool C = lunit.prefix != runit.prefix;

	if(A || B || C) return false;
	return true;
}

// overloading copy operator!=
bool operator!=(const Unit& lunit, const Unit& runit){
	return !operator==(lunit,runit);
}

