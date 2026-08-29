#pragma once

template <typename T>
class StringBase
{
public:
    int compare(const StringBase<T> &str) const;
    int compare(const T *str, int len) const;
    void concat(T c);
    void concat(const T *str, int len);
    int getLength() const;
    const T *str() const;
    void set(T c);
    void set(const T *str, int len);

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
