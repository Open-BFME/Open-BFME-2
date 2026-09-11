// cl: /O1
// BFME1 StringBase cleanup entry points transferred to BFME2.  The wrappers
// tail-jump to the existing BFME2 releaseBuffer workers, so this mirror keeps
// the shared header and the worker implementations untouched.  The nulling
// default constructor and the no-op leak hook ride in the same mirror for the
// same reason: each folds onto an existing retail body by bytes alone.

typedef unsigned short wchar_t;

template <typename T>
class StringBase
{
public:
    void clear();
    void debugIgnoreLeaks();

private:
    StringBase();
    void releaseBuffer();
    void validate() const;
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
StringBase<T>::StringBase()
{
    m_data = 0;
}

template <typename T>
void StringBase<T>::clear()
{
    releaseBuffer();
}

template <typename T>
void StringBase<T>::debugIgnoreLeaks()
{
}

template <typename T>
void StringBase<T>::validate() const
{
}

template <typename T>
StringBase<T>::~StringBase()
{
    releaseBuffer();
}

template void StringBase<char>::clear();
template void StringBase<wchar_t>::clear();
template void StringBase<char>::debugIgnoreLeaks();
template void StringBase<wchar_t>::debugIgnoreLeaks();
template void StringBase<char>::validate() const;
template void StringBase<wchar_t>::validate() const;
template StringBase<char>::StringBase();
template StringBase<wchar_t>::StringBase();
template StringBase<char>::~StringBase();
template StringBase<wchar_t>::~StringBase();
