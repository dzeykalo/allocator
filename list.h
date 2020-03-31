#pragma once
#include <iostream>

template <typename T>
struct link
{
    T data;
    link* next;
    link* previous;
};

template <typename T>
class iterator_list
{
private:
    link<T>* l;
public:

    iterator_list(): l(nullptr){};
    iterator_list(link<T>* _l): l(_l){};
    T& operator *(){ return l->data;}
    iterator_list operator++()
    {
        l = l->previous;
        return *this;
    }
    iterator_list operator++(int)
    {
        l = l->previous;
        return *this;
    }
    bool operator!=(const iterator_list &itr){return l != itr.l;}
    bool operator==(const iterator_list &itr){return l == itr.l;}
};

template <typename T, typename A = std::allocator<link<T>>>
class other_list
{
private:
    link<T>* first;
    link<T>* last;
    typename A::template rebind<link<T>>::other alloc;
public:
    other_list():first(nullptr),last(nullptr){};
    template <typename _A>
    other_list(other_list<T, _A> &ol):first(nullptr),last(nullptr)
    {
        for (auto &i : ol)
            push_back(i);
    }
    template <typename _A>
    other_list(other_list<T, _A> &&ol):first(nullptr),last(nullptr)
    {
        std::swap(first, ol.first);
        std::swap(last, ol.last);
        std::swap(alloc, ol.alloc);
    }

    ~other_list()
    {
        while (first != last)
        {
            alloc.deallocate(first,1);
            first = first->next;
        }
        alloc.deallocate(last,1);
    };
    template<typename... Args>
    void push_back(Args &&... args)
    {
        if (first == nullptr && last == nullptr)
        {
            first = alloc.allocate(1);
            alloc.construct(&first->data,std::forward<Args>(args)...);
            last = first;
            return;
        }
        link<T>* new_link = alloc.allocate(1);
        alloc.construct(&new_link->data,std::forward<Args>(args)...);
        new_link->next = first;
        first->previous = new_link;
        first = new_link;
    }
    iterator_list<T> begin(){return iterator_list<T>(last);}
    iterator_list<T> end(){return iterator_list<T>(first->previous);}
};
