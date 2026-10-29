// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
//
// ?rva000BB4CE@W3DScriptedModelDraw@@QAEXPAVAsciiString@@H@Z, retail 0x000BB4CE
// (393 bytes, RET 8; WB twin 0x00949B30 by its "+Perm:%s"/"-Perm:%s" strings):
// clears the given string, then lists the 24-byte entries of the vector at
// +0x74 as "+Perm:name"/"-Perm:name" (the bool at +4 picks the sign) and those
// of the vector at +0x68 as "+name"/"-name", comma separated and broken onto a
// new line every perLine entries. Each branch formats and appends on its own
// (retail tail-merges them), as in the matched 0x00049BE8 flag description.
// Address-derived names; the entry layout is only what this body reads.
#include <vector>
#include "ascii_string.h"

struct Rva000BB4CEEntry
{
	AsciiString m_name;		// +0x00
	bool m_off;			// +0x04
	unsigned char m_pad05[0x18 - 5];
};

typedef _STL::vector<Rva000BB4CEEntry> Rva000BB4CEList;

class W3DScriptedModelDraw
{
public:
	void rva000BB4CE(AsciiString *out, int perLine);
private:
	unsigned char m_pad00[0x68];
	Rva000BB4CEList m_states;		// +0x68
	Rva000BB4CEList m_permanents;		// +0x74
};

void W3DScriptedModelDraw::rva000BB4CE(AsciiString *out, int perLine)
{
	int i;
	bool first;
	AsciiString entry;
	int n;
	int count;
	if (!out)
		return;
	out->clear();
	count = 0;
	first = true;
	const Rva000BB4CEList &perms = m_permanents;
	n = perms.size();
	for (i = 0; i < n; i++)
	{
		const Rva000BB4CEEntry &stateEntry = m_permanents[i];
		if (!first)
			reinterpret_cast<StringBase<char> *>(out)->concat(", ");
		if (count >= perLine)
		{
			count = 0;
			reinterpret_cast<StringBase<char> *>(out)->concat("\n");
		}
		if (stateEntry.m_off)
		{
			entry.format("-Perm:%s", stateEntry.m_name.str());
			out->concat(entry);
		}
		else
		{
			entry.format("+Perm:%s", stateEntry.m_name.str());
			out->concat(entry);
		}
		first = false;
		count++;
	}
	const Rva000BB4CEList &states = m_states;
	n = states.size();
	for (i = 0; i < n; i++)
	{
		const Rva000BB4CEEntry &stateEntry = m_states[i];
		if (!first)
			reinterpret_cast<StringBase<char> *>(out)->concat(", ");
		if (count >= perLine)
		{
			count = 0;
			reinterpret_cast<StringBase<char> *>(out)->concat("\n");
		}
		if (stateEntry.m_off)
		{
			entry.format("-%s", stateEntry.m_name.str());
			out->concat(entry);
		}
		else
		{
			entry.format("+%s", stateEntry.m_name.str());
			out->concat(entry);
		}
		first = false;
		count++;
	}
}
