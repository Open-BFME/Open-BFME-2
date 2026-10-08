// flags: region default (reverse/retail_inventory/flag_regions.csv)

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

// Clean BF1 9cbfb551fe System/SaveGame/GameStateRealMapPathToPortableMapPathThunk.cpp
// stringLength supplies null-safe length semantics. Native052C4..052D2 follows
// the rowed RGB-color debug body's RET052C3, tests the cdecl pointer, returns
// full EAX0 for null and otherwise tail-calls the actual strlen import thunk
// at629170 (IAT BBA6D4). Original helper/template name and return signedness
// remain unknown; this address-named unsigned view preserves the result bits.
#include <string.h>
unsigned int Rva000052C4LengthOrZero(const char *text)
{
    return text ? (unsigned int)strlen(text) : 0u;
}
