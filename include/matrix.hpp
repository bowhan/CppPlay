#pragma once

#include <initializer_list>
#include <cassert>

/// \brief base matrix class taking care of all static values so that they will be available in drived class
template <class T, size_t... NN>
class nMatrixBase {
private:

    /// \brief metafunction to canculate number of elements at the compile time (general form)
    template <size_t... KK>
    struct GetSize {
    };

    /// \brief metafunction to canculate number of elements at the compile time (partially specialized)
    template <size_t K, size_t... KK>
    struct GetSize<K, KK...> {
        const static size_t value = K * GetSize<KK...>::value;
    };

    /// \brief metafunction to canculate number of elements at the compile time (base case)
    template <size_t K>
    struct GetSize<K> {
        const static size_t value = K;
    };

public:
    /// \brief default constructor
    /// \return a nMatrixBase instance
    nMatrixBase()
        : dim_{sizeof...(NN)}, shape_{NN...} {
    }

    /// \brief return number of elements in the class
    /// \return number of elements in the class
    constexpr size_t totalSize() const noexcept {
        return total_size_;
    }

protected:
    /// \brief number of dimentions
    size_t dim_;

    /// \brief shape of the matrix, shape_ {2,3,4} means 2 x 3 x 4 matrix
    size_t shape_[sizeof...(NN)];

    /// \brief total number of elements
    static const size_t total_size_ = GetSize<NN...>::value;
};

/// \brief concrete class of Matrix
template <class T, size_t... NN>
class nMatrix
    : private nMatrixBase<T, NN...> {
private:
    using self = nMatrix<T, NN...>;
    using parent = nMatrixBase<T, NN...>;
    using parent::total_size_;
    using parent::shape_;
    using parent::dim_;

    template <class, size_t...> friend
    class nMatrix;

public:
    using pointer_type = T *;

    template <class U>
    using convert_t = nMatrix<U, NN...>;

    /// \brief constructor of Matrix from initializer list
    /// \param initial_values
    /// \return nMatrix instance
    nMatrix(const std::initializer_list<T>& initial_values) {
        size_t i = 0;
        for (auto x : initial_values) {
            data_[i++] = x;
            if (i == total_size_) break;
        }
    }

    /// \brief element access function, to support syntax arr({1,2,3...})
    /// \param dimentions
    /// \return element at a position
    T& operator()(const std::initializer_list<size_t>& dimentions) {
        assert(dimentions.size() == dim_);
        size_t idx{0}, i{1}, tmp;
        for (auto d : dimentions) {
            tmp = d;
            for (size_t j = i++; j < dim_; ++j) {
                tmp *= shape_[j];
            }
            idx += tmp;
        }
        return data_[idx];
    }

    /// \brief element access function, to support syntax arr(1,2,3...)
    /// \param d1 first dimention
    /// \param drest the other dimentions
    /// \return element at position pointed by the dimentions
    template <class... Ints>
    // have to use template even though we know Ints are int
    size_t getIndex(size_t d1, Ints... drest) {
        size_t idx = 1;
        size_t i = dim_ - sizeof...(drest);
        for (size_t j = i; j < dim_; ++j)
            idx *= shape_[j] * d1;
        return idx + getIndex(drest...);
    }

    /// \brief base case for element access function (last dimention)
    /// \param d last dimention
    /// \return base case
    size_t getIndex(size_t d) {
        return d;
    }

    /// \brief element access function, to support syntax arr(1,2,3...)
    /// \param idx dimentions as variadic arguments
    /// \return element at a position
    template <class... Ints>
    T& operator()(Ints... idx) {
        return data_[getIndex(idx...)];
    }

    /// \brief
    /// \param other
    /// \return
    self operator+(const self& other) {
        self result{};
        for (size_t i = 0; i < total_size_; ++i) {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    /// \brief
    /// \param other
    /// \return
    self operator-(const self& other) {
        self result{};
        for (size_t i = 0; i < total_size_; ++i) {
            result.data_[i] = data_[i] - other.data_[i];
        }
        return result;
    }

    /// \brief
    /// \param other
    /// \param f
    /// \return
    self operate(const self& other, T(f)(const T&, const T&)) {
        self result{};
        for (size_t i = 0; i < total_size_; ++i) {
            result.data_[i] = f(data_[i], other.data_[i]);
        }
        return result;
    }

    template <class U>
    auto operate(const nMatrix<U, NN...>& other
                 , auto (f)(const T&, const U&)
                 , std::enable_if_t<std::is_convertible<T, U>::value, void **> = nullptr
                ) {
        using W = std::result_of_t<decltype(f)(const T&, const U &)>;
        nMatrix<W, NN...> result{};
        for (size_t i = 0; i < total_size_; ++i) {
            result.data_[i] = f(data_[i], other.data_[i]);
        }
        return result;
    }

    // TODO: learn from numpy on how to display matrices with dimentions higher than 2
    /// \brief display matrix
    /// \return output ostream
    friend std::ostream& operator<<(std::ostream& os, const self& mx) {
        return os;
    }

    #define DEFINE_MATRIX_SIMPLE_OPERATOR_OVERLOALING(__x) \
    self operator __x (T t) { self result{}; for(size_t i = 0; i < total_size_; ++i) { result.data_[i] = data_[i] __x t; } return result; }

    #define DEFINE_MATRIX_SIMPLE_BINARY_OPERATOR_OVERLOALING(__x) \
    void operator __x##= (T t) { for(size_t i = 0; i < total_size_; ++i) { data_[i] __x##= t; } }

    #define DEFINE_MATRIX_SIMPLE_FRIEND_OPERATOR(__x) \
        friend self operator __x (T t, const self& mx) { self result{}; for (size_t i = 0; i < total_size_; ++i) { result.data_[i] = mx.data_[i] __x t; } return result; }

    #define DEFINE_MATRIX_SIMPLE_FRIEND_OPERATOR_REV(__x) \
        friend self operator __x (T t, const self& mx) { self result{}; for (size_t i = 0; i < total_size_; ++i) { result.data_[i] = t __x mx.data_[i]; } return result; }


    DEFINE_MATRIX_SIMPLE_OPERATOR_OVERLOALING(+)

    DEFINE_MATRIX_SIMPLE_OPERATOR_OVERLOALING(-)

    DEFINE_MATRIX_SIMPLE_OPERATOR_OVERLOALING(*)

    DEFINE_MATRIX_SIMPLE_OPERATOR_OVERLOALING(/)

    DEFINE_MATRIX_SIMPLE_BINARY_OPERATOR_OVERLOALING(+)

    DEFINE_MATRIX_SIMPLE_BINARY_OPERATOR_OVERLOALING(-)

    DEFINE_MATRIX_SIMPLE_BINARY_OPERATOR_OVERLOALING(*)

    DEFINE_MATRIX_SIMPLE_BINARY_OPERATOR_OVERLOALING(/)

    DEFINE_MATRIX_SIMPLE_FRIEND_OPERATOR(+)

    DEFINE_MATRIX_SIMPLE_FRIEND_OPERATOR(-)

    DEFINE_MATRIX_SIMPLE_FRIEND_OPERATOR(*)

    DEFINE_MATRIX_SIMPLE_FRIEND_OPERATOR_REV(/)

protected:
    /// \brief array
    T data_[total_size_];
};

