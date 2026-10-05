// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD
//
// ?Rva0046133BParse@@YAXPAVINI@@PAX1PBX@Z, retail 0x0046133B (176B): the
// WayPoint FieldParse proc (row 0x00C42A58, store +0x120). Reads "Index" (an
// int) and "Type" sub-tokens; the type maps Walk / Climb / PreClimb to 2 / 3 / 4
// (left unset otherwise) and the {index, type} pair is appended to the vector
// at the store (8-byte-element push_back fold 0x00539A2E). Name
// address-derived.

#include "ascii_string.h"

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	int scanInt(const char *token);
};

struct Rva0046133BWayPoint
{
	int m_index;
	int m_type;
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<Rva0046133BWayPoint, allocator<Rva0046133BWayPoint> >
{
public:
	void push_back(const Rva0046133BWayPoint &x);
private:
	Rva0046133BWayPoint *m_start;
	Rva0046133BWayPoint *m_finish;
	Rva0046133BWayPoint *m_endOfStorage;
};
}

// ?Rva0046133BParse@@YAXPAVINI@@PAX1PBX@Z
void Rva0046133BParse(INI *ini, void *, void *store, const void *)
{
	Rva0046133BWayPoint wayPoint;
	wayPoint.m_index = ini->scanInt(ini->getNextSubToken("Index"));
	AsciiString type(ini->getNextSubToken("Type"));
	if (type.compare("Walk") == 0)
		wayPoint.m_type = 2;
	else if (type.compare("Climb") == 0)
		wayPoint.m_type = 3;
	else if (type.compare("PreClimb") == 0)
		wayPoint.m_type = 4;
	((_STL::vector<Rva0046133BWayPoint, _STL::allocator<Rva0046133BWayPoint> > *)store)->push_back(wayPoint);
}
