#pragma once

const size_t more = 10;

template <typename T>
struct other_allocator
{
private:
    T* Pt;
    size_t space;
    size_t sz;
public:
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using value_type      = T;

    other_allocator():Pt(nullptr),space(0),sz(0){};

    pointer allocate(size_type st)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if ( space <= sz )
        {
            space += more;
            Pt = reinterpret_cast<pointer>(realloc(Pt, sizeof(T)*st*space));
            if (Pt == nullptr)
                throw std::bad_alloc();
        }

        return &Pt[sz++];
    }

    void deallocate (pointer p, size_type st)
    {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (--sz == 0) free(p);
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
