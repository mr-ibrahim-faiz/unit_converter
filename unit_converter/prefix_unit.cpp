#include "prefix_unit.h"

// constructor taking name, symbol and factor as arguments
Prefix_Unit::Prefix_Unit(string name, string symbol, double factor) noexcept
	: name { name }, symbol { symbol }, factor { factor }{}

// destructor
Prefix_Unit::~Prefix_Unit(){}

// retrieves the name
string Prefix_Unit::Name() const noexcept {
	return name;
}

// retrieves the symbol
string Prefix_Unit::Symbol() const noexcept {
	return symbol;
}

// retrieves the factor
double Prefix_Unit::Factor() const noexcept {
	return factor;
}

// overloading copy operator<<
ostream& operator<<(ostream& os, const Prefix_Unit& prefix){
	os << prefix.name;
	return os;
}

// overloading copy operator==
bool operator==(const Prefix_Unit& left, const Prefix_Unit& right){
	bool A = left.name != right.name;
	bool B = left.symbol != right.symbol;
	bool C = left.factor != right.factor;

	if(A || B || C) return false;
	return true;
}
	
// overloading copy operator!=
bool operator!=(const Prefix_Unit& left, const Prefix_Unit& right){
	return !operator==(left,right);
}
