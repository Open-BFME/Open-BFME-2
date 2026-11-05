// cl: /EHsc /DNDEBUG /DWIN32 /MD
// ?rva006C3840@Rva006C1F60@@QAEXHH@Z @ 0x006C3840 (138B).
// Lock-guarded two-field setter of the Rva006C1F60 family (same +0x4E4 lock
// and +0x530/+0x540/+0x544/+0x554 layout as the recovered 0x006C1EB0 setter in
// Rva006C1F60.cpp). Retail holds the +0x4E4 critical-section lock through a
// local RAII guard, and when +0x540 changes calls the unrowed method
// 0x006C33D0(0, 0) before storing the new pair. The compiler-generated SEH
// frame (handler 0x00BA7D58, try levels 0 then -1) is the guard's destructor
// unwind, so the guard is a local object, not a bare pointer. 0x006C33D0 is
// address-derived and pinned; identity of the setter is not proven.
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

// The counted critical-section guard; Rva00034C90Finish.cpp supplies retail's
// out-of-line destructor (0x000317C0) under this name.
class Rva00034C90Lock
{
public:
	Rva00034C90Lock(Rva00030DD0Lock *lock) : m_lock(lock)
	{
		if (m_lock != 0)
			Rva00030DD0AddRef(m_lock);
	}
	~Rva00034C90Lock()
	{
		if (m_lock != 0)
			Rva00030DF0Release(m_lock);
	}

private:
	Rva00030DD0Lock *m_lock;
};

#include "../../Include/Common/Rva006C1F60.h"

void Rva006C1F60::rva006C3840(int arg1, int arg2)
{
	Rva00034C90Lock guard(m_pLock);
	if (m_540 != arg1) {
		rva006C33D0(0, 0);
		m_540 = arg1;
		m_544 = arg2;
	}
}
