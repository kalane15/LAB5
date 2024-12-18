#pragma once

#include <compare>
#include <cstddef>
#include <stdexcept>

class iterator {
	const double* begin_;
	const double* end_;
	double* position_;

	void advance(long long n);

   public:
	explicit iterator(const double* begin, const double* end, double* position)
	    : begin_(begin), end_(end), position_(position) {
		if (position_ < begin_ || position_ > end_) {
			throw std::invalid_argument(
			    "position must be between 'begin' and 'end'");
		}
	}

	iterator(const iterator& iterator) = default;

	/* ---------------------------------------------------------------------- */

	iterator& operator++();
	iterator operator++(int);

	iterator& operator--();
	iterator operator--(int);

	iterator operator+(long long n) const;
	iterator& operator+=(long long n);

	iterator operator-(long long n) const;
	iterator& operator-=(long long n);

	bool operator==(const iterator& other) const = default;
	bool operator!=(const iterator& other) const = default;
	std::partial_ordering operator<=>(const iterator& other) const;

	double& operator->() const;
	double& operator*() const;
	double& operator[](long long n) const;
};