#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include <iterator>
#include <vector>
#include <algorithm>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template<typename T>
std::set<T> setIntersection(const std::set<T>& s1, const std::set<T>& s2)
{
    std::set<T> intersect;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersect, intersect.begin()));
    return intersect;
}
template<typename T>
std::set<T> setUnion(const std::set<T>& s1, const std::set<T>& s2)
{
    std::set<T> unionSet;
    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(unionSet, unionSet.begin()));
    return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
