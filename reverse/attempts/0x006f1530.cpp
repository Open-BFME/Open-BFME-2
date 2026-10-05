// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z
// partial score=0.92 date=2026-10-05
// ?rva006F1530@@YAXPAVBfmeAptValue006DCD20@@@Z
// partial score=0.92 date=2026-10-05
// cl: /O2 /DNDEBUG /MD
// 0x006F1530 (63B) Apt predicate-to-bool: if the value is an XmlNode and its
// checked cast target carries a non-null inner at +0x20, publish
// (inner->slot9() != 0) through the MakeBool helper; otherwise publish false.
//
// Improvement over the prior banked body: binding the cast result to its own
// pointer (`p`) before reading m_inner20 reproduces retail's register
// allocation exactly -- inner in ecx, vtable in eax, `setne cl` -- which the
// single-expression form got wrong (inner in eax, vtable in edx). The body now
// matches retail byte-for-byte through 0x6F1557 (64B compiled vs 63B target).
//
// Remaining wall (unchanged): retail does NOT tail-call either MakeBool site;
// both end `push arg / call 0x6D88C0 / add esp,4 / pop esi / ret`, while /O2
// tail-calls both (`pop esi / mov [esp+4],arg / jmp 0x6D88C0`). /Oy- restores
// the two separate non-tail calls but adds an ebp frame retail never builds
// (67B). No /O1 //O2 //Ox /Oy- //Ob1 or pragma shape reaches two separate
// non-tail calls without the frame.
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

void rva006F1530(BfmeAptValue006DCD20 *obj)
{
	if (obj->isXmlNode()) {
		BfmeAptValue006DCD20 *p = obj->rva006DD220();
		Rva006F1530Inner *inner = p->m_inner20;
		if (inner) {
			Rva006D88C0MakeBool(inner->slot9() != 0);
			return;
		}
	}
	Rva006D88C0MakeBool(false);
}
