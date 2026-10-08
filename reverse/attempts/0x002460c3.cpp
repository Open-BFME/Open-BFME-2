// ??A?$hash_map@VAsciiString@@W4BuildableStatus@@U?$hash@VAsciiString@@@rts@@U?$equal_to@VAsciiString@@@4@V?$allocator@U?$pair@$$CBVAsciiString@@W4BuildableStatus@@@_STL@@@_STL@@@_STL@@QAEAAW4BuildableStatus@@ABVAsciiString@@@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?setBuildableStatusOverride@GameLogic@@QAEXPBVThingTemplate@@W4BuildableStatus@@@Z
// Target evidence: retail 0x00246F71 is a 29-byte Ghidra function. Its body
// null-checks the first argument, passes ThingTemplate+0x64 as the key to the
// hash map at GameLogic+0x10, then writes the second argument through the
// returned value pointer. The operation's semantic identity is inferred from
// that behavior and the matching retail call relationships; the offsets below
// are target-specific structural evidence, not donor layout claims.

#include <hash_map>
#include "ascii_string.h"

typedef unsigned int size_t;


enum BuildableStatus
{
	BUILDABLE_STATUS_UNKNOWN = 0
};

namespace rts
{
	template <class T> struct hash
	{
		size_t operator()(const T &value) const;
	};

	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}

typedef _STL::pair<const AsciiString, BuildableStatus> BuildableStatusPair;
typedef _STL::hash_map<AsciiString, BuildableStatus, rts::hash<AsciiString>,
	rts::equal_to<AsciiString>, _STL::allocator<BuildableStatusPair> > BuildableMap;


class Rva00056F61;
struct Rva0041534BIter {
    void *m_node;
    Rva00056F61 *m_table;
    Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61 {
public:
    __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);
};
class Rva00242F1A { public: void *rva00242F1A(const void *); };
struct BuildableSlotPair {
    AsciiString name;
    BuildableStatus status;
    BuildableSlotPair(const AsciiString &n, BuildableStatus s) : name(n), status(s) {}
};
// Native 0x002460C3..0x0024613C: GameLogic's +0x10 override map returns
// node+8 or inserts the copied key and enum zero, then returns pair+4.
// The 0x41534B provider has a proven nonthrowing hash/compare-only chain.
template<>
BuildableStatus &BuildableMap::operator[](const AsciiString &name)
{
    void *node;
    {
        Rva0041534BIter found = ((Rva00056F61 *)this)->rva0041534B(&name);
        node = found.m_node;
    }
    return *(BuildableStatus *)(node == 0
        ? (char *)((Rva00242F1A *)this)->rva00242F1A(
            &static_cast<const BuildableSlotPair &>(BuildableSlotPair(name, BUILDABLE_STATUS_UNKNOWN))) + 4
        : (char *)node + 8);
}

class ThingTemplate; // +0x64 AsciiString key; NOT ThingTemplate::getName (kept +0x10 in ThingFactory.cpp), retail inlines +0x64

class GameLogic
{
	char m_unknown00[0x10];
	BuildableMap m_thingTemplateBuildableOverrides;

public:
	void setBuildableStatusOverride(const ThingTemplate *tt, BuildableStatus bs);
};

void GameLogic::setBuildableStatusOverride(const ThingTemplate *tt, BuildableStatus bs)
{
	if (tt)
		m_thingTemplateBuildableOverrides[*reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const char *>(tt) + 0x64)] = bs;
}
