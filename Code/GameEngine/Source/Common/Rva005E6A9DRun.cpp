// cl: /MD
// ?run@Rva005E6A9DRun@@QAEXXZ @0x005E6A9D 59B
// Chain run called by step 0x005E6BA3: if the +0x1C holder is non-empty,
// compare its first word to the int helper on +0x08 and conditionally run
// the second helper, clear the holder, then forward +0x14 into the +0x04
// object at +0xC via rowed 0x005E3B25.
// Retail calls 0x005CB265 annotated as reverseAnimateWindow (Bool + arg);
// the site passes no arg and compares full eax, so call the rowed int
// no-arg twin ?rva005CB265@Rva005CB265@@UAEHXZ at the same address.
// Evidence: packet disasm; pins at 0x005E6A9D; rows 0x005CB265 0x005CB260
// 0x002BED91 0x005E3B25; precedent Rva005E21EB::rva005E25CD.
class Rva005CB265
{
public:
	virtual int rva005CB265();
};
class Rva005CB260
{
public:
	void rva005CB260();
};
struct Rva002BED91
{
	int m_ptr;
	void clear();
};
class Rva005E3B25
{
public:
	void rva005E3B25(int v);
};
struct Outer005E6A9D
{
	char m_pad[0xC];
	Rva005E3B25 m_C;
};
class Rva005E6A9DRun
{
public:
	void run();
private:
	char m_00[4];
	Outer005E6A9D *m_04;
	Rva005CB260 *m_08;
	char m_0C[8];
	int m_14;
	char m_18[4];
	Rva002BED91 m_1C;
};
void Rva005E6A9DRun::run()
{
	int cached = m_1C.m_ptr;
	if (cached)
	{
		if (((Rva005CB265 *)m_08)->Rva005CB265::rva005CB265() == cached)
			m_08->rva005CB260();
		m_1C.clear();
	}
	((Rva005E3B25 *)((char *)m_04 + 0xC))->rva005E3B25(m_14);
}
