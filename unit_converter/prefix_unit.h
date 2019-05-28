#ifndef PREFIX_UNIT_H
#define PREFIX_UNIT_H

#include<iostream>
using std::ostream;

#include<string>
using std::string;

// user-defined type Prefix_Unit
class Prefix_Unit {
public:
	// default constructor
	Prefix_Unit() noexcept = delete;

	// constructor taking name, symbol and factor as arguments
	explicit Prefix_Unit(string, string, double) noexcept;

	// destructor
	~Prefix_Unit();

	// retrieves the name
	string Name() const noexcept;

	// retrieves the symbol
	string Symbol() const noexcept;

	// retrieves the factor
	double Factor() const noexcept;

	// overloading copy operator<<
	friend ostream& operator<<(ostream&, const Prefix_Unit&);

	// overloading copy operator==
	friend bool operator==(const Prefix_Unit&, const Prefix_Unit&);

	// overloading copy operator!=
	friend bool operator!=(const Prefix_Unit&, const Prefix_Unit&);

private:
	string name;
	string symbol;
	double factor;
};

#endif
