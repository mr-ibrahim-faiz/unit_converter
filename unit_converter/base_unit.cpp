#include "base_unit.h"

#include<stdexcept>
using std::runtime_error;

#include<limits>
using std::numeric_limits;

// constant expressions
constexpr double FACTOR_IDENTITY { 1.0 };
constexpr size_t ID_INVALID = numeric_limits<size_t>::max();

// constructor taking name, symbol, id and factor as arguments
Base_Unit::Base_Unit(string name, string symbol, size_t conversion_unit_id, double conversion_unit_factor, double conversion_unit_summand, double conversion_unit_addend, Base_Unit::Measure measure, bool can_be_preceded) 
	: name { name }, symbol { symbol }, conversion_unit_id { conversion_unit_id }, conversion_unit_factor { conversion_unit_factor }
	, conversion_unit_summand { conversion_unit_summand }, conversion_unit_addend { conversion_unit_addend }, measure { measure }, can_be_preceded { can_be_preceded }
{
	unit_id = get_unit_id();
	if(!is_valid()){
		const string error_message = "unable to create the unit (" + name + ").";
		throw runtime_error(error_message);
	}
}

// destructor
Base_Unit::~Base_Unit(){}

// retrieves the name
string Base_Unit::Name() const noexcept {
	return name;
}
	
// retrieves the abbreviation
string Base_Unit::Symbol() const noexcept {
	return symbol;
}

// gets unit ID
size_t Base_Unit::get_unit_id(){
	static size_t next_id = ID_INVALID;
	++next_id;
	return next_id;
}

// retrieves the id
size_t Base_Unit::ID() const noexcept {
	return unit_id;
}	

// retrieves the conversion unit id
size_t Base_Unit::ID_conversion() const noexcept {
	return conversion_unit_id;
}

// retrieves the conversion unit factor
double Base_Unit::Factor() const noexcept {
	return conversion_unit_factor;
}
	
// retrieves the conversion unit summand
double Base_Unit::Summand() const noexcept {
	return conversion_unit_summand;
}

// retrieves the conversion unit addend
double Base_Unit::Addend() const noexcept {
	return conversion_unit_addend;
}

// retrieves the measure
Base_Unit::Measure Base_Unit::Quantity() const noexcept {
	return measure;
}

// checks if the base unit can be preceded by a prefix
bool Base_Unit::Can_be_preceded() const noexcept {
	return can_be_preceded;
}

// overloading copy operator<<
ostream& operator<<(ostream& os, const Base_Unit& unit){
	os << unit.Name();
	return os;
}

// checks if the unit is valid
bool Base_Unit::is_valid()
// the conversion unit id is less or equal to the unit id*
// the conversion unit factor is greater to 0.0
// when the conversion unit id equals the unit id, the conversion unit factor equals 1 (the identity factor)
{
	bool A = conversion_unit_id == unit_id;
	bool B = conversion_unit_factor == FACTOR_IDENTITY && conversion_unit_summand == 0 && conversion_unit_addend == 0;
	bool C = bool(A^B);
	bool D = conversion_unit_factor <= 0.0;
	
	if(C || D) return false;

	return true;	
}
