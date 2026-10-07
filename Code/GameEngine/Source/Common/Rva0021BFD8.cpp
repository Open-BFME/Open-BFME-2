// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
//
// ?rva0021BFD8@Rva0021BFD8@@QAE_NABV?$StringBase@D@@@Z @0x0021BFD8, 343B.
// CreateAHeroManager trailing three-string matcher: empty arg is false,
// else Build/operator/set/compareNoCase against +0x1c4/+0x1c8/+0x1cc.
// Target evidence: contiguous gap after GetSubClassAttributeDefaultValue
// 0x0021BFA6 (50B ends at 0x0021BFD8); three AsciiStrings at those offsets;
// callees all StringBase plus Rva000B6AF5Build and Rva000B6AA9Rec operator.
#define BFME_ASCII_KEEP_COPY_SET_BODY
#include "ascii_string.h"
#include "string_base.h"

struct Rva000B6AA9Rec
{
	operator AsciiString();

	AsciiString *m_string;
	int m_start;
	int m_len;
};

struct Rva000B6AF5Rec : public Rva000B6AA9Rec
{
};

Rva000B6AF5Rec *__cdecl Rva000B6AF5Build(Rva000B6AF5Rec *dest, void **srcpp, int val);

class Rva0021BFD8
{
public:
	bool rva0021BFD8(const StringBase<char> &arg);

private:
	char m_pad[0x1C4];
	AsciiString m_1c4; // +0x1C4
	AsciiString m_1c8; // +0x1C8
	AsciiString m_1cc; // +0x1CC
};

bool Rva0021BFD8::rva0021BFD8(const StringBase<char> &arg)
{
	if (arg.isEmpty())
		return false;
	AsciiString tmp;
	Rva000B6AF5Rec rec;
	tmp.set(*Rva000B6AF5Build(&rec, (void **)&arg, m_1c4.getLength()));
	if (tmp.compareNoCase(m_1c4) == 0)
		goto yes;
	tmp.set(*Rva000B6AF5Build(&rec, (void **)&arg, m_1c8.getLength()));
	if (tmp.compareNoCase(m_1c8) == 0)
		goto yes;
	tmp.set(*Rva000B6AF5Build(&rec, (void **)&arg, m_1cc.getLength()));
	if (tmp.compareNoCase(m_1cc) == 0)
		goto yes;
	return false;
yes:
	return true;
}
