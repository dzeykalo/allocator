#pragma once

const size_t space = 10;

template <typename T>
struct other_allocator
{
private:
    T* Pt;
    size_t sz;
    std::vector<T*> pt_storage;
public:
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using value_type      = T;

    other_allocator():Pt(nullptr),sz(0),pt_storage(){};

    pointer allocate(size_type st)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if ( space <= sz || sz == 0 )
        {
          sz = 0;
          Pt = reinterpret_cast<pointer>(malloc(sizeof(T)*space));
          if (Pt == nullptr)
              throw std::bad_alloc();
          pt_storage.push_back(Pt);
        }
        auto t_sz = sz;
        sz+=st;
        if (sz > space)
          throw std::bad_alloc();

        return &pt_storage.back()[t_sz];
    }

    void deallocate (pointer p, size_type st)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        sz -= st;
        if (sz <= 0)
        {
          if (pt_storage.size()>1)
            sz += space;
          else
            sz = 0;

          if (!pt_storage.empty()) {
            free(p);
            pt_storage.pop_back();
          }
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
