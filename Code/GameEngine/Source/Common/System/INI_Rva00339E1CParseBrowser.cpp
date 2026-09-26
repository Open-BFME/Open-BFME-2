// cl: /O1 /DNDEBUG /MD /GX-
// Rva00339E1C_ParseBrowser (retail 0x00339E1C, 100 bytes). Clears the
// ScienceType vector, then reads an OrNull token list: "None" clears and
// stops, anything else resolves through the rowed INI::scanIndexList at
// 0x002BD39 against the token's userData table into a stack temp pushed
// through the rowed vector push_back at 0x002E01C6. The clears call the
// pinned vector erase at 0x00532803 with the vector's own start/finish
// words (ParseSciences 0x339AF1 twin for the loop/erase shape). Serves
// the Browser entry of the table at 0x80EBE0. The callback name stays
// address-derived; the owning struct is BFME2-new (no BFME1 donor).

enum ScienceType
{
	SCIENCE_INVALID = 0
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, typename A = allocator<T> > class vector
{
public:
	T *erase(T *first, T *last);
	void push_back(const T &value);

	T *m_start;
	T *m_finish;
};
}

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	int scanIndexList(const char *token, const char * const *table);
	static void Rva00339E1C_ParseBrowser(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// ?Rva00339E1C_ParseBrowser@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva00339E1C_ParseBrowser(INI *ini, void *instance, void *store, const void *userData)
{
	_STL::vector<ScienceType> *vec = (_STL::vector<ScienceType> *)store;
	vec->erase(vec->m_start, vec->m_finish);
	for (;;) {
		const char *token = ini->getNextTokenOrNull(0);
		if (token == 0)
			break;
		if (_strcmpi(token, "None") == 0) {
			vec->erase(vec->m_start, vec->m_finish);
			break;
		}
		ScienceType value = (ScienceType)ini->scanIndexList(token, (const char * const *)userData);
		vec->push_back(value);
	}
}
