// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BfmeAptWindowManager's text-binding setters (retail 0x00225299, 104B, and
// bfmeSetText 0x00225301, 116B; rva00225375 follows in
// AptMapPreviewSetMapTitle.cpp). The manager keeps an AsciiString-keyed table
// at +0x48 (lookup 0x00224BDB, still unmatched) of bindings: a vector of text
// sinks and the current UnicodeString at +0x0C. Each setter updates the text,
// then pushes it to every sink through 0x00222CCB, which walks the vector
// calling the sinks' slot 1 with a by-value 0x00222719 temp and returns it.
// Target evidence: both bodies' retail call sites (lookup, push_back 0x004DFCB0,
// isEmpty 0x00035740, compare 0x00006A7A against UnicodeString::TheEmptyString,
// set 0x0000565D with the L" " literal, set 0x00037150, the 0x00222719 temp
// constructed in the outgoing argument slot, the returned temp released
// through 0x00036E70). Class and member names are address-derived or
// descriptive; the original spellings are unknown.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>

class Rva00222CCB;

class Rva00222719Temp
{
public:
	Rva00222719Temp(const UnicodeString &src);
private:
	UnicodeString m_str;
};

class Rva0022300F
{
public:
	std::vector<Rva00222CCB *> m_sinks;
	UnicodeString m_text;
};

class Rva00224BDBMap
{
public:
	Rva0022300F &rva00224BDB(const AsciiString &key);
};

// 0x00222CCB is rowed under its UnicodeString spelling in Rva00222CCBLeaf.cpp;
// its argument and result are the 0x00222719 temp (same 4-byte layout). The
// call names it by that type, and the linker resolves the spelling to the
// rowed body.
Rva00222719Temp Rva00222CCBBuild(Rva00222CCB **begin, Rva00222CCB **end, Rva00222719Temp text);
#pragma comment(linker, "/alternatename:?Rva00222CCBBuild@@YA?AVRva00222719Temp@@PAPAVRva00222CCB@@0V1@@Z=?Rva00222CCBBuild@@YA?AVUnicodeString@@PAPAVRva00222CCB@@0V1@@Z")

class BfmeAptWindowManager
{
public:
	void rva00225299(const AsciiString &key, const UnicodeString &text, Rva00222CCB *sink);
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder);
private:
	char m_pad[0x48];
	Rva00224BDBMap m_bindings;
};

void BfmeAptWindowManager::rva00225299(const AsciiString &key, const UnicodeString &text, Rva00222CCB *sink)
{
	if (sink)
	{
		Rva0022300F &binding = m_bindings.rva00224BDB(key);
		binding.m_sinks.push_back(sink);
		if (binding.m_text.isEmpty())
			binding.m_text.set(text);
		Rva00222CCBBuild(binding.m_sinks.begin(), binding.m_sinks.end(), Rva00222719Temp(binding.m_text));
	}
}

void BfmeAptWindowManager::bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder)
{
	Rva0022300F &binding = m_bindings.rva00224BDB(key);
	if (usePlaceholder && text.compare(UnicodeString::TheEmptyString) == 0)
		binding.m_text.set(L" ");
	else
		binding.m_text.set(text);
	Rva00222CCBBuild(binding.m_sinks.begin(), binding.m_sinks.end(), Rva00222719Temp(binding.m_text));
}
