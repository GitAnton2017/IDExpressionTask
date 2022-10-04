//
//  pair.cpp
//  A-Z1-9
//
//  Created by Anton2016 on 04.10.2022.
//

#include "pair.hpp"

const std::unordered_set<char>
Pair::exception_set {'D', 'F', 'G', 'J', 'M', 'Q', 'V'}; //«D», «F», «G», «J», «M», «Q», «V» и цифра «0».

bool Pair::isFull() const { return index == '9' && letter == 'Z'; }
void Pair::reset() { letter = 'A'; index = '1'; }

void Pair::operator++(int){
 if (isFull()) { return; }
 if (index == '9') {
  index = '1';
  while (exception_set.find(++letter) != exception_set.end());
 } else {
  index++;
 }
}
