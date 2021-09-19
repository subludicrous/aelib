// © subludicrous
// SPDX-License-Identifier: BSL-1.0

#include <ae/base.h>
#include <cstdio>

struct test_struct {
private:
    inline static int next_id = 1;

    void invalidate() noexcept {
        id = -1;
    }
public:
    int id;

    explicit test_struct() noexcept {
        id = next_id;
        ++next_id;
        std::printf("test_struct id: %02d, fn: constructor\n", id);
    }

    explicit test_struct(test_struct const &other) noexcept {
        id = next_id++;
        std::printf("test_struct id: %02d, fn: copy constructor\n", id);
    }

    explicit test_struct(test_struct &&other) noexcept {
        id = other.id;
        other.invalidate();
        std::printf("test_struct id: %02d, fn: move constructor\n", id);
    }

    test_struct &operator=(test_struct const &other) noexcept {
        id = other.id;
        std::printf("test_struct id: %02d, fn: copy operator\n", id);
        return *this;
    }

    test_struct &operator=(test_struct &&other) noexcept {
        id = other.id;
        other.invalidate();
        std::printf("test_struct id: %02d, fn: move operator\n", id);
        return *this;
    }

    ~test_struct() {
        std::printf("test_struct id: %02d, fn: destructor\n", id);
    }

    void test() noexcept {
        std::printf("test_struct id: %02d, fn: test\n", id);
    }
};
