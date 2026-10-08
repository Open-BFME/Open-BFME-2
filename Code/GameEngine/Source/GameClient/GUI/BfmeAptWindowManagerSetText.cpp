// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BfmeAptWindowManager's text-binding setters (retail 0x00225299, 104B, and
// bfmeSetText 0x00225301, 116B; rva00225375 follows in
// AptMapPreviewSetMapTitle.cpp). The manager keeps an AsciiString-keyed table
// at +0x48 (lookup 0x00224BDB) of bindings: a vector of text
// sinks and the current UnicodeString at +0x0C. Each setter updates the text,
// then pushes it to every sink through 0x00222CCB, which walks the vector
// calling the sinks' slot 1 with a by-value 0x00222719 temp and returns it.
// Target evidence: both bodies' retail call sites (lookup, push_back 0x004DFCB0,
// isEmpty 0x00035740, compare 0x00006A7A against UnicodeString::TheEmptyString,
// set 0x0000565D with the L" " literal, set 0x00037150, the 0x00222719 temp
// constructed in the outgoing argument slot, the returned temp released
// through 0x00036E70). Class and member names are address-derived or
// descriptive; the original spellings are unknown.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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
	Rva0022300F();
	~Rva0022300F();
	std::vector<Rva00222CCB *> m_sinks;
	UnicodeString m_text;
};


// The constructor/copy/destructor providers prove a 16-byte binding: a
// three-pointer vector at +0 and a UnicodeString at +0xC. Pair ctor2233F0
// places its four-byte key before that binding; no shortened scratch layout.
class Rva0022304A {
public:
    Rva0022304A(const AsciiString &, const Rva0022300F &);
    ~Rva0022304A();
    AsciiString m_head;
    Rva0022300F m_item;
};
class Rva00056F61;
struct Rva0041534BIter {
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
    // Same proven hash/compare-only contract as the rowed iterator provider.
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
    Rva0022304A &rva002249ED(const Rva0022304A &);
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

// Native224BDB..224C76 RET4. The setters above identify the +48 name-keyed
// binding map. Native default construction2231E7, pair ctor2233F0, insertion
// 2249ED and both destructors establish the full conditional lifetimes.
Rva0022300F &Rva00224BDBMap::rva00224BDB(const AsciiString &key)
{
    void *node;
    {
        Rva0041534BIter found=((Rva00056F61 *)this)->rva0041534B(&key);
        node=found.m_node;
    }
    return node==0
        ? ((Rva00056F61 *)this)->rva002249ED(Rva0022304A(key,Rva0022300F())).m_item
        : *(Rva0022300F *)((char *)node+8);
}
