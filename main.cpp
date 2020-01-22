#include <iostream>
#include <map>
#include "allocator.h"
#include "contaiter.h"
#include <list>

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
  this_is_list<int> _list;
  for(int i = 0; i <10; i++)
    _list.push_back(i);
  for(auto i = _list.begin(); i != _list.end(); i++)
    std::cout << *i << std::endl;
  return 0;
}