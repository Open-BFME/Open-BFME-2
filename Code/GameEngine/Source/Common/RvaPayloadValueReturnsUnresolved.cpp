// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Ghidra factory boundaries 5FAC2B/5FAC5D/5FAC8F are 50 bytes;
// clone boundaries 5FACC1/5FAD05/5FAD49 are 68 bytes.
// Existing constructors 5FAAA1/5FAB16/5FAB9E prove owners, allocation
// sizes 0x10/0x18/0x18, zero count +4 and payload +8. Native vtables
// C79EA8/C79EB4/C79EC4 place clones in slot 1. Each result stores one
// fresh object pointer and increments its count; its nontrivial value ABI
// naturally emits the otherwise unused local initialization flag.
// The three verified 30-byte payload constructors only write the vptr,
// zero the count and copy scalar words; their throw() contracts suppress
// unwarranted allocation cleanup while retaining the native value-result ABI.
// The result destructor is declared only; these six bodies do not call it.

#include "BattlePromptCallbackPayloadView.h"

namespace
{
extern "C" {
extern const void *const __identifier("??_7Rva005FAAA1@@6B@")[];
extern const void *const __identifier("??_7Rva005FAB16@@6B@")[];
extern const void *const __identifier("??_7Rva005FAB9E@@6B@")[];
}
inline const void *const *payloadCloneTable0() { return __identifier("??_7Rva005FAAA1@@6B@"); }
inline const void *const *payloadCloneTable1() { return __identifier("??_7Rva005FAB16@@6B@"); }
inline const void *const *payloadCloneTable2() { return __identifier("??_7Rva005FAB9E@@6B@"); }
}

class __declspec(novtable) Rva005FAAA1
{
public:
 struct Payload { int v[2]; };
 Rva005FAAA1(const Payload *src) throw();
 __forceinline Rva005FAAA1(const Rva005FAAA1 &rhs)
 {
  *(const void *const **)this = payloadCloneTable0();
  m_ref = 0;
  m_data = rhs.m_data;
 }
 virtual ~Rva005FAAA1();
 virtual RvaCloneResult<Rva005FAAA1> clone() const;
 int m_ref;
 Payload m_data;
};

class __declspec(novtable) Rva005FAB16
{
public:
 Rva005FAB16(const Payload005FAB16 &src) throw();
 __forceinline Rva005FAB16(const Rva005FAB16 &rhs)
 {
  *(const void *const **)this = payloadCloneTable1();
  m_ref = 0;
  m_data = rhs.m_data;
 }
 virtual ~Rva005FAB16();
 virtual RvaCloneResult<Rva005FAB16> clone() const;
 int m_ref;
 Payload005FAB16 m_data;
};

class __declspec(novtable) Rva005FAB9E
{
public:
 Rva005FAB9E(const Payload005FAB9E &src) throw();
 __forceinline Rva005FAB9E(const Rva005FAB9E &rhs)
 {
  *(const void *const **)this = payloadCloneTable2();
  m_ref = 0;
  m_data = rhs.m_data;
 }
 virtual ~Rva005FAB9E();
 virtual RvaCloneResult<Rva005FAB9E> clone() const;
 int m_ref;
 Payload005FAB9E m_data;
};

RvaCloneResult<Rva005FAAA1> Rva005FAAA1::clone() const
{
 return RvaCloneResult<Rva005FAAA1>(new Rva005FAAA1(*this));
}

RvaCloneResult<Rva005FAB16> Rva005FAB16::clone() const
{
 return RvaCloneResult<Rva005FAB16>(new Rva005FAB16(*this));
}

RvaCloneResult<Rva005FAB9E> Rva005FAB9E::clone() const
{
 return RvaCloneResult<Rva005FAB9E>(new Rva005FAB9E(*this));
}
