//
//  main.cpp
//  A-Z1-9
//
//  Created by Anton2016 on 03.10.2022.
//

#include "identifier.hpp"
#include <iostream>
#include <list>

#include <thread>
#include <vector>

#define assertm(exp, msg) assert((msg, exp))

void test_concurrent_post_increment(auto id, auto count, auto result){
 std::vector<std::thread> tasks {};
 
 for (auto i = 0; i < count; ++i){
  std::thread t{[&](){ id++;}};
  tasks.push_back(std::move(t));
 }
 
 
 for (auto & t : tasks){ t.join(); }
 
 assertm(id.str() == result, "The concurrent increment result must be" );
}

void test_concurrent_pre_increment(auto id, auto count, auto result){
 std::vector<std::thread> tasks {};
 
 for (auto i = 0; i < count; ++i){
  std::thread t{[&](){ ++id; }};
  tasks.push_back(std::move(t));
 }
 
 
 for (auto & t : tasks){ t.join(); }
 
 assertm(id.str() == result, "The concurrent increment result must be" );
}

std::mutex pm;
int main() {
 
 IDExpression id{};
 
 id = "A1";
 
 std::vector<std::thread> tasks {};
 
 for (auto i = 0; i < 9 * 18; ++i){
  std::thread t{[&](){ ++id;}};
  tasks.push_back(std::move(t));
 }
 
 
 for (auto & t : tasks){
  t.join();
 }
 

 std::cout<<id.str()<<std::endl;
 
//test wrapping when max pair count exceeded...
 test_concurrent_post_increment(IDExpression{"Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"}, 10, "B1");
 test_concurrent_pre_increment(IDExpression{"Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9"}, 10, "B1");
//
 test_concurrent_post_increment(IDExpression{"Z9"}, 10, "A1-B1");
 test_concurrent_pre_increment(IDExpression{"Z9"}, 10, "A1-B1");

//test default expression
 test_concurrent_post_increment(IDExpression{"A1"}, 10, "B2");
 test_concurrent_pre_increment(IDExpression{"A1"}, 10, "B2");

 //test default expression
 test_concurrent_post_increment(IDExpression{}, 9 * 18, "Z1");
 test_concurrent_pre_increment(IDExpression{}, 9 * 18, "Z1");

 
 
 return 0;
}
