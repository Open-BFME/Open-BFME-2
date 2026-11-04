// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva002C8754@Rva002C8754@@QAEXPAVINI@@PAX@Z @0x002C8754 234B.
// Multi-token INI bitstring-list driver over BitFlags104 worker 0x002C82C8.
// Direct transfer of the landed 234B sibling ?rva0033B84E@Rva0033AFBB in
// INI_VeterancyLevelListParse.cpp (same shape same callees same EH).
// Evidence: thiscall with this=worker flag set; INI arg flows as this into
// 0x0002DFE2 null-tolerant quoted-token reader; accumulator void star flows
// as the string arg of the join-append at 0x0049B6AE whose null-guard makes
// the 0x002C8C06 wrapper NULL pass legal; str m_data plus 8 or empty shape;
// EH prolog frame 0x00629188 over two string temporaries. The join-append
// is the rowed Rva0049B6AE::append member (both call sites set ecx edi
// before push call; its body ignores the receiver); the string temporaries
// are the canonical AsciiString.
#include "ascii_string.h"

#include "../../Include/Common/INI/INI.h"

class Rva002C82C8
{
public:
	bool rva002C82C8(const char *token, bool *foundNormal, bool *foundAddOrSub);
};

class Rva0049B6AE
{
public:
	void append(const char *s, StringBase<char> *b);
};

class Rva002C8754
{
public:
	void rva002C8754(INI *ini, void *extra);
};

void Rva002C8754::rva002C8754(INI *ini, void *accumVoid)
{
	AsciiString *accum = (AsciiString *)accumVoid;
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
				const char *s = part.str();
				((Rva0049B6AE *)this)->append(s, (StringBase<char> *)accum);
				if (!((Rva002C82C8 *)this)->rva002C82C8(s, &foundNormal, &foundAddOrSub))
					break;
			}
			wasQuoted = false;
		} else {
			((Rva0049B6AE *)this)->append(token, (StringBase<char> *)accum);
			if (!((Rva002C82C8 *)this)->rva002C82C8(token, &foundNormal, &foundAddOrSub))
				break;
		}
	}
}
