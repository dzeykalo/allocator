#include <iostream>
#include <map>
#include "allocator.h"
#include "contaiter.h"
#include <list>
#include "hard.h"

struct hard
{
    int fa;
    int fi;
    hard(int fa, int fi) : fa(fa), fi(fi) {};
    hard() : fa(0), fi(0) {};
    hard(const hard &) = delete;
    hard(hard &&) noexcept = delete;
    ~hard(){};

};

int main() {
  const int N = 10;
  this_is_list<int, this_is_allocator<link<int>,10>> _list;
  for(int i = 0; i <10; i++)
  {
    //_list.push_back(i);
    std::cout << i << " " << fibonacci<int>(i) << std::endl;
  }

  /*for(auto &i : _list)
    std::cout << i << std::endl;*/
  return 0;
}