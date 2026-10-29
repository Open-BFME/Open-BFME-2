// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// The deleting destructors formerly scaffolded here are emitted by their
// destructor units (AttributeModifierAuraUpdate, ProductionUpdate and
// EmotionTrackerUpdate). Their rows live with those complete providers;
// partial local vtables would compete with the real class views.

#include "ascii_string.h"

// ?parse@Rva0049B8A0@@QAEXPAVINI@@PAX@Z @0x0049B8A0 234B
// Bitstring-list INI driver, same shape as the KindOf driver Rva00256499
// (System/Rva00256499Parse.cpp) and the ModelCondition twin Rva000B937E.
// The worker is the rowed 0x0049B750 single-token worker.
// The join-append is the shared Rva0049B6AE::append member (rowed, body
// ignores ecx); the string temporaries are the canonical AsciiString.
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

__forceinline const char *GetStr0049B8A0(const AsciiString &asciiString)
{
	char *stringData = *(char * *)(void *)&asciiString;
	return stringData ? stringData + 8 : "";
}

class Rva0049B750
{
public:
	bool rva0049B750(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0049B8A0 : public Rva0049B750
{
public:
	void parse(INI *ini, void *extra);
};

void Rva0049B8A0::parse(INI *ini, void *extra)
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
				const char *partText = GetStr0049B8A0(part);
				((Rva0049B6AE *)this)->append(partText, (StringBase<char> *)accum);
				if (!rva0049B750(partText, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!rva0049B750(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
