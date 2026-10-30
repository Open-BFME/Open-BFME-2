// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva00256499@Rva00256499@@QAEXPAVINI@@PAX@Z @0x00256499 234B: KindOf bitstring-list driver for worker 0x00255D58 via StringBase split plus join-append 0x0049B6AE.
// Target evidence: LINK BONUS 20B plus pin plus callers 0x002567F4 0x002C8C41 0x002C8C75, this=worker edi homing with mov ecx edi before both Append plus worker calls, INI rva0002DFE2 0x0002DFE2 null-tolerant quoted reader, StringBase ctor 0x00037BA0 plus nextToken 0x00036D90 plus releaseBuffer 0x00036410, worker 0x00255D58, Append 0x0049B6AE, empty fallback g_Rva0107301CEmptyString, __EH_prolog frame; donor is INI_VeterancyLevelListParse.cpp 0x0033B84E 234B same shape: member Append homing (now the rowed Rva0049B6AE::append) and quoted-arm wasQuoted reclear; string temporaries are the canonical AsciiString.
#include "ascii_string.h"

class INI
{
public:
	const char *rva0002DFE2(const char *seps, bool *substituted);
};

class Rva0049B6AE
{
public:
	void append(const char *s, StringBase<char> *b);
};

__forceinline const char *GetStr00256499(const AsciiString &asciiString)
{
	char *text = *(char * *)(void *)&asciiString;
	return text ? text + 8 : "";
}

class Rva00255D58
{
public:
	bool rva00255D58(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva00256499 : public Rva00255D58
{
public:
	void rva00256499(INI *ini, void *extra);
};

void Rva00256499::rva00256499(INI *ini, void *extra)
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
				const char *partText = GetStr00256499(part);
				((Rva0049B6AE *)this)->append(partText, (StringBase<char> *)accum);
				if (!rva00255D58(partText, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!rva00255D58(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
