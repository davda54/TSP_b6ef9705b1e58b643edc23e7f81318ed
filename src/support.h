#ifndef TSP_CHALLENGE_KIWI_QUEUE_H
#define TSP_CHALLENGE_KIWI_QUEUE_H

#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>

template <typename Type, typename Compare = std::less<Type>>
class queue
{
public:
    explicit queue(const Compare& compare = Compare()) : _compare{compare} {}

    void push(Type element) {
        _elements.push_back(std::move(element));
        std::push_heap(_elements.begin(), _elements.end(), _compare);
    }

    Type pop() {
        std::pop_heap(_elements.begin(), _elements.end(), _compare);
        Type result = std::move(_elements.back());
        _elements.pop_back();
        return std::move(result);
    }

    bool empty() { return _elements.size() == 0; }

private:
    std::vector<Type> _elements;
    Compare _compare;
};

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

    std::vector<size_t> idx(v.size());
    std::iota(idx.begin(), idx.end(), 0);

    sort(idx.begin(), idx.end(),
         [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

    return idx;
}

#endif //TSP_CHALLENGE_KIWI_QUEUE_H
