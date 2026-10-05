// ?rva003B7647@Rva003B56A5@@QAEXXZ
// partial score=0.8 date=2026-10-05
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003B7647@Rva003B56A5@@QAEXXZ @0x003B7647 36B: reset via swap with a
// fresh temp: constructs a 0x20-byte Rva003B761E temp through rowed
// 0x003B761E, swaps it with this through rowed Rva003B56A5::swap at
// 0x003B56A5, then runs the pinned 0x003B7167 temp cleanup. Evidence: temp
// address flows to all three calls, no member access on this, plain frame
// (no EH: the temp is opaque-trivial here, real vector layout lives in
// ScriptListSubrecordCtor.cpp).
#include <new>

class Rva003B56A5
{
public:
	void swap(Rva003B56A5 *other);
	void rva003B7647(void);

private:
	char m_opaque[0x20];
};

class Rva003B761E : public Rva003B56A5
{
public:
	Rva003B761E();
	void rva003B7167();
};

void Rva003B56A5::rva003B7647(void)
{
	Rva003B761E tmp;
	tmp.swap(this);
	tmp.rva003B7167();
}
