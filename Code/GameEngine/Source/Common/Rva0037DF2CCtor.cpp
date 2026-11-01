// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
// ??0CarryoverUnit@@QAE@XZ @0x0037DF2C (97B).
// Ctor with vtable 0x00BDF158 at +0x0, AsciiString at +0x4 from TheEmptyString
// 0x00DE0878 via pinned StringBase copy 0x000365F0, float 0 at +0x8 via xorps
// plus movss, int 0 at +0xC, 0x80-byte block at +0x10 via inline helper ctor
// calling rowed clear80 0x001EAE6F, int 0 at +0x90, record at +0x94 via rowed
// zeroing ctor 0x004E04FD. The Snapshot base (inline ctor, inline virtual
// dtor) arms EH state 0 before the first member call; the dtor 0x0037DEE4
// shares this unit's EH handler 0x0077F0BE and restores Snapshot's vtable
// 0x00BBB554. The class is the CarryoverUnit.cpp TU's view.
// Callers at 0x001EC15F 0x001EC3FA 0x001EC491 0x001ECD05 0x0040C354.
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "unicode_string.h"

// The 0x18-byte record at +0x94 (UnitRevivalEntry holds the same record at
// +0xB0): its zeroing ctor 0x004E04FD and its out-of-line dtor 0x001EB05E
// are both rowed under Rva001EB15A.
class Rva001EB15A{public:Rva001EB15A();~Rva001EB15A();private:int m_00;int m_04;int m_08;UnicodeString m_wstr0C;AsciiString m_str10;unsigned char m_14;};

// The 0x80-byte block at +0x10; its inline ctor clears it through 0x001EAE6F.
class Rva001EAE6FHelper{public:Rva001EAE6FHelper(){clear80();}Rva001EAE6FHelper*clear80();private:char m_pad[0x80];};

class Xfer;

// Layout from the ctor 0x0037DF2C: name +0x04 (copied from TheEmptyString),
// float +0x08 (xorps/movss), int +0x0C, the cleared block +0x10, int +0x90,
// the record +0x94; the dtor 0x0037DEE4 tears down +0x94 then +0x04.
class CarryoverUnit:public Snapshot{public:CarryoverUnit();virtual ~CarryoverUnit();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);private:AsciiString name;float m_f08;int m_c0C;Rva001EAE6FHelper m_h10;int m_90;Rva001EB15A member;};

CarryoverUnit::CarryoverUnit() : name(AsciiString::TheEmptyString), m_f08(0.0f), m_c0C(0), m_90(0)
{
}
