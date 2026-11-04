#pragma once
// Target-owned ABI view: slot ordering and accessed prefix are proven; original
// source class names, abstractness and complete layouts are not recovered.
// Windows names this type once <windows.h> is included ahead of this header.
#ifndef _WINBASE_
struct CRITICAL_SECTION { unsigned char data[24]; };
#endif

class Rva0040EDB
{
public:
 virtual bool lock(int time) throw();
 virtual bool unlock();
 virtual ~Rva0040EDB();
 // ?Rva0040EDB::Rva0040EDB present-unmatched
 __forceinline Rva0040EDB() : m_handle04(0) {}
 void *m_handle04;
};
// Retail's no-argument slot points directly to the real game __purecall.
// It reads no incoming this/arguments, returns EAX0 and uses plain RET;
// this binding models that exact callable ABI, not historical abstractness.
#pragma comment(linker, "/alternatename:?unlock@Rva0040EDB@@UAE_NXZ=__purecall")
class Rva00041004 : public Rva0040EDB
{
public:
 virtual bool lock(int time) throw();
 virtual bool unlock();
 virtual ~Rva00041004();
 Rva00041004(int x);
 CRITICAL_SECTION m_cs;
 unsigned char m_flag;
};

// Observed descendant table BC93A0 keeps the base wait method and selects the
// already verified 3B true predicate at 50B5C6. This is a byte-identical slot
// binding; original owner identity and historical folding are unknown.
class Rva00514E6B : public Rva0040EDB
{
public:
    virtual bool unlock();
    virtual ~Rva00514E6B();
};
#pragma comment(linker, "/alternatename:?unlock@Rva00514E6B@@UAE_NXZ=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
