#pragma once

template <typename T>
class StringBase
{
public:
    StringBase<T> &operator=(const StringBase<T> &str);
    int compare(const StringBase<T> &str) const;
    int compare(const T *str) const;
    int compare(const T *str, int len) const;
    int compareNoCase(const StringBase<T> &str) const;
    int compareNoCase(const T *str) const;
    int compareNoCase(const T *str, int len) const;
    void concat(const StringBase<T> &str);
    void concat(T c);
    void concat(const T *str);
    void concat(const T *str, int len);
    T getCharAt(int index) const;
    int getLength() const;
    bool isEmpty() const;
    bool isNotEmpty() const;
    bool isNone() const;
    bool isNotNone() const;
    const T *str() const;
    void set(const StringBase<T> &str);
    void set(T c);
    void set(const T *str);
    void set(const T *str, int len);
    void swap(StringBase<T> &other);

private:
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};
