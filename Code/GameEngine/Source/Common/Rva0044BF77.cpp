// cl: /EHsc /MD
// ??0Rva0044BF77@@QAE@URva0051732ABase@@@Z @0x0044BF77 59B
// Ctor of the single-callback holder: forward the by-value ref holder at
// [ebp+8] as const ref to the rowed ctor-like 0x0044BEE6 (new impl plus AddRef,
// same shape as rowed 0x005173CB), then Release the input pointer via rowed
// fastcall 0x0007DEEF, return this. Model and flags mirror
// Code/GameEngine/Source/Common/Rva00517547Set.cpp. Caller 0x0044C0A8
// (MessageBoxOk): the call site builds the holder in the outer arg slot and
// pushes the by-value holder copy; target evidence is the ctor shape (the
// receiver slot is built first and the holder copied inline after it).
// Rva0051732ABase is the holder's by-value parameter view; this unit sees its
// dtor (the callee releases the argument), callers see it as a plain copy
// (their temp of the derived Rva0051732A owns the release).
#include "../../../Libraries/Source/Apt/AptRefTarget.h"

struct Rva0051732A;
struct Rva0051732ABase
{
	TargetRef00217D4C *m_ptr;
	~Rva0051732ABase() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

struct Rva0044BDA2
{
	void *m_vtbl;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva0044BDA2(const Rva0051732A &other);
};

struct Rva0044BEE6
{
	Rva0044BDA2 *m_ptr;
	Rva0044BEE6 *rva0044BEE6(const Rva0051732A &arg);
};

struct Rva0044BF77 : Rva0044BEE6
{
	Rva0044BF77(Rva0051732ABase arg);
};

Rva0044BF77::Rva0044BF77(Rva0051732ABase arg)
{
	rva0044BEE6(*(const Rva0051732A *)&arg);
}
