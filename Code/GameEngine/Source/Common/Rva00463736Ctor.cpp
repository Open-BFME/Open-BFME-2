// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00463736@@QAE@ABEI@Z @0x00463736 (42B):
// Derived of rowed Rva00463469 base: base ctor via 0x00463469 with unsigned
// dummy plus +4 zero then 0x60-block head init 0 0 self self.
// Evidence: chain lane call 0x00463469 just landed 4x reload shape caller
// 0x00463D68 unblocks 0x00463D59; LINK BONUS 468B via 0x00463D59; same shape
// as Rva004D9B18 0x004D9B18 (51B with srcByte) minus m_8 store = 42B.
#include <deque>

class Rva00463469
{
public:
	Rva00463469(unsigned dummy);
protected:
	unsigned m_ptrVal;
};

class Rva00463736 : public Rva00463469
{
public:
	Rva00463736(const unsigned char &srcByte, unsigned dummy);
private:
	int m_4;
};

Rva00463736::Rva00463736(const unsigned char &srcByte, unsigned dummy) : Rva00463469(dummy)
{
	(void)srcByte;
	m_4 = 0;
	((char *)m_ptrVal)[0] = 0;
	*(int *)((char *)m_ptrVal + 4) = 0;
	*(char **)((char *)m_ptrVal + 8) = (char *)m_ptrVal;
	*(char **)((char *)m_ptrVal + 12) = (char *)m_ptrVal;
}
