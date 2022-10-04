//
//  pair.hpp
//  A-Z1-9
//
//  Created by Anton2016 on 04.10.2022.
//

#ifndef pair_hpp
#define pair_hpp

#include <unordered_set>

//IDExpression Pair Interface
struct Pair{
 static const std::unordered_set<char> exception_set;
 char letter {'A'};
 char index {'1'};
 bool isFull() const;
 void reset();
 void operator++(int);

};

#endif /* pair_hpp */
