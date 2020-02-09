#pragma once
#include <iostream>

const int container_size = 10;

template <typename T>
class iterator_vector
{
private:
    T* data;
public:

    iterator_vector(): data(nullptr){};
    iterator_vector(T* d): data(d){};
    T& operator [](int n){ return data[n];}
    T& operator *(){ return *data;}
    iterator_vector operator++(){return data++;}
    iterator_vector operator++(int){return data++;}
    bool operator!=(const iterator_vector &itr){return data != itr.data;}
    bool operator==(const iterator_vector &itr){return data == itr.data;}
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
    iterator_vector<T> begin(){return iterator_vector<T>(data);}
    iterator_vector<T> end(){return iterator_vector<T>(&data[sz]);}
};