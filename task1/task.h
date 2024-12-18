#pragma once
#include <iostream>
#include <vector>

class binary_int {
   private:
	int n;

   public:
	binary_int(int n_) : n(n_) {}

	binary_int operator-() const;
	binary_int& operator++();
	binary_int& operator--();
	binary_int operator++(int);
	binary_int operator--(int);
	binary_int operator+(const binary_int&) const;
	binary_int operator-(const binary_int&) const;
	binary_int& operator+=(const binary_int&);
	binary_int& operator-=(const binary_int&);
	binary_int operator>>(const binary_int&) const;
	binary_int operator<<(const binary_int&) const;
	binary_int& operator>>=(const binary_int&);
	binary_int& operator<<=(const binary_int&);
	binary_int operator*(const binary_int&) const;
	binary_int& operator*=(const binary_int&);

	friend std::ostream& operator<<(std::ostream&, const binary_int&);

	std::pair<binary_int, binary_int> split() const;
};