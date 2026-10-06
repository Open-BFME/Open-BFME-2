// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva0059E3FA@@UAE@XZ @0x0059E3FA 60B: virtual dtor with vector plus string.
// Vtable 0x00870FC8, vector<AsciiString> at +4 via rowed vector dtor 0x0002CC70,
// AsciiString at +0x10 via rowed releaseBuffer 0x00036410, EH states for two members.
// Evidence: retail vtable store plus and-state-0 plus lea-call pair plus or-ffffffff
// plus second lea-call, neighbours Rva0059E2FD plus siblings, caller 0x0059E3DE.
#include <vector>
#include "ascii_string.h"

class Rva0059E3FA
{
public:
	virtual ~Rva0059E3FA();
private:
	_STL::vector<AsciiString> m_vec04;
	AsciiString m_str10;
};

Rva0059E3FA::~Rva0059E3FA()
{
}

// ??1Rva0059E4D5@@UAE@XZ @0x0059E4D5 60B: same vector-plus-string dtor shape as
// 0x0059E3FA with vtable 0x0087102C. Evidence: identical retail vtable store
// plus releaseBuffer plus vector-dtor EH sequence, neighbours Rva0059E436Parse
// plus Rva0059E511Parse same page, caller 0x0059E4BC.
class Rva0059E4D5
{
public:
	virtual ~Rva0059E4D5();
private:
	_STL::vector<AsciiString> m_vec04;
	AsciiString m_str10;
};

Rva0059E4D5::~Rva0059E4D5()
{
}
