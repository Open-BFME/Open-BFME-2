// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// Named-real list FieldParse procs (one shape; names address-derived): the
// first token is a name, the rest of the line a real parsed through
// INI::parseReal into a zeroed local (SSE); a {name, real} record is appended
// to the vector in the instance through the rowed push_back of its type.
//   0x00318242 122B TerrainObject (0x00C0C3E8): vector at +0x24
//       (push_back 0x00318203).
//   0x004C3F48 122B ElvenWoodObject (0x00C5D038): vector at +0x7C
//       (push_back 0x004C3F09).

#include "ascii_string.h"

typedef float Real;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00318242_ParseNamedReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004C3F48_ParseNamedReal(INI *ini, void *instance, void *store, const void *userData);
};

struct Rva00318203Element
{
	AsciiString m_name;
	Real m_value;
};

struct Rva004C3F09Element
{
	AsciiString m_name;
	Real m_value;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva00318203Element, allocator<Rva00318203Element> >
{
public:
	void push_back(const Rva00318203Element &x);
private:
	Rva00318203Element *m_start;
	Rva00318203Element *m_finish;
	Rva00318203Element *m_endOfStorage;
};
template <> class vector<Rva004C3F09Element, allocator<Rva004C3F09Element> >
{
public:
	void push_back(const Rva004C3F09Element &x);
private:
	Rva004C3F09Element *m_start;
	Rva004C3F09Element *m_finish;
	Rva004C3F09Element *m_endOfStorage;
};
}

struct Rva00318242Owner
{
	unsigned char m_unreconstructed_00[0x24];
	_STL::vector<Rva00318203Element, _STL::allocator<Rva00318203Element> > m_objects;	// +0x24
};

struct Rva004C3F48Owner
{
	unsigned char m_unreconstructed_00[0x7C];
	_STL::vector<Rva004C3F09Element, _STL::allocator<Rva004C3F09Element> > m_objects;	// +0x7C
};

// ?Rva00318242_ParseNamedReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00318242_ParseNamedReal(INI *ini, void *instance, void *, const void *userData)
{
	const char *name = ini->getNextToken();
	Real value = 0.0f;
	INI::parseReal(ini, instance, &value, userData);

	Rva00318203Element entry;
	entry.m_name.set(name);
	entry.m_value = value;
	((Rva00318242Owner *)instance)->m_objects.push_back(entry);
}

// ?Rva004C3F48_ParseNamedReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004C3F48_ParseNamedReal(INI *ini, void *instance, void *, const void *userData)
{
	const char *name = ini->getNextToken();
	Real value = 0.0f;
	INI::parseReal(ini, instance, &value, userData);

	Rva004C3F09Element entry;
	entry.m_name.set(name);
	entry.m_value = value;
	((Rva004C3F48Owner *)instance)->m_objects.push_back(entry);
}
