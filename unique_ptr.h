#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <ranges>

namespace my_std
{

/**
 * @brief default deleter for my_std::unique_ptr.
 *
 * @tparam T type of object for the unique_ptr for deletion.
 */
template <class T>
struct default_delete
{
    /**
     * @brief when calling this struct as a function it will do whats inside {}.
     *
     * @param p pointer to our generic type.
     */
    constexpr void operator()(T *p) const
    {
        delete p;
    }

    constexpr bool operator==(const default_delete &) const = default;
};

/**
 * @brief unique_ptr class.
 *
 * @tparam T Type of the object for the smart pointer.
 * @tparam D deleter function (default = default_deleter<T>).
 */
template <class T, class D = default_delete<T>>
class unique_ptr
{
  public:
    using pointer = T *;
    using element_type = T;
    using deleter_type = D;

    /**
     * @brief creates a unique_ptr that points to a nullptr if not arguments are
     * passed into the constructor.
     *
     */
    constexpr unique_ptr()
        : unique_ptr{nullptr} // calls the other(second) constructor.
    {
    }

    /**
     * @brief creates the standard unique_ptr.
     *
     */
    constexpr unique_ptr(pointer p) : obj_{p}, deleter_{}
    {
    }

    /**
     * @brief on deletion of unique_ptr it calls the destructor.
     *
     */
    constexpr ~unique_ptr()
    {
        if (obj_ != nullptr)
        {
            deleter_(obj_);
        }
    }

    /**
     * @brief Deleted copy constructor and copy assignment operator for unique
     * ownership semantics. (Unable to copy object).
     *
     */
    constexpr unique_ptr(const unique_ptr &) = delete;
    constexpr unique_ptr &operator=(const unique_ptr &) = delete;

    /**
     * @brief swaps pointers. e.g unique_ptr<int> up2(up).
     *
     */
    constexpr unique_ptr(unique_ptr &&other) : unique_ptr{}
    {
        swap(other);
    }
    /**
     * @brief transfers ownership through the assignment operator.
     *
     * @param other the other unique_ptr where ownership will be moved to.
     * @return constexpr unique_ptr&
     */
    constexpr unique_ptr &operator=(unique_ptr &&other)
    {
        unique_ptr new_obj{std::move(
            other)};   // transfer ownership to other (calls constructor above).
        swap(new_obj); // swaps the objects.

        return *this;
    }

    /**
     * @brief returns the derefence of obj_. e.g *up.
     *
     * @return constexpr element_type&
     */
    constexpr element_type &operator*() const noexcept
    {
        return *obj_;
    }
    /**
     * @brief returns the obj_. e.g up->x.
     *
     * @return constexpr pointer
     */
    constexpr pointer operator->() const noexcept
    {
        return obj_;
    }
    /**
     * @brief returns the obj_.
     *
     * @return constexpr pointer
     */
    constexpr pointer get() const noexcept
    {
        return obj_;
    }

    /**
     * @brief swaps object.
     *
     * @param other reference to the other unique_ptr.
     */
    constexpr void swap(unique_ptr &other) noexcept
    {
        std::ranges::swap(obj_, other.obj_);
        std::ranges::swap(deleter_, other.deleter_);
    }

    /**
     * @brief allows for: if (unique_ptr) {...}.
     * explicit means that you can only use it in places like loops and ifs but
     * cannot assign it to a bool variable.
     *
     * @return true if there is an object present.
     * @return false if there is no object present.
     */
    constexpr explicit operator bool() const noexcept
    {
        return obj_ != nullptr;
    }

    constexpr bool operator==(const unique_ptr &other) const
    {
        return get() == other.get();
    }

  private:
    pointer obj_;
    [[no_unique_address]] deleter_type deleter_;
};

/**
 * @brief creates a unique_ptr with set given args.
 *
 * @tparam T Type of the unique_ptr.
 * @tparam Args ... any valid arguments to pass for T.
 * @param args ... any valid arguments to pass for T.
 * @return unique_ptr<T>
 */
template <class T, class... Args>
unique_ptr<T> make_unique(Args &&...args)
{
    return unique_ptr(new T{std::forward<Args>(args)...});
}

} // namespace my_std

#endif /* UNIQUE_PTR_H */
