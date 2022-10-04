//
//  identifier.cpp
//  A-Z1-9
//
//  Created by Anton2016 on 03.10.2022.
//

#include "identifier.hpp"

IDExpression::IDExpression(){
 std::lock_guard<std::mutex> lock{m};
 this->pairs_list = std::list<Pair>{Pair{}};
}

IDExpression::IDExpression(IDExpression& e){
 this->pairs_list = e.pairs_list;
}

IDExpression & IDExpression::operator = (IDExpression const & e){
 std::lock_guard<std::mutex> lock{m};
 this->pairs_list = e.pairs_list;
 return *this;
}


IDExpression & IDExpression::operator = (std::string id_str){
 *this = IDExpression{id_str};
 return *this;
}

IDExpression::IDExpression(std::string id_str){
 if (!std::regex_match(id_str, parser)){
  throw std::invalid_argument{"Incorrect ID string"};
 }
 
 auto token_iter = std::sregex_token_iterator(id_str.begin(), id_str.end(), tokenizer, -1);
 
 std::list<Pair> pairs {};
 for (auto it = token_iter; it != std::sregex_token_iterator(); ++it ){
  auto token = it->str();
  pairs.push_back({token[0], token[1]});
 }
 
 {
  std::lock_guard<std::mutex> lock{m};
  pairs_list = pairs;
 }
 
 
}

std::string IDExpression::str() const {
 std::lock_guard<std::mutex> lock{m};
 std::string str{};
 auto it = pairs_list.begin();
 str.push_back(it->letter);
 str.push_back(it->index);
 it++;
 
 for (; it != pairs_list.end(); ++it ){
  str.push_back('-');
  str.push_back(it->letter);
  str.push_back(it->index);
 }
 return str;
 
}


IDExpression & IDExpression::operator++(){
 std::lock_guard<std::mutex> lock{m};
 auto iter = std::find_if(pairs_list.rbegin(), pairs_list.rend(), [](auto & pair){
  if (pair.isFull()) { pair.reset(); return false; }
  return true;
  
 });
 
 if ( iter == pairs_list.rend()){
  if ( pairs_list.size() == 10 ){
   pairs_list = std::list<Pair>{Pair{}};
   return *this;
  } else {
   pairs_list.push_front(Pair{});
  }
 } else {
  (*iter)++;
 }
 
 return *this;
}

IDExpression IDExpression::operator++(int){
 
 std::lock_guard<std::mutex> lock{m};
 auto copy { *this };
 auto iter = std::find_if(pairs_list.rbegin(), pairs_list.rend(), [](auto & pair){
  if (pair.isFull()) { pair.reset(); return false; }
  return true;
  
 });
 
 if ( iter == pairs_list.rend()){
  if ( pairs_list.size() == 10 ){
   pairs_list = std::list<Pair>{Pair{}};
   return *this;
  } else {
   pairs_list.push_front(Pair{});
  }
 } else {
  (*iter)++;
 }
 return copy;
}
