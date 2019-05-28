#ifndef UNIT_H
#define UNIT_H

#include "base_unit.h"
#include "prefix_unit.h"

// user-defined type Unit
class Unit {
public:
	// default constructor
	Unit() noexcept = delete;

	// constructor taking a prefix and a base unit as arguments
	explicit Unit(Prefix_Unit, Base_Unit);

	// destructor
	~Unit();

	// retrieves the prefix
	Prefix_Unit Prefix() const noexcept;

	// retrieves the base unit
	Base_Unit Base() const noexcept;

	// retrieves the name
	string Name() const noexcept;

	// retrieves the symbol
	string Symbol() const noexcept;

	// overloading copy operator==
	friend bool operator==(const Unit&, const Unit&);

	// overloading copy operator!=
	friend bool operator!=(const Unit&, const Unit&);

private:
	Prefix_Unit prefix;
	Base_Unit base;	
	string name;
	string symbol;
	
	// checks if the unit is valid
	bool is_valid();
};

#endif
