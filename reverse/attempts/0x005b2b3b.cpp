// ?rva005B2B3B@Rva005B2B3BOwner@@QBEPAV?$StringBase@D@@AAV2@@Z
// partial score=0.5 date=2026-10-08
// cl: /MD /Ireference/shims/bfme2_ascii
// ?rva005B2B3B@Rva005B2B3BOwner@@QBEPAV?$StringBase@D@@AAV2@@Z @0x005B2B3B 50B: thiscall, one
// reference argument, ret 4. Copies the owner's string at +0x240 into the
// argument, or the shared empty string when the owner's string is none; returns
// the argument. Owner and the chosen-string meaning are address-derived views.
#include "string_base.h"

extern StringBase<char> TheEmptyString;

class Rva005B2B3BOwner
{
public:
	StringBase<char> *rva005B2B3B(StringBase<char> &out) const;
private:
	char pad00[0x240];
	StringBase<char> m_240;
};

StringBase<char> *Rva005B2B3BOwner::rva005B2B3B(StringBase<char> &out) const
{
	const StringBase<char> *src = m_240.isNone() ? &TheEmptyString : &m_240;
	out.StringBase<char>::StringBase(*src);
	return &out;
}
