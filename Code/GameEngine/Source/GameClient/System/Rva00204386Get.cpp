// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <hash_map>
// ?Rva00204386Get@@YGPAVParticleSystemTemplate@@PBD@Z @0x00204386 111B
// slot 1 of vtable 0x00BE39F4 (RVA 0x007E39F4) but body uses no this: free __stdcall
// clone helper like Rva002043F5Get plus new(0xD4) and FXParticleSystem copy ctor.
// Evidence: StringBase PBD 0x00037BA0, TheParticleSystemManager 0x009FDD04,
// findTemplate 0x001F90DA, releaseBuffer 0x00036410, new 0x0002FDA0,
// ParticleSystemTemplate copy ctor 0x001FCE6B, EH prolog 0x00629188, ret 4.
#include "ascii_string.h"

class ParticleSystemTemplate;

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
};

extern ParticleSystemManager *TheParticleSystemManager;

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	ParticleSystemTemplate(const ParticleSystemTemplate &other);

private:
	char m_pad[0xD4];
};

}

ParticleSystemTemplate * __stdcall Rva00204386Get(const char *name)
{
	ParticleSystemTemplate *found;
	{
		AsciiString tmp(name);
		found = TheParticleSystemManager->findTemplate(tmp);
	}
	if (!found)
		return 0;
	return (ParticleSystemTemplate *)new FXParticleSystem::ParticleSystemTemplate(*(FXParticleSystem::ParticleSystemTemplate *)found);
}

// ?Rva002082F1Enumerate@@YGXPAVRva002082F1Visitor@@@Z @0x002082F1 82B
// slot 4 of the same vtable 0x00BE39F4, again with no use of this (free
// __stdcall, ret 4): walks TheParticleSystemManager's +0x88 name table
// (rowed cursor begin 0x00427195 / next 0x00411084) and hands each
// template's name (the node's +4 key string) to the visitor's slot 0.
struct AudioCacheCursor
{
	struct { void *first, *second; } s;
	AudioCacheCursor(void *a, void *b);
	AudioCacheCursor(const AudioCacheCursor &v);
};
class Rva000427195 { public: AudioCacheCursor rva00427195(); };
class Rva000411084 { public: void *next(); };
class Rva002082F1Visitor { public: virtual void visit(const char *name); };
struct Rva002082F1Node
{
	void *m_next;
	AsciiString m_name;	// +4
};

void __stdcall Rva002082F1Enumerate(Rva002082F1Visitor *visitor)
{
	AudioCacheCursor it = ((Rva000427195 *)((char *)TheParticleSystemManager + 0x88))->rva00427195();
	while (it.s.first)
	{
		visitor->visit(((Rva002082F1Node *)it.s.first)->m_name.str());
		((Rva000411084 *)&it)->next();
	}
}

// ?Rva00206DA4Enumerate@@YGXPAVRva002082F1Visitor@@@Z @0x00206DA4 91B
// slot 3 of 0x00BE39F4 (free __stdcall, ret 4): the same walk over
// TheFXListStore's +0xC table through the GameWindow-keyed STLport iterator
// spelling the rows use (begin 0x00427195, prefix ++ 0x0041E832; the
// postfix increment is inline), visiting each entry's (+8) name at +0xC.
class GameWindow; class WindowVideo;
class WindowVideoManager { public: struct hashConstGameWindowPtr { size_t operator()(const GameWindow *) const; }; };
typedef _STL::pair<const GameWindow * const, WindowVideo *> Rva00206DA4Pair;
typedef _STL::hashtable<Rva00206DA4Pair, const GameWindow *, WindowVideoManager::hashConstGameWindowPtr, _STL::_Select1st<Rva00206DA4Pair>, _STL::equal_to<const GameWindow *>, _STL::allocator<Rva00206DA4Pair> > Rva00206DA4Table;
namespace _STL {
template <> Rva00206DA4Table::iterator Rva00206DA4Table::begin();
template <> Rva00206DA4Table::iterator &Rva00206DA4Table::iterator::operator++();
}
class FXListStore;
extern FXListStore *TheFXListStore;
struct Rva00206DA4Entry
{
	unsigned char m_pad00[0x0C];
	AsciiString m_name;	// +0x0C
};

void __stdcall Rva00206DA4Enumerate(Rva002082F1Visitor *visitor)
{
	for (Rva00206DA4Table::iterator it = ((Rva00206DA4Table *)((char *)TheFXListStore + 0x0C))->begin(); it._M_cur; ++it)
	{
		Rva00206DA4Table::iterator cur = it;
		visitor->visit(((Rva00206DA4Entry *)(*cur).second)->m_name.str());
	}
}
