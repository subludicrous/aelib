// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#ifndef AE_DARRAY_HPP
#define AE_DARRAY_HPP

/**
* ABOUT:
* ae::darray is a bootleg std::vector.
*/

#include <ae/base.h>
#include <ae/memory.hpp>

AE_BEGIN

template <
    typename T, 
    typename CAllocator = c_allocator<T, abort_noexcept>
>
struct darray {
    using value_type = T;
    using allocator_type = CAllocator;
    static_assert(is_same_v<value_type, typename allocator_type::value_type>,
        "CAllocator must have the same value_type.");

    [[nodiscard]]
    darray() noexcept {
        mem = allocator_type::alloc_fn(res_elem_amount);
        used = 0;
        reserved = mem ? res_elem_amount : 0;
    }

    ~darray() {
        // destruct from end to start:
        for (auto rendit = mem + used; rendit != mem; ) {
            --rendit;
            ae::dtor(*rendit);
        }
        ae::tfree(mem);
    }

    [[nodiscard]]
    value_type &operator[](std::size_t const i) noexcept {
        return mem[i];
    }

    [[nodiscard]]
    value_type const &operator[](std::size_t const i) const noexcept {
        return mem[i];
    }

    [[nodiscard]]
    value_type *begin() noexcept {
        return mem;
    }

    [[nodiscard]]
    value_type *end() noexcept {
        return mem + used;
    }

    [[nodiscard]]
    value_type const *begin() const noexcept {
        return mem;
    }

    [[nodiscard]]
    value_type const *end() const noexcept {
        return mem + used;
    }

    [[nodiscard]]
    value_type const *cbegin() const noexcept {
        return begin();
    }

    [[nodiscard]]
    value_type const *cend() const noexcept {
        return end();
    }

    [[nodiscard]]
    std::size_t count() const noexcept {
        return used;
    }

    // return a bool in case we don't use a noreturn fn.\
    for handler
    bool reserve(std::size_t const req) noexcept {
        // won't downsize
        if (req > reserved) {
            return reserve_unchecked();
        }
        return true;
    }

    value_type *push_back(value_type copy) {
        // resize if needed, then move passed copy
        if (reserve_opt()) {
            // = *new (mem + used) value_type(std::move(copy));
            value_type &nref = ctor<value_type>(mem + used, std::move(copy));
            ++used;
            return &nref;
        }
        return nullptr;
    }

    template <typename ...Args>
    value_type *emplace_back(Args ...args) {
        if (reserve_opt()) {
            value_type &nref = ctor<value_type>(mem + used, move(args)...);
            ++used;
            return &nref;
        }
        return nullptr;
    }

private:
    value_type *mem;
    static constexpr std::size_t res_elem_amount = 32;
    std::size_t reserved;
    std::size_t used;

    bool reserve_opt() noexcept {
        // reserves more if all reserved space has been used
        if (used == reserved) {
            auto const nres = used + res_elem_amount; // new capacity
            // reserve more:
            return reserve_unchecked(nres);
        }
        return true;
    }

    bool reserve_unchecked(std::size_t const req) noexcept {
        auto const nmem = allocator_type::realloc_fn(mem, req);
        if (nmem) {
            mem = nmem;
            reserved = req;
        }
        return nmem;
    }
};

AE_END

#endif // AE_DARRAY_HPP
