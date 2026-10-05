// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva004D1EB1@Rva004D1EB1@@QAEXG@Z, retail 0x004D1EB1, 64 bytes.
// STL bitset version of the Gen00667F30ClearRange window: last = id+0x800A,
// first = id+0x7FF6, 20 iterations of (index % 0x10000) via _Unchecked_reset
// on bitset<86> at +0x0. Evidence: same constants as BFME1 donor
// Gen00667F30ClearRange.cpp; callee rowed 0x004D0F63; caller 0x004D217A.
#include <bitset>

class Rva004D1EB1
{
public:
	void rva004D1EB1(unsigned short commandID);

private:
	_STL::bitset<86> m_bits;
};

void Rva004D1EB1::rva004D1EB1(unsigned short commandID)
{
	int last = commandID + 0x800A;
	int first = commandID + 0x7FF6;
	if (first >= last)
		return;
	int index = first + 0x10000;
	int count = last - first;
	do {
		int normalized = index % 0x10000;
		m_bits._Unchecked_reset(normalized);
		++index;
		--count;
	} while (count != 0);
}
