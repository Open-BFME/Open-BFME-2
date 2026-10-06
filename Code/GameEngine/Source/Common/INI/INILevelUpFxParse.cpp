// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// ?Rva00289C24Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x00289C24 (199B): the
// LevelUpFx FieldParse proc (row 0x00BFBB10). Expects the token "FX"
// (_strcmpi, else INIException "'fx' expected"), parses an FXList into a local
// {FXList, bone name} entry, takes an optional "BONE <name>" pair, and appends
// the entry to the vector at instance + 0x3C (rowed push_back 0x002898AC).
// Separators come from the INI's +0x420 field. Name address-derived.

#include "ascii_string.h"

#define NULL 0

class FXList;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	const char *separators() const { return m_separators; }
private:
	unsigned char m_unreconstructed_000[0x420];
	const char *m_separators;		// +0x420
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

struct Rva002898ACElement
{
	const FXList *m_fx;
	AsciiString m_bone;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva002898ACElement, allocator<Rva002898ACElement> >
{
public:
	void push_back(const Rva002898ACElement &x);
private:
	Rva002898ACElement *m_start;
	Rva002898ACElement *m_finish;
	Rva002898ACElement *m_endOfStorage;
};
}

struct Rva00289C24Owner
{
	unsigned char m_unreconstructed_00[0x3C];
	_STL::vector<Rva002898ACElement, _STL::allocator<Rva002898ACElement> > m_levelUpFX;	// +0x3C
};

// ?Rva00289C24Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00289C24Parse(INI *ini, void *instance, void *, const void *)
{
	Rva002898ACElement entry;
	const char *token = ini->getNextToken(ini->separators());
	if (_strcmpi(token, "FX") != 0)
		throw INIException(3, "'fx' expected");

	INI::parseFXList(ini, instance, &entry.m_fx, NULL);

	token = ini->getNextTokenOrNull(ini->separators());
	if (token && _strcmpi(token, "BONE") == 0)
		entry.m_bone.set(ini->getNextTokenOrNull(NULL));

	((Rva00289C24Owner *)instance)->m_levelUpFX.push_back(entry);
}
