// cl: /MD /EHsc
// Native 0x000F1B37 constructs the 12-byte entry; table 0x007CEFD4 holds
// deleting destructor 0x000F1B73 and Get_Key 0x0030F45F. The shared eight-byte
// HashableClass owns the zeroed link at +4, with the StringClass key at +8.
// Caller 0x000F1BEC adds this entry to the hash table; derived identity is unknown.
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"
#include "../../../Libraries/Source/WWVegas/WWLib/HashableClass.h"
inline StringClass::operator const char *() const { return m_Buffer; }
struct Rva000F1B8F : HashableClass {
    StringClass m_08;
    Rva000F1B8F(const char *s);
    virtual ~Rva000F1B8F();
    virtual const char *Get_Key() { return m_08; }
};
Rva000F1B8F::Rva000F1B8F(const char *s) : m_08(s, false)
{
}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
