#include <iostream>
#include <map>
#include "allocator.h"

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
    std::map<int, hard, std::less<int>, this_is_allocator<std::pair<const int, hard>, 10>> container;
    for(int i=0;i<10;i++)
        container.emplace(std::piecewise_construct, std::forward_as_tuple(i), std::forward_as_tuple(i, i));
    for(auto &[i, v] : container)
        std::cout << i << " " << v.fa << " " << v.fi << std::endl;
    return 0;
}