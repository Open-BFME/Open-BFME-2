// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva003FB508@Rva003FB508@@QAEXPAVINI@@PAX@Z @0x003FB508 234B: VeterancyLevel-style bitstring-list INI driver for the rowed single-token worker 0x003FB3B8, same shape as the KindOf driver Rva00256499 (System/Rva00256499Parse.cpp) and the ModelCondition driver 0x000B937E: StringBase split plus join-append plus the worker per token.
// Target evidence: retail body matches the 234B driver family by masked n-gram (1.0); worker callee 0x003FB3B8 read at the REL32; the join-append 0x0049B6AE is the rowed Rva0049B6AE::append member (no pin); string temporaries are the canonical AsciiString. Class names are address-derived.
#include "ascii_string.h"

#include "../../../Include/Common/INI/INI.h"

__forceinline const char *GetStr003FB508(const AsciiString &asciiString)
{
	char *t = *(char * *)(void *)&asciiString;
	return t ? t + 8 : "";
}

class Rva003FB3B8
{
public:
	bool rva003FB3B8(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0049B6AE
{
public:
	void append(const char *s, StringBase<char> *b);
};

class Rva003FB508 : public Rva003FB3B8
{
public:
	void rva003FB508(INI *ini, void *extra);
};

void Rva003FB508::rva003FB508(INI *ini, void *extra)
{
	AsciiString *accum = (AsciiString *)extra;
	if (accum != 0)
		accum->clear();

	bool foundNormal = false;
	bool foundAddOrSub = false;
	bool wasQuoted = false;

	const char *token;
	while ((token = ini->rva0002DFE2(0, &wasQuoted)) != 0) {
		if (wasQuoted) {
			AsciiString tmp(token);
			AsciiString part;
			while (tmp.nextToken(&part, 0)) {
				const char *s = GetStr003FB508(part);
				((Rva0049B6AE *)this)->append(s, (StringBase<char> *)accum);
				if (!rva003FB3B8(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!rva003FB3B8(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
