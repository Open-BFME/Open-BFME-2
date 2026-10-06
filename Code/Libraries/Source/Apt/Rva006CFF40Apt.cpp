// cl: /MD
// ?rva006CFF40@AptCIH@@QBEPAXXZ @0x006CFF40 48B
// AptCIH sprite-base accessor returning +0x4C with isSpriteInstBase assert at AptCIH.h:0x7D.
// Evidence: predicate pin ?rva006CFCD0@AptCIH@@QBE_NXZ at 0x006CFCD0; file/message strings
// at VA 0x00CE8C60/0x008E9A78; assert globals g_bfmeAptAssertAtE17734/g_bfmeAptBreakOnAssertAtDDC01C.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)

class AptCIH
{
public:
	virtual void vtableSlot0();
	void *rva006CFF40() const;
private:
	unsigned char m_pad[0x48];
	void *m_4C;
};

class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};

void *AptCIH::rva006CFF40() const
{
	if (!((const Rva006CFCD0 *)this)->isSpriteInstBase()) {
		g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	_ReadWriteBarrier();
	return m_4C;
}
