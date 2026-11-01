// cl: /DNDEBUG /MD /GX-
// parseScienceVector (retail 0x00339AF1, 95 bytes). Clears the
// ScienceType vector, then reads an OrNull token list: "None" clears and
// stops, anything else resolves through the rowed INI::scanScience at
// 0x00338A8D into a stack temp pushed through the rowed vector push_back
// at 0x002E01C6. The clears call the pinned vector erase at 0x00532803
// with the vector's own start/finish words (killerScience precedent for
// the ScienceType spelling). Serves the IntrinsicSciences,
// IntrinsicSciencesMP and SciencesGranted entries of the table at
// 0x7E2870. The retail CommandButton Science field uses this callback;
// the owning struct is BFME2-new (no BFME1 donor).

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

#include "../../../Include/Common/INI/INI.h"

#include <string.h>

// ?parseScienceVector@INI@@SAXPAV1@PAX1PBX@Z
void INI::parseScienceVector(INI *ini, void *instance, void *store, const void *userData)
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
		ScienceType value = INI::scanScience(token);
		vec->push_back(value);
	}
}
