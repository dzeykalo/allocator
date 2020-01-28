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
    iterator operator++(int){return data++;}
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
    template <typename _T, typename _A>
    other_vector(other_vector<_T,_A> &ov)
    {
      auto itr = ov.begin();
      if (itr == data) return;

      space = ov.getSpace();
      T* new_malloc = alloc.allocate(space);
      sz = 0;
      for(;itr!=ov.end();itr++)
      {
        alloc.construct(&new_malloc[sz], *itr);
        sz++;
      }
      data = new_malloc;
    }
    template <typename _T, typename _A>
    other_vector(other_vector<_T,_A> &&ov)
    {
      auto itr = ov.begin();
      if (itr == data) return;

      space = ov.getSpace();
      T* new_malloc = alloc.allocate(space);
      sz = 0;
      for(;itr!=ov.end();itr++)
      {
        alloc.construct(&new_malloc[sz], *itr);
        sz++;
      }
      data = new_malloc;
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
    size_t getSpace(){return space;}
    iterator<T> begin(){return iterator<T>(data);}
    iterator<T> end(){return iterator<T>(&data[sz]);}
};