// cl: /O1 /GX /DNDEBUG /MD
//
// ?Rva0033A167_ParseSoundRefList@INI@@SAXPAV1@PAX1PBX@Z, retail
// 0x0033A167..0x0033A1CE (103B), cdecl FieldParse proc (ret).
//
// For every token (getNextTokenOrNull 0x0002DEED, first token included) a
// one-pointer ref-counted audio handle is zeroed, filled by the pinned audio
// token parser Rva00339184 (const char * and handle *), appended to the
// vector at the store through the rowed push_back 0x0005A084 and released
// (rowed Release_Ref 0x00050ED3) after the next token is read.
//
// Evidence (target): the body is the twin of the rowed record-list parser
// 0x0033A1CE that follows it (INIRecordListParsers.cpp: same loop and EH
// shape over an {index and pointer} handle filled by 0x00339235) and of the
// Sound proc 0x0045D2F6 (InstantDeathBehaviorParsers.cpp: same parser
// 0x00339184 and push_back 0x0005A084 on the same 4-byte handle). No direct
// call or address reference to it exists in retail; the name stays
// address-derived.

#define NULL 0

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	static void Rva0033A167_ParseSoundRefList(INI *ini, void *instance, void *store, const void *userData);
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

// Same 4-byte element the rowed push_back 0x0005A084 is instantiated on.
struct Rva0005A084Element
{
	int a[1];
};

// One ref-counted pointer filled by the token parser, released on exit.
class Rva0033A167SoundRef
{
public:
	Rva0033A167SoundRef() : m_ref(NULL) {}
	~Rva0033A167SoundRef()
	{
		if (m_ref)
			m_ref->Release_Ref();
	}
	OpaqueRefCounted *m_ref;
};

void Rva00339184(const char *token, void *store);

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva0005A084Element, allocator<Rva0005A084Element> >
{
public:
	void push_back(const Rva0005A084Element &x);
private:
	Rva0005A084Element *m_start;
	Rva0005A084Element *m_finish;
	Rva0005A084Element *m_endOfStorage;
};
}

void INI::Rva0033A167_ParseSoundRefList(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextTokenOrNull();
	while (token)
	{
		Rva0033A167SoundRef sound;
		Rva00339184(token, &sound);
		((_STL::vector<Rva0005A084Element, _STL::allocator<Rva0005A084Element> > *)store)->push_back(*(const Rva0005A084Element *)&sound);
		token = ini->getNextTokenOrNull();
	}
}
