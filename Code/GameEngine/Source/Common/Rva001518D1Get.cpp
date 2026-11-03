// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?rva001518D1@Rva001518D1@@QAEPAVRva00082EB8@@XZ at 0x001518D1 (68B).
// Getter returning the shader parameter vector at +0x0C or its static empty value.
// First deref +0 then +0x14 link proven by Rva00151632/Rva001517DE layout,
// fallback constructs empty via rowed Vector_base 0x00211E58 plus atexit
// row 0x006291F8. Caller 0x001526C1 proves getter shape.
#include <vector>
#include "ascii_string.h"

// The native atexit callback at 0x007B71AA calls the 0x0007C632
// wrapper, which destroys vector<Rva0007BB16Record> at 0x0007C5D5.
// The wrapper destructor already has a verified row in the post-FX lookup TU.
#include "../../../Libraries/Source/WWVegas/WWLib/Rva0007BB16Record.h"
namespace _STL { template <> vector<Rva0007BB16Record>::~vector(); }
class Rva00082EB8 : public _STL::vector<Rva0007BB16Record>
{
public:
	~Rva00082EB8();
};

class Link
{
public:
	char m_pad00[0x0C];
	Rva00082EB8 m_vec; // +0x0C
};

class Mid
{
public:
	char m_pad00[0x14];
	Link *m_link; // +0x14
};

class Rva001518D1
{
public:
	Rva00082EB8 *rva001518D1();
private:
	Mid *m_ptr; // +0
};

Rva00082EB8 *Rva001518D1::rva001518D1()
{
	if (m_ptr != 0 && m_ptr->m_link != 0)
		return &m_ptr->m_link->m_vec;
	static Rva00082EB8 empty;
	return &empty;
}
