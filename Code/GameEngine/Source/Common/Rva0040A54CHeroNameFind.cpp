// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// STLport 4.5.3 find_if over the CreateAHeroData* vector with the by-name
// functor rowed at 0x40A424 (an AsciiString compared case-insensitively
// against the hero's name at +0x4C). Sibling of the two __find_if
// instantiations in Rva0040A1ACHeroPtrAlgos.cpp; this functor owns a
// string, so the bodies carry an EH frame that releases the by-value copy
// (StringBase copy 0x365F0, releaseBuffer 0x36410). find_if (0x40A54C) passes
// the tag temporary by address to the 4x unrolled __find_if, which retail
// keeps at 0x40A46F: that body is rowed as Rva0040A46FFind
// (Rva0040A46FFind.cpp), and this unit's implicit __find_if instantiation
// compiles to the same bytes, so its name is fold-pinned there. The
// functor's compare is throw(): retail __find_if never enters EH state 0
// for its by-value functor, which the compiler does only when nothing in the
// loop can throw; the rowed body only calls the throw() compareNoCase. The
// only caller is the lookup at 0x40A5CF.
#include "ascii_string.h"
#include <algorithm>
#include <vector>

class CreateAHeroData;

class Rva0040A424
{
public:
	Rva0040A424(const AsciiString &name) : m_name(name) {}
	bool rva0040A424(CreateAHeroData *value) throw();
	bool operator()(CreateAHeroData *p) { return rva0040A424(p); }
private:
	AsciiString m_name;
};

template CreateAHeroData **_STL::find_if<CreateAHeroData **, Rva0040A424>(CreateAHeroData **, CreateAHeroData **, Rva0040A424);

// The CreateAHeroData* list of Rva0040A3F9Find.cpp (vector at +0).
class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A5CF(const AsciiString &name);
private:
	_STL::vector<CreateAHeroData *> m_list;
};

// ?rva0040A5CF@Rva0040A3F9@@QAEPAVCreateAHeroData@@ABVAsciiString@@@Z
// @0x0040A5CF 52B: the hero with this name, or null. The functor is built in
// find_if's argument slot straight from the key (StringBase copy 0x365F0).
CreateAHeroData *Rva0040A3F9::rva0040A5CF(const AsciiString &name)
{
	_STL::vector<CreateAHeroData *>::iterator found = _STL::find_if(m_list.begin(), m_list.end(), Rva0040A424(name));
	if (found == m_list.end())
		return 0;
	return *found;
}
