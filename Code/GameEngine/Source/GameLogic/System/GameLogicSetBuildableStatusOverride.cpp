// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
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

typedef unsigned int size_t;

class AsciiString
{
	unsigned int m_first;
	unsigned int m_second;
};

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
