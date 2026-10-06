// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// Object-record FieldParse proc (name address-derived):
//   0x003F341E 113B ConnectsTo (0x00C36640): for every token (separators
//       from the INI's +0x420 field) a LivingWorldRegionConnection (rowed
//       ctor 0x003F24F3 / virtual dtor 0x003F2517) takes the token as its
//       region name (+0x04) and is appended to the vector at the store
//       (rowed push_back 0x003F309A); it is destroyed after the next token
//       is read.

#include "ascii_string.h"

#define NULL 0

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	static void Rva003F341E_ParseConnections(INI *ini, void *instance, void *store, const void *userData);
	const char *separators() const { return m_separators; }
private:
	unsigned char m_unreconstructed_000[0x420];
	const char *m_separators;		// +0x420
};

class LivingWorldRegionConnection
{
public:
	LivingWorldRegionConnection();
	virtual ~LivingWorldRegionConnection();
	AsciiString m_regionName;		// +0x04
private:
	unsigned char m_unreconstructed_08[0x18 - 0x08];
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<LivingWorldRegionConnection, allocator<LivingWorldRegionConnection> >
{
public:
	void push_back(const LivingWorldRegionConnection &x);
private:
	LivingWorldRegionConnection *m_start;
	LivingWorldRegionConnection *m_finish;
	LivingWorldRegionConnection *m_endOfStorage;
};
}

// ?Rva003F341E_ParseConnections@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003F341E_ParseConnections(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextTokenOrNull(ini->separators());
	while (token)
	{
		LivingWorldRegionConnection connection;
		connection.m_regionName.set(token);
		((_STL::vector<LivingWorldRegionConnection, _STL::allocator<LivingWorldRegionConnection> > *)store)->push_back(connection);
		token = ini->getNextTokenOrNull(ini->separators());
	}
}
