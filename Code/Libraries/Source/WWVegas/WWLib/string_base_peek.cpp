// cl: /O1
// BFME1 StringBase<T>::peek() transferred to BFME2.  This private accessor is
// kept in a TU-scoped layout mirror so the shared StringBase header stays
// unchanged while both explicit instantiations retain their retail boundary.

typedef unsigned short wchar_t;

template <typename T>
class StringBase
{
private:
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

private:
    T *peek() const;

private:
    Header *m_data;
};

template <typename T>
T *StringBase<T>::peek() const
{
    return &m_data->data[0];
}

template char *StringBase<char>::peek() const;
template wchar_t *StringBase<wchar_t>::peek() const;
