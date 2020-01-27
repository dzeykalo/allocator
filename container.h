#pragma once
#include <iostream>

const int container_size = 10;

template <typename T>
class iterator
{
private:
    T* data;
public:

    iterator(): data(nullptr){};
    iterator(T* d): data(d){};
    T& operator [](int n){ return data[n];}
    T& operator *(){ return *data;}
    iterator operator++(){return data++;}
    bool operator!=(const iterator &itr){return data != itr.data;}
    bool operator==(const iterator &itr){return data == itr.data;}
};

template <typename T, typename A>
class other_vector
{
private:
    size_t sz;
    T* data;
    size_t space;
    A alloc;
public:
    other_vector():data(nullptr),sz(0),space(0){};
    template <typename other_alloc>
    other_vector(other_vector<T,other_alloc> &&oa):other_vector()
    {
      for(size_t i = 0; i < sz; i++)
        oa.push_back(data[i]);
    }
    ~other_vector()
    {
      for(size_t i = 0; i < sz; i++)
      {
        alloc.destroy(&data[i]);
      }
      alloc.deallocate(data, space);
    }
    template<typename... Args>
    void reserve (size_t new_alloc)
    {
      if (new_alloc < space) return;
      T* new_malloc = alloc.allocate(new_alloc);
      for(size_t i = 0; i < sz; i++)
      {
        alloc.construct(&new_malloc[i], data[i]);
        alloc.destroy(&data[i]);
      }
      alloc.deallocate(data, space);
      data = new_malloc;
      space = new_alloc;
    }
    template<typename... Args>
    void push_back(Args &&... args)
    {
        if (space == sz)
          reserve(space+container_size);
        alloc.construct(&data[sz],std::forward<Args>(args)...);
        sz++;
    }
    iterator<T> begin(){return iterator<T>(data);}
    iterator<T> end(){return iterator<T>(&data[sz]);}
};