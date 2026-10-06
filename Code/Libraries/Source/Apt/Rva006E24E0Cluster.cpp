// cl: /MD
//
// ?rva006E24E0@AptCIH@@QBE_NXZ, retail 0x006E24E0, 116 bytes.
// Target evidence: this+0x4C holds a field whose +0x24 pointer is tail-called
// at the pinned 0x006F7AC0 (the per-node walker that calls this predicate back
// on each +0x54 chain node); the sprite-base predicate at 0x006CFCD0 is tested
// once, then again inside the "isSpriteInstBase()" assert at AptCIH.h line
// 0x7D (file string 0x008E8C60, message 0x008E9A78); the else path ORs the
// rowed type predicates 0x006E0260 (12), 0x006E02B0 (15), 0x006E0300 (16) and
// 0x006DCC60 (14, argument 0). Same AptCIH layout as 0x6E0B80 in the near file;
// names are address-derived.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)

class BfmeAptValue006DCD20
{
public:
	int rva006E0260() const;
	int rva006E02B0() const;
	int rva006E0300() const;
	int rva006DCC60(bool) const;
};

class Rva006F7AC0
{
public:
	bool rva006F7AC0() const;
};

class Rva006E24E0Field4C
{
public:
	char m_pad[0x24];
	Rva006F7AC0 *m_24;
};

class AptCIH
{
public:
	virtual void vtableSlot0();
	bool rva006CFCD0() const;
	bool rva006E24E0() const;

private:
	unsigned char m_pad[0x48];
	Rva006E24E0Field4C *m_4C;
};

bool AptCIH::rva006E24E0() const
{
	const BfmeAptValue006DCD20 *self = (const BfmeAptValue006DCD20 *)this;
	if (rva006CFCD0()) {
		if (!rva006CFCD0()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		return m_4C->m_24->rva006F7AC0();
	}
	if ((unsigned char)self->rva006E0260()
		|| (unsigned char)self->rva006E02B0()
		|| (unsigned char)self->rva006E0300()
		|| (unsigned char)self->rva006DCC60(false))
		return true;
	return false;
}
