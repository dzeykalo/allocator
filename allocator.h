#pragma once
#include<algorithm>

const size_t space = 10;

template <typename T>
struct other_allocator
{
private:
    size_t sz;
    std::vector<T*> pt_storage;
public:
    using size_type       = size_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using value_type      = T;

    other_allocator():sz(0),pt_storage(){};

    pointer allocate(size_type st)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if ( sz + st > space || sz == 0 )
        {
          sz = 0;
          pointer pt = reinterpret_cast<pointer>(malloc(sizeof(T)*space));
          if (pt == nullptr)
              throw std::bad_alloc();
          pt_storage.push_back(pt);
        }
        auto j = sz;
        sz+=st;
        return &pt_storage.back()[j];
    }

    void deallocate (pointer p, size_type st)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
      auto result = std::find(pt_storage.begin(), pt_storage.end(), p);
      if (result != pt_storage.end()){
        free(*result);
        pt_storage.erase(result);
      }
    }

    template<typename U, typename... Args>
    void construct (U *p, Args&&... args)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;

        new(p) U(std::forward<Args>(args)...);
    }

    void destroy (pointer p)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~value_type();
    }
    template <typename U>
    struct rebind {
        using other = other_allocator<U>;
    };
};
