//
//  identifier.hpp
//  A-Z1-9
//
//  Created by Anton2016 on 03.10.2022.
//

#ifndef identifier_hpp
#define identifier_hpp

#include <string>
#include <initializer_list>
#include <list>
#include <regex>
#include <mutex>
#include "pair.hpp"

class IDExpression{

private:
 std::list<Pair> pairs_list;
 std::regex parser {"([ABCEHKLNOPRSTUWXYZ][1-9])(-[ABCEHKLNOPRSTUWXYZ][1-9]){0,9}"};
  //«D», «F», «G», «J», «M», «Q», «V» и цифра «0».
 
 std::regex tokenizer {"-"};
 mutable std::mutex m{};
 
public:

 IDExpression();                   //Initialize default ID expression with single default pair - "A1"
 IDExpression(std::string id_str); //Initialize default ID expression with ID std::string expression and parse it.
 
 IDExpression & operator = (std::string id_str); //Assign new std::string ID expression and parse it
 IDExpression & operator++();  
 IDExpression operator++(int);
 
 IDExpression (IDExpression &);
 IDExpression & operator = (const IDExpression &);
 
 std::string str() const;  //extract string representation of underlying ID expression.
 
};


#endif /* identifier_hpp */
