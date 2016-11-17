#pragma once

#include <vector>
#include <stdexcept>

namespace FP {

template <class Args, class F1>
auto Run(Args args, F1&& f1) {
    return f1(args);
};

template <class Args, class F1, class... Fs>
auto Run(Args args, F1&& f1, Fs&& ... fs) {
    return Run(f1(args), fs...);
};

template <class T>
class Pipeline {
private:
    using value_type = T;
    using func_t = value_type(*)(value_type);
    std::vector<func_t> steps_;
public:
    Pipeline() {}

    Pipeline(const Pipeline&) = delete;

    Pipeline(Pipeline&&) = delete;

    Pipeline& operator=(const Pipeline&) = delete;

    Pipeline& operator=(Pipeline&&) = delete;

    Pipeline& Register(func_t f) {
        steps_.push_back(f);
        return *this;
    }

    value_type operator()(value_type arg) {
        if (steps_.size() == 0)
            throw std::out_of_range("empty pipeline");
        value_type ret = steps_[0](arg);
        for (int i = 1; i < steps_.size(); ++i) {
            ret = steps_[i](ret);
        }
        return ret;
    }
};

}