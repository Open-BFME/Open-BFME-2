// ?rva004D2164@Rva004D2164@@QAE_NGH@Z
// partial score=0.92 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva004D2164@Rva004D2164@@QAE_NGH@Z @0x004D2164 75B bitset check-and-set with global gate.
// Calls rowed rva004D1EB1 0x004D1EB1 ClearRange then rowed _Unchecked_test 0x001E37E8; sets bit manually.
// Evidence: caller 0x004D26D2 passes ID word at +0x10 and frame; same bitset<86> at +0x0 as sibling Rva004D1EB1ClearRange; global TheWritableGlobalData +0xD24 gate.
// No fallback paths.
#include <bitset>

class GlobalData
{
public:
	char m_pad[0xd24];
	unsigned char m_flagD24;
};
extern GlobalData *TheWritableGlobalData;

class Rva004D1EB1
{
public:
	void rva004D1EB1(unsigned short commandID);
};

class Rva004D2164
{
public:
	bool rva004D2164(unsigned short id, int frame);
private:
	_STL::bitset<45> m_bits;
};

// ?rva004D2164@Rva004D2164@@QAE_NGH@Z present-unmatched
bool Rva004D2164::rva004D2164(unsigned short id, int frame)
{
	unsigned int nid = id;
	if (TheWritableGlobalData->m_flagD24 == 0)
		return true;
	((Rva004D1EB1 *)this)->rva004D1EB1((unsigned short)nid);
	if (m_bits._Unchecked_test(nid))
		return false;
	m_bits._Unchecked_set(nid);
	return true;
}
