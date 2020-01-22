#pragma once
#include <iostream>

template <typename T>
struct link
{
    T data;
    link* next;
};

template <typename T>
class iterator
{
private:
    link<T>* first;
public:

    iterator(): first(nullptr){};
    iterator(link<T>* first): first(first){};
    T& operator *(){ return first->data;}
    iterator operator++()
    {
        first = first->next;
        return *this;
    }
    bool operator!=(const iterator &itr){return first != itr.first;}
    bool operator==(const iterator &itr){return first == itr.first;}
};

template <typename T>
class this_is_list
{
private:
    link<T>* first;
public:

    this_is_list():first(nullptr){};
    ~this_is_list(){};
    void push_back(T d)
    {
        link<T>* new_link = new link<T>;
        new_link->data = d;
        new_link->next = first;
        first = new_link;

    }
    iterator<T> begin(){return iterator<T>(first);}
    iterator<T> end(){return iterator<T>();}
};