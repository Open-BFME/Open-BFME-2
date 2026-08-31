// cl: /O1

// The shared, reference-counted buffer behind every StringBase. isEmpty tests a
// 16-bit field at offset 4 rather than the first character, so the length lives
// beside the refcount and the allocation size, not in the character data.
struct StringDataBase
{
    unsigned short m_refCount;
    unsigned short m_numCharsAllocated;
    unsigned short m_numChars;
};

template <class CHAR>
class StringBase
{
public:
    bool isEmpty() const;

protected:
    StringDataBase *m_data;
};

template <class CHAR>
bool StringBase<CHAR>::isEmpty() const
{
    return m_data == 0 || m_data->m_numChars == 0;
}

template class StringBase<char>;
