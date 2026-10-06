// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?rva002B48E1@Rva002B48E1@@QAEPAURva002E1948Entry@@ABVAsciiString@@@Z, retail 0x002B48E1, 72 bytes.
// Searches the Rva002E1948Lookup vector at +0x8C for the first entry whose
// rowed find at 0x002E1948 accepts the AsciiString key, returning it or null.
// Evidence: callees rowed; callers 0x003F8454 0x00564C22 0x005650B7; same
// vector-find idiom and flags as Rva002BA8F1Lookups.cpp.
#include <vector>

class AsciiString { public: int compare(const AsciiString &) const; private: void *data; };
struct Rva002E1948Entry { char m_0[0x1c]; AsciiString m_1c; };
class Rva002E1948Lookup {
public:
	Rva002E1948Entry *find(const AsciiString &);
};

class Rva002B48E1 {
	char m_pad[0x8C];
	_STL::vector<Rva002E1948Lookup *> m_vec8C;
public:
	Rva002E1948Entry *rva002B48E1(const AsciiString &name);
};

Rva002E1948Entry *Rva002B48E1::rva002B48E1(const AsciiString &name)
{
	for (unsigned int i = 0; i < m_vec8C.size(); ++i) {
		Rva002E1948Entry *entry = m_vec8C[i]->find(name);
		if (entry != 0)
			return entry;
	}
	return 0;
}
