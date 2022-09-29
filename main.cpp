#include <iostream>

class Vector {
public:
    Vector() : capacity_(10), size_(0) {
        data_ = new int[10];
    }
    Vector(size_t size) : size_(size), capacity_(size * 2) {
        data_ = new int[2 * size]();
    }
    Vector(const int *other, size_t size) : size_(size), capacity_(size * 2) {
        data_ = new int[2 * size];
        for (size_t i = 0; i < size; ++i) {
            data_[i] = other[i];
        }
    }
    Vector(std::initializer_list<int> l) {
        size_ = l.size();
        capacity_ = 2 * size_;
        data_ = new int[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = *(l.begin() + i);
        }
    }
    Vector(const Vector &other)
        : size_(other.size_), data_(new int[2 * size_]), capacity_(other.size_ * 2) {
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    ~Vector() {
        delete[] data_;
    }

    struct Iterator {
        using IteratorCategory = std::random_access_iterator_tag;
        using DifferenceType = std::ptrdiff_t;

        Iterator(int *ptr) : m_ptr_(ptr){};

        int &operator*() const {
            return *m_ptr_;
        }

        int *operator->() {
            return m_ptr_;
        }

        Iterator &operator++() {
            ++m_ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++*this;
            return temp;
        }

        Iterator &operator--() {
            --m_ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --*this;
            return temp;
        }

        Iterator operator+(const DifferenceType &movement) {
            return {m_ptr_ + movement};
        }

        Iterator operator-(const DifferenceType &movement) {
            return {m_ptr_ - movement};
        }

        Iterator &operator+=(const DifferenceType &movement) {
            m_ptr_ += movement;
            return *this;
        }

        Iterator &operator-=(const DifferenceType &movement) {
            m_ptr_ -= movement;
            return *this;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.m_ptr_ == b.m_ptr_;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return !(a == b);
        }

        friend int64_t operator-(const Iterator &a, const Iterator &b) {
            return a.m_ptr_ - b.m_ptr_;
        }

        Iterator begin() {
            return {m_ptr_};
        }

        Iterator end() {
            return {m_ptr_};
        }

    private:
        int *m_ptr_;
    };

    [[nodiscard]] size_t getSize() const {
        return size_;
    }

    [[nodiscard]] size_t getCapacity() const {
        return capacity_;
    }

    [[nodiscard]] bool isEmpty() const {
        if (size_ == 0) {
            return true;
        }
        return false;
    }

    void resize(size_t n_size) {
        if (n_size >= capacity_) {
            capacity_ = 2 * n_size;
        }
        int *copy = new int[n_size];
        for (size_t i = 0; i < size_ && i < n_size; ++i) {
            copy[i] = data_[i];
        }
        delete[] data_;
        data_ = copy;
        size_ = n_size;
    }

    void pushBack(int el) {
        if (size_ == capacity_) {
            size_t old_cap = capacity_;
            capacity_ = old_cap * 2;
            int *copy = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                copy[i] = data_[i];
            }
            delete[] data_;
            data_ = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = copy[i];
            }
            delete[] copy;
        }
        data_[size_++] = el;
    }

    void popBack() {
        if (size_ == 0) {
            throw std::runtime_error("Empty Array!");
        }
        int *copy = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            copy[i] = data_[i];
        }
        delete[] data_;
        --size_;
        data_ = new int[size_ * 2];
        for (int i = 0; i < size_; ++i) {
            data_[i] = copy[i];
        }
        delete[] copy;
    }

    void clear() {
        delete[] data_;
        data_ = new int[capacity_];
        size_ = 0;
    }

    void insert(size_t ind, int val) {
        int *copy = new int[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            copy[i] = data_[i];
        }
        if (ind > size_) {
            delete[] copy;
            throw std::runtime_error("Wrong Position!");
        } else {
            if (size_ >= capacity_) {
                size_t old_cap = capacity_;
                ++size_;
                capacity_ = old_cap * 2;
                delete[] data_;
                data_ = new int[capacity_];
                for (size_t i = 0; i < ind; ++i) {
                    data_[i] = copy[i];
                }
                data_[ind] = val;
                for (size_t i = ind + 1; i < size_; ++i) {
                    data_[i] = copy[i - 1];
                }
                delete[] copy;
            } else {
                for (size_t i = 0; i < ind; ++i) {
                    data_[i] = copy[i];
                }
                data_[ind] = val;
                size_t old_cap = capacity_;
                ++size_;
                capacity_ = old_cap * 2;
                for (size_t i = ind + 1; i < size_; ++i) {
                    data_[i] = copy[i - 1];
                }
                delete[] copy;
            }
        }
    }

    void erase(size_t ind) {
        if (size_ == 0) {
            throw std::runtime_error("Empty Array!");
        }
        if (ind >= size_) {
            throw std::runtime_error("Wrong Position!");
        }
        for (size_t i = ind; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    int at(size_t pos) {
        if (pos >= size_) {
            throw std::runtime_error("Wrong Position!");
        }
        return data_[pos];
    }

    int front() {
        if (size_ == 0) {
            throw std::runtime_error("Empty Array!");
        }
        return data_[0];
    }

    int back() {
        if (size_ == 0) {
            throw std::runtime_error("Empty Array!");
        }
        return data_[size_ - 1];
    }

    Iterator begin() {
        if (size_ != 0) {
            return {&data_[0]};
        }
        return end();
    }

    Iterator end() {
        auto iter = Iterator(&data_[size_]);
        return iter.end();
    }

    int &operator[](size_t ind) const {
        if (ind >= size_) {
            throw std::runtime_error("Wrong Position");
        }
        return data_[ind];
    }

    Vector &operator=(const Vector &other) = default;

private:
    size_t capacity_;
    size_t size_;
    int *data_;
};

void merge(Vector::Iterator begin, Vector::Iterator end) {
    auto i = begin;
    auto middle = begin + (end - begin) / 2;
    auto j = middle;
    Vector v;
    while (middle - i > 0 && end - j > 0) {
        if (*i <= *j) {
            v.pushBack(*i);
            ++i;
        } else {
            v.pushBack(*j);
            ++j;
        }
    }
    while (middle - i > 0) {
        v.pushBack(*i);
        ++i;
    }
    while (end - j > 0) {
        v.pushBack(*j);
        ++j;
    }
    for (int &it : v) {
        *begin = it;
        ++begin;
    }
}

void mergeSort(Vector::Iterator begin, Vector::Iterator end) {
    if (end - begin > 1) {
        auto middle = begin + (end - begin) / 2;
        mergeSort(begin, middle);
        mergeSort(middle, end);
        merge(begin, end);
    }
}

void insertionSort(Vector::Iterator begin, Vector::Iterator end) {
    if (end == begin) {
        return;
    }
    for (auto it = begin + 1; it != end; ++it) {
        Vector::Iterator key = it;
        for (Vector::Iterator i = it - 1; i - begin >= 0; --i) {
            if (*i > *key) {
                std::swap(i, key);
                --key;
            } else {
                break;
            }
        }
    }
}
