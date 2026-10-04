// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z
// partial score=0.86 date=2026-10-04
// cl: /O2 /DNDEBUG /MD
// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z @0x006F1530 63B
//
// Apt predicate-to-bool: if the value is an XmlNode and its checked cast target
// carries a non-null inner at +0x20, publish (inner->slot9() != 0) through the
// MakeBool helper; otherwise publish false.
//
// Improvement over the previous banked body: retail's first call tests `al`
// (84 c0), so the predicate is declared to RETURN bool here -- an int return
// emits `test eax` (85 c0). The predicate's real definition is the matched
// ?isXmlNode@BfmeAptValue006DCD20@@QBEHXZ at 0x006DBDE0; a bool-returning TU
// view is ?isXmlNode@BfmeAptValue006DCD20@@QBE_NXZ, which needs a symbols.csv
// alias pin at 0x006DBDE0 before this body can resolve its first call.
//
// Remaining wall (unchanged): retail does NOT tail-call either MakeBool site
// (it emits push arg / call / add esp,4 / pop esi / ret at both 0x6F1559 and
// 0x6F1565), while /O2 in this toolchain tail-calls both (`pop esi; mov
// [esp+4],arg; jmp MakeBool`). `_ReadWriteBarrier()` after a call suppresses
// the tail call but makes MSVC merge the two sites into one shared call and
// epilogue (57B), which retail also does not do. No /O1 //O2 //Oy- //Ob1 or
// statement-order variant produced two separate non-tail calls.

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
	bool isXmlNode() const;
	BfmeAptValue006DCD20 *rva006DD220();

private:
	char m_pad[0x1C];

public:
	Rva006F1530Inner *m_inner20;	// +0x20
};

class AptValue;
AptValue *Rva006D88C0MakeBool(bool b);

// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z present-unmatched
void rva006F1530(BfmeAptValue006DCD20 *obj)
{
	if (obj->isXmlNode()) {
		Rva006F1530Inner *inner = obj->rva006DD220()->m_inner20;
		if (inner) {
			Rva006D88C0MakeBool(inner->slot9() != 0);
			return;
		}
	}
	Rva006D88C0MakeBool(false);
}
