#pragma once

template <typename T, size_t Size>
struct this_is_allocator
{
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using value_type      = T;

    pointer allocate(size_type st)
    {
        auto ptr = malloc(sizeof(T)*Size);
        if (ptr == nullptr)
            throw std::bad_alloc();
        return reinterpret_cast<pointer>(ptr);
    }

    void deallocate (pointer p, size_type st)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        free(p);
    }

    template<typename U, typename... Args>
    void construct (U *p, Args&&... args)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy (pointer p)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~value_type();
    }
    template <typename U>
    struct rebind {
        using other = this_is_allocator<U,Size>;
    };
};
