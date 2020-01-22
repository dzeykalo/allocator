#pragma once
#include <iostream>

template <typename T>
struct link
{
    T data;
    link* next;
};

//template <typename T>


template <typename T>
class this_is_list
{
private:
    link<T>* first;
    link<T>* head;
public:
    class iterator
    {
    private:
      link<T>* first;
    public:
      iterator(link<T>* first) {this->first = first;}
      T& operator *(){ return first->data;}
      iterator operator++(int)
      {
        iterator itr = *this;
        first = first->next;
        return itr;
      }
      bool operator!=(const iterator &itr){return first != itr.first;}
      bool operator==(const iterator &itr){return first == itr.first;}
    };

    this_is_list()
    {
        first = nullptr;
        head = nullptr;
    };
    ~this_is_list(){}
    void push_back(T d)
    {
        link<T>* new_link = new link<T>;
        new_link->data = d;
        new_link->next = first;
        if (first == nullptr)
          head = new_link;
        first = new_link;

    }
    void display()
    {
        link<T>* current = first;
        while (current != nullptr)
        {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
    iterator begin(){return iterator(first);}
    iterator end(){return iterator(head);}
};