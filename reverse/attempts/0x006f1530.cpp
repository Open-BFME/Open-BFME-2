// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z
// partial score=0.93 date=2026-10-05
// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z @0x006F1530 63B
// cl: /O2 /DNDEBUG /MD
//
// Apt predicate-to-bool conversion helper.  Calls the rowed isXmlNode()
// (0x006DBDE0) and, when its checked cast carries a non-null inner at +0x20,
// publishes (inner->slot9() != 0) through the rowed MakeBool pin (0x006D88C0);
// otherwise publishes false.
//
// isXmlNode is declared with the row's own `int QBEHXZ` signature so the call
// resolves; the `(unsigned char)` test reproduces retail's `test al,al`
// (84 c0) instead of an int test.  _ReadWriteBarrier after the first MakeBool
// keeps that call out of tail position, matching retail exactly.  This matches
// retail byte-for-byte through 0x006F1562 (the whole true path and its non-tail
// call epilogue); the sole remaining wall is the final MakeBool: MSVC
// tail-calls it, while retail emits a second `push 0 / call / add esp,4 /
// pop esi / ret`.  Adding a barrier there instead makes MSVC tail-merge the two
// call sites into one shared 55B body.  No flag (/O1 /Os /Ox /Ob0 /Ob1 /Oy-
// /Og-) or source shape reaches retail's two separate, non-merged, frameless
// call epilogues.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva006F1530Inner
{
public:
	virtual void *s0();
	virtual void *s1();
	virtual void *s2();
	virtual void *s3();
	virtual void *s4();
	virtual void *s5();
	virtual void *s6();
	virtual void *s7();
	virtual void *s8();
	virtual void *slot9();
};

class BfmeAptValue006DCD20
{
public:
	virtual void vtableSlot0();
	int isXmlNode() const;
	BfmeAptValue006DCD20 *rva006DD220();

private:
	char m_pad[0x1C];

public:
	Rva006F1530Inner *m_inner20;	// +0x20
};

class AptValue;
AptValue *Rva006D88C0MakeBool(bool b);

void rva006F1530(BfmeAptValue006DCD20 *obj)
{
	if ((unsigned char)obj->isXmlNode()) {
		BfmeAptValue006DCD20 *p = obj->rva006DD220();
		Rva006F1530Inner *inner = p->m_inner20;
		if (inner) {
			Rva006D88C0MakeBool(inner->slot9() != 0);
			_ReadWriteBarrier();
			return;
		}
	}
	Rva006D88C0MakeBool(false);
}
