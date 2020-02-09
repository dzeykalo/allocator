#include <iostream>
#include <vector>
#include <map>
#include "allocator.h"
#include "container.h"
#include "hard.h"
#include "list"
#include "list.h"

int main()
{
    {
        //################ std::map ####################################//
        std::map<int, hard> _map;
        for (int i = 0; i < 10; i++)
            _map.emplace(std::piecewise_construct, std::forward_as_tuple(i),
                         std::forward_as_tuple(factorial<int>(i), fibonacci<int>(i)));
        for (auto &i : _map)
            std::cout << i.first << " " << i.second.fa << " " << i.second.fi << std::endl;
    }
    {
        //################ std::map + other_allocator ##################//
        std::map<int, hard, std::less<int>, other_allocator<std::pair<const int, hard>>> __map;
        for (int i = 0; i < 10; i++)
            __map.emplace(std::piecewise_construct, std::forward_as_tuple(i),
                          std::forward_as_tuple(factorial<int>(i), fibonacci<int>(i)));
        for (auto &i : __map)
            std::cout << i.first << " " << i.second.fa << " " << i.second.fi << std::endl;
    }
    {
        //################ other_list + std:allocator ################//
        other_list<hard> list;
        for (int i = 0; i < 10; i++)
            list.push_back(factorial<int>(i), fibonacci<int>(i));
        for (auto &i : list)
            std::cout << i.fi << " " << i.fa << std::endl;
    }
    {
        //################ other_list + other_allocator ##############//
        other_list<hard, other_allocator<hard>> list;
        for (int i = 0; i < 10; i++)
            list.push_back(factorial<int>(i), fibonacci<int>(i));
        for (auto &i : list)
            std::cout << i.fa << " " << i.fi << std::endl;
    }
    {
        //################ other_list + copy constructor ##############//
        other_list<hard, other_allocator<hard>> from_list;
        for (int i = 0; i < 10; i++)
            from_list.push_back(factorial<int>(i), fibonacci<int>(i));
        other_list<hard, other_allocator<hard>> to_list = from_list;
        for (auto &i : to_list)
            std::cout << i.fa << " " << i.fi << std::endl;
    }
    {
        //################ other_list + move ##############//
        other_list<hard, other_allocator<hard>> _from_list;
        for (int i = 0; i < 10; i++)
            _from_list.push_back(factorial<int>(i), fibonacci<int>(i));
        other_list<hard, other_allocator<hard>> _to_list = std::move(_from_list);
        for (auto i : _to_list)
            std::cout << i.fa << " " << i.fi << std::endl;
    }

    return 0;
}