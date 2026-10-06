// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ??1Rva002A8BB9@@QAE@XZ @ 0x002A8BB9 (53B). Gap between erase 0x002A8B8C and
// clear 0x002A8BEE of RvaTreeEraseClearFamily.cpp; same flags plus shared
// ascii header first. Non-virtual dtor of an address-derived class with two
// AsciiStrings at +0/+4: destroys +4 via rowed releaseBuffer 0x00036410 then
// +0. Evidence: two releaseBuffer calls with EH states 0 then -1; callers
// at 0x002A9354 and unwind 0x0077587A.
#include "ascii_string.h"

class Rva002A8BB9
{
public:
	~Rva002A8BB9();
private:
	AsciiString m_0;
	AsciiString m_4;
};

Rva002A8BB9::~Rva002A8BB9()
{
}
