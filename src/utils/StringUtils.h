/*
 * StringUtils.h
 *
 *  Created on: Jun 24, 2012
 *      Author: joe
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

class BadConversion : public std::runtime_error
{
	public:
		BadConversion(std::string const& s) : std::runtime_error(s){ }
};

inline std::string stringify(double x)
{
	std::ostringstream o;

	if (!(o << x))
		throw BadConversion("stringify(double)");

	return o.str();
}

#endif /* STRINGUTILS_H_ */
