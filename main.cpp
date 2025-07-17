#include "tester.h"
#include "unique_ptr.h"
#include <print>

struct Foo
{
    Foo(bool *deleted) : deleted{deleted}
    {
    }

    ~Foo()
    {
        *deleted = true;
    }

    bool *deleted;
};

int main()
{
    {
        bool deleted = false;

        {
            my_std::unique_ptr<Foo>(new Foo{&deleted});
        }

        ASSERT_TRUE(deleted);
    }

    {
        my_std::unique_ptr<int> p(new int{42});
        ASSERT_EQ(*p, 42);
    }

    {
        struct Bar
        {
            int x;
        };
        my_std::unique_ptr<Bar> p(new Bar{});
        p->x = 42;
        ASSERT_EQ(p->x, 42);
    }

    {
        my_std::unique_ptr<int> p1(new int{});
        const auto saved_ptr = p1.get();

        my_std::unique_ptr<int> p2(std::move(p1));

        // my_std::unique_ptr<int> p2 = std::move(p1);
        /* '=' here means the
         * compiler will look through all the constructors and if one matches it
         * will call it.
         */

        ASSERT_EQ(p1.get(), nullptr);
        ASSERT_EQ(p2.get(), saved_ptr);
    }

    {
        my_std::unique_ptr<int> p1(new int{});
        const auto saved_ptr = p1.get();

        my_std::unique_ptr<int> p2(new int{});
        p2 = std::move(p1);

        ASSERT_EQ(p1.get(), nullptr);
        ASSERT_EQ(p2.get(), saved_ptr);
    }

    {
        struct Bar
        {
            int x;
            int y;
            int z;
        };

        auto p = my_std::make_unique<Bar>(1, 2, 3);

        ASSERT_EQ(p->x, 1);
        ASSERT_EQ(p->y, 2);
        ASSERT_EQ(p->z, 3);
    }

    return 0;
}
