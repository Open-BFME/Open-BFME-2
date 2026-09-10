// cl: /O1
// BFME1 StringBase cleanup entry points transferred to BFME2.  The wrappers
// tail-jump to the existing BFME2 releaseBuffer workers, so this mirror keeps
// the shared header and the worker implementations untouched.

typedef unsigned short wchar_t;

template <typename T>
class StringBase
{
public:
    void clear();

private:
    void releaseBuffer();
    ~StringBase();

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

template <typename T>
void StringBase<T>::clear()
{
    releaseBuffer();
}

template <typename T>
StringBase<T>::~StringBase()
{
    releaseBuffer();
}

template void StringBase<char>::clear();
template void StringBase<wchar_t>::clear();
template StringBase<char>::~StringBase();
template StringBase<wchar_t>::~StringBase();
