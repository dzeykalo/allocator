#include <iostream>
#include <vector>
#include <map>
#include "allocator.h"
#include "container.h"
#include "hard.h"

int main()
{
    /*################ std::map ####################################*/
    /*std::map<int, hard> _map;
    for(int i = 0; i <10; i++)
      _map.emplace(std::piecewise_construct, std::forward_as_tuple(i),std::forward_as_tuple(factorial<int>(i), fibonacci<int>(i)));
    for(auto &i : _map)
      std::cout << i.first << " " << i.second.fa << " " << i.second.fi << std::endl;*/

    /*################ std::map + other_allocator ##################*/
    /*std::map<int, hard, std::less<int>, other_allocator<hard>> __map;
    for(int i = 0; i <10; i++)
        __map.emplace(std::piecewise_construct, std::forward_as_tuple(i),std::forward_as_tuple(factorial<int>(i), fibonacci<int>(i)));
    for(auto &i : __map)
        std::cout << i.first << " " << i.second.fa << " " << i.second.fi << std::endl;*/

    /*################ other_vector + std:allocator ################*/
    /*other_vector<hard, std::allocator<hard>> _vector;
    for(int i = 0; i <10; i++)
        _vector.push_back(factorial<int>(i), fibonacci<int>(i));
    for(auto &i : _vector)
        std::cout << i.fa << " " << i.fi << std::endl;*/

    /*################ other_vector + other_allocator ##############*/
    /*other_vector<hard, other_allocator<hard>> __vector;
    for(int i = 0; i <10; i++)
        __vector.push_back(factorial<int>(i), fibonacci<int>(i));
    for(auto &i : __vector)
        std::cout << i.fa << " " << i.fi << std::endl;*/

    /*################ other_vector + copy constructor ##############*/
    /*other_vector<hard, std::allocator<hard>> from_vector;
    for(int i = 0; i <10; i++)
      from_vector.push_back(factorial<int>(i), fibonacci<int>(i));
    other_vector<hard, std::allocator<hard>> to_vector = from_vector;
    for(auto &i : to_vector)
      std::cout << i.fa << " " << i.fi << std::endl;*/

    /*################ other_vector + copy constructor ##############*/
    other_vector<hard, other_allocator<hard>> _from_vector;
    for(int i = 0; i <10; i++)
      _from_vector.push_back(factorial<int>(i), fibonacci<int>(i));
    other_vector<hard, std::allocator<hard>> _to_vector = std::move(_from_vector);
    for(auto i : _to_vector)
      std::cout << i.fa << " " << i.fi << std::endl;


    return 0;
}