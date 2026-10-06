// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva004072D2@Rva004072D2@@QAE_NH@Z @0x004072D2 90B: thiscall bool clearing 12B hero element at this+0x80[index] when index<15 via rowed operator= then returning true else false. Evidence: imul 0xC lea ecx array operator= 0x406E22 releaseBuffer 0x36410 ret 4; caller 0x005B45BB; prev StringRecordCopy EHsc.
#include "ascii_string.h"
struct BfmeHeroElement005C39DE
{
	AsciiString text;
	unsigned int word4;
	unsigned int word8;
	BfmeHeroElement005C39DE();
	BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &o);
};
inline BfmeHeroElement005C39DE::BfmeHeroElement005C39DE() : text(), word4(0), word8(0) {}
class Rva004072D2
{
	char m_pad[0x80];
	BfmeHeroElement005C39DE m_arr[15];
public:
	bool rva004072D2(int index);
};
bool Rva004072D2::rva004072D2(int index)
{
	BfmeHeroElement005C39DE empty;
	if ((unsigned int)index >= 15)
		return false;
	m_arr[index] = empty;
	return true;
}
