#include <iostream>
#include <string>
#include "avlmap.h"

using namespace std;

template <typename Iter>
void printDebugInfo(const std::pair<Iter, bool> &insert_info) { auto c1 = *insert_info.first; std::cout << (insert_info.second ? "Dodano " + c1.second : "Nie dodano ;/") << std::endl; }

template <typename Iter>
void printDebugInfo(const Iter &find_info) { auto c1 = *find_info; std::cout << ("Nie znaleziono ;/") << std::endl; }

template <typename K, typename V>
void printSetSizeAndElems(avl_tree<K, V> &m)
{
std::cout << "Size: " << m.size() << std::endl;
for(auto &e : m) std::cout << e.second << ", ";
std::cout << std::endl;
}

template <typename K, typename V>
void printSetSizeAndElems(const avl_tree<K, V> &m)
{
std::cout << "Size: " << m.size() << std::endl;
for(const auto &e : m) std::cout << e.second << ", ";
std::cout << std::endl;
}
int main()
{
avl_tree<int, std::string> m;
printDebugInfo(m.insert( { 8, "eight" } ));
printDebugInfo(m.insert( { 4, "four" } ));
printDebugInfo(m.insert( { 10, "ten" } ));
printDebugInfo(m.insert( { 10, "ten" } ));
printDebugInfo(m.insert( { 2, "two" } ));
printDebugInfo(m.insert( { 5, "five" } ));
printDebugInfo(m.insert( { 9, "nine" } ));
printDebugInfo(m.insert( { 12, "twelve" } ));
printDebugInfo(m.insert( { 12, "twelve" } ));
printDebugInfo(m.insert( { 1, "one" } ));
printDebugInfo(m.insert( { 14, "fourteen" } ));
printDebugInfo(m.insert( { 7, "seven" } ));
{
auto m2 = m;
printSetSizeAndElems(m2);
}
auto it = m.find(10);

//*it = "10 (poprawione)";
printDebugInfo(m.find(5));
m.erase(4);
printDebugInfo(m.find(5));
m.erase(12);
m.erase(14);
printDebugInfo(m.insert( { 0, "zero" } ));
printDebugInfo(m.insert( { 16, "sixteen" } ));

{
avl_tree<int, std::string> m3;
//m3 = m;
//printSetSizeAndElems(m3);
}
m.erase(8);
printSetSizeAndElems(m);
const auto m4 = m;
//printSetSizeAndElems(m4);
auto it2 = m4.find(10);

// *it2 = "nie powinno sie skompilowac";
// m4[2] = "nie powinno sie skompilowac";
m[2] = "two (poprawione)";
m[20] = "twenty";
//printSetSizeAndElems(m);

return 0;
}
