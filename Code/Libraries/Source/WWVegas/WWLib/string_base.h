#pragma once

template <typename T>
class StringBase
{
public:
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
