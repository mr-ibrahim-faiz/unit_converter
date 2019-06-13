#ifndef BASE_UNIT_H
#define BASE_UNIT_H

#include<string>
using std::string;

#include<iostream>
using std::ostream;

// user-defined type Base_Unit
class Base_Unit {
public:
	// measures
	enum class Measure {
		length, mass, time, temperature, area
	};

	// default constructor
	Base_Unit() noexcept = delete;

	// constructor taking name, symbol, id and factor as arguments
	explicit Base_Unit(string, string, size_t, double, double, double, Base_Unit::Measure, bool = false);

	// destructor
	~Base_Unit();

	// retrieves the name
	string Name() const noexcept;

	// retrieves the abbreviation
	string Symbol() const noexcept;

	// retrieves the id
	size_t ID() const noexcept;

	// retrieves the conversion unit id
	size_t ID_conversion() const noexcept;

	// retrieves the conversion unit factor
	double Factor() const noexcept;

	// retrieves the conversion unit summand
	double Summand() const noexcept;

	// retrieves the conversion unit addend
	double Addend() const noexcept;

	// retrieves the measure
	Base_Unit::Measure Quantity() const noexcept;

	// checks if the base unit can be preceded by a prefix
	bool Can_be_preceded() const noexcept;

	// overloading copy operator<<
	friend ostream& operator<<(ostream&, const Base_Unit&);

private:
	string name;
	string symbol;
	size_t unit_id;
	size_t conversion_unit_id;
	double conversion_unit_factor;
	double conversion_unit_summand;
	double conversion_unit_addend;
	Base_Unit::Measure measure;
	bool can_be_preceded;

	// gets unit ID
	size_t get_unit_id();

	// checks if the unit is valid
	bool is_valid();
};

#endif
