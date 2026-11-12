// cl: /MD /EHsc
// ??0Rva000F1B8F@@QAE@PBD@Z 0x000F1B37 60B ctor vtable g_00BCEFD4 plus m_04 zero plus String m_08 from arg plus false; caller 0x000F1BEC new 0xC plus Add
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"
struct Rva000F1B8FBase {
    int m_04;
    Rva000F1B8FBase() : m_04(0) {}
    virtual ~Rva000F1B8FBase() {}
    // Retail table 0x00BCEF94: 1 __purecall entry follows.
    virtual void slot1() = 0;
};
struct Rva000F1B8F : Rva000F1B8FBase {
    StringClass m_08;
    Rva000F1B8F(const char *s);
    virtual ~Rva000F1B8F();
};
Rva000F1B8F::Rva000F1B8F(const char *s) : m_08(s, false)
{
}

// Inline public teardown calls Free_String directly; the standalone destructor is 0x00065F5B.
