// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ??1Rva003371B1@@QAE@XZ @ 0x003372B7 (53B): non-virtual dtor of 20-byte record with AsciiString at +0 and vector at +8 via rowed 0x003321D8 and releaseBuffer 0x00036410. Evidence: pin ??1Rva003371B1, prev copy 0x003371B1 layout, _Destroy caller 0x003376DA and Insert callers.
#include "ascii_string.h"

struct Rva003321D8
{
	~Rva003321D8();
private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva003371B1
{
public:
	~Rva003371B1();
private:
	AsciiString m_str;
	unsigned char m_flag;
	unsigned char m_pad[3];
	Rva003321D8 m_vec;
};

Rva003371B1::~Rva003371B1()
{
}
