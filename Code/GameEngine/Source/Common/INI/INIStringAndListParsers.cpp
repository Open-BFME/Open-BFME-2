// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD
//
// Two FieldParse procs whose bodies are generic but which sit in their own
// units (names address-derived):
//   0x003EEABF 60B RegionObject (0x00DC14C8, store +0x1C): assigns the next
//       AsciiString to the store -- the same body as INI::parseAsciiString
//       (rowed 0x0002F11E) in another unit, the temporary released under EH.
//   0x00289228 61B Scalars (0x00BFB820): empties the float vector at the store
//       (erase(begin, end), the 4-byte-element fold 0x0031BD55) and appends
//       every remaining token through scanReal (push_back fold 0x004DFCB0).

#include "ascii_string.h"

#define NULL 0

typedef float Real;

class INI
{
public:
	AsciiString getNextAsciiString();
	const char *getNextTokenOrNull(const char *seps = 0);
	Real scanReal(const char *token);
	static void Rva003EEABF_ParseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva00289228_ParseRealList(INI *ini, void *instance, void *store, const void *userData);
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Real, allocator<Real> >
{
public:
	Real *begin() { return m_start; }
	Real *end() { return m_finish; }
	Real *erase(Real *first, Real *last);
	void push_back(const Real &x);
private:
	Real *m_start;
	Real *m_finish;
	Real *m_endOfStorage;
};
}

typedef _STL::vector<Real, _STL::allocator<Real> > RealVector;

// ?Rva003EEABF_ParseAsciiString@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003EEABF_ParseAsciiString(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	AsciiString *asciiString = (AsciiString *)store;
	*asciiString = ini->getNextAsciiString();
}

// ?Rva00289228_ParseRealList@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00289228_ParseRealList(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	RealVector *values = (RealVector *)store;
	values->erase(values->begin(), values->end());

	const char *token;
	while ((token = ini->getNextTokenOrNull()) != NULL)
	{
		Real value = ini->scanReal(token);
		values->push_back(value);
	}
}
