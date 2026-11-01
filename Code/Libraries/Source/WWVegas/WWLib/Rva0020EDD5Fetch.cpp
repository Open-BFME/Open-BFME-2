// cl: /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EDD5@Rva0020EDD5@@QAE?AVUnicodeString@@H@Z @0x0020EDD5 84B
// Honest-address __thiscall returning UnicodeString selected by int index:
// switch 1/2/3 fetches Ascii labels at *(this+8)+8/+4/+12 via TheGameText
// slot 0x38 else returns UnicodeString::TheEmptyString via rowed wide copy
// 0x00037050. Evidence: retail dec-je-dec-je-dec-je chain for 1-2-3,
// TheGameText VA 0x009FF0BC, empty VA 0x00A0C898, caller 0x003F03C9 forwards
// hidden plus [ecx+0x5c] selector, sibling Rva0020E89CFetch.cpp model.
typedef unsigned short wchar_t;
typedef bool Bool;

#include "ascii_string.h"


#include "unicode_string.h"

#include "../../../../GameEngine/Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

struct LabelBlock
{
	char m_pad[4];
	AsciiString m_a4;
	AsciiString m_a8;
	AsciiString m_ac;
};

class Rva0020EDD5
{
public:
	UnicodeString rva0020EDD5(int index);
private:
	char m_pad[8];
	LabelBlock *m_block;
};

UnicodeString Rva0020EDD5::rva0020EDD5(int index)
{
	switch (index) {
	case 1:
		return TheGameText->fetch(m_block->m_a8);
	case 2:
		return TheGameText->fetch(m_block->m_a4);
	case 3:
		return TheGameText->fetch(m_block->m_ac);
	default:
		return UnicodeString::TheEmptyString;
	}
}
