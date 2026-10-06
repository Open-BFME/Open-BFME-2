// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva004D9B18@@QAE@ABEI@Z @0x004D9B18 (51B):
// Derived of rowed Rva004D9A8B base: base ctor via 0x004D9A8B with unsigned,
// +4 zero, +8 byte from src, then 0x38-block head init 0,0,self,self.
// Evidence: chain lane, call 0x004D9A8B just landed, 4x reload shape,
// caller 0x004DA338, unblocks 0x004DA329.
#include <deque>

class Rva004D9A8B
{
public:
	Rva004D9A8B(unsigned dummy);
protected:
	unsigned m_ptrVal;
};

class Rva004D9B18 : public Rva004D9A8B
{
public:
	Rva004D9B18(const unsigned char &srcByte, unsigned dummy);
private:
	int m_4;
	unsigned char m_8;
};

Rva004D9B18::Rva004D9B18(const unsigned char &srcByte, unsigned dummy) : Rva004D9A8B(dummy)
{
	m_4 = 0;
	m_8 = srcByte;
	((char *)m_ptrVal)[0] = 0;
	*(int *)((char *)m_ptrVal + 4) = 0;
	*(char **)((char *)m_ptrVal + 8) = (char *)m_ptrVal;
	*(char **)((char *)m_ptrVal + 12) = (char *)m_ptrVal;
}
