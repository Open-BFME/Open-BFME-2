// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// Record-list FieldParse procs (names address-derived) appending a local
// record to the vector at the store through the rowed push_back of the
// record type:
//   0x0033A1CE 108B UnitSpecificSound (0x00C15608 +2): for every token an
//       audio handle {index -1, ref-counted pointer} (ctor ICF-folded at
//       0x004CEE6E, pinned for this type) is filled by the pinned token parser
//       0x00339235, appended (push_back 0x00339F70) and released after the
//       next token is read.
//   0x0039A4FC 105B PreBuiltList (0x00C1ABE0): name + count record; the name
//       is set from the first token and the record appended (push_back
//       0x0039A48E) only when a count follows.

#include "ascii_string.h"

#define NULL 0

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanInt(const char *token);
	static void Rva0033A1CE_ParseSoundList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0039A4FC_ParseNameCountList(INI *ini, void *instance, void *store, const void *userData);
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva002390CB
{
public:
	Rva002390CB();
	~Rva002390CB()
	{
		if (m_ref)
			m_ref->Release_Ref();
	}
	int m_index;
	OpaqueRefCounted *m_ref;
};

struct Rva0039A48EElement
{
	AsciiString m_name;
	int m_count;
};

void Rva00339235(const char *token, void *store);

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva002390CB, allocator<Rva002390CB> >
{
public:
	void push_back(const Rva002390CB &x);
private:
	Rva002390CB *m_start;
	Rva002390CB *m_finish;
	Rva002390CB *m_endOfStorage;
};
template <> class vector<Rva0039A48EElement, allocator<Rva0039A48EElement> >
{
public:
	void push_back(const Rva0039A48EElement &x);
private:
	Rva0039A48EElement *m_start;
	Rva0039A48EElement *m_finish;
	Rva0039A48EElement *m_endOfStorage;
};
}

// ?Rva0033A1CE_ParseSoundList@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0033A1CE_ParseSoundList(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextTokenOrNull();
	while (token)
	{
		Rva002390CB sound;
		Rva00339235(token, &sound);
		((_STL::vector<Rva002390CB, _STL::allocator<Rva002390CB> > *)store)->push_back(sound);
		token = ini->getNextTokenOrNull();
	}
}

// ?Rva0039A4FC_ParseNameCountList@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva0039A4FC_ParseNameCountList(INI *ini, void *, void *store, const void *)
{
	Rva0039A48EElement entry;
	const char *token = ini->getNextToken();
	if (token == NULL)
		return;
	entry.m_name.set(token);
	token = ini->getNextTokenOrNull();
	if (token == NULL)
		return;
	entry.m_count = ini->scanInt(token);
	((_STL::vector<Rva0039A48EElement, _STL::allocator<Rva0039A48EElement> > *)store)->push_back(entry);
}
