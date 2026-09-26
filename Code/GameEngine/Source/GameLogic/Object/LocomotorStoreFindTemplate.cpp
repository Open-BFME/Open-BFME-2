// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?findLocomotorTemplate@LocomotorStore@@QAEPAVLocomotorTemplate@@H@Z
// retail 0x001E6FEA (38 bytes).
//
// BFME1 donor
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Locomotor.cpp):
// LocomotorStore::findLocomotorTemplate null-guards the key, finds the
// template in m_locomotorTemplates, and returns it or NULL. The trailing
// else is load-bearing: without it MSVC7.1 lays the shared zero block late
// (je-forward to it); with it the zero block is the fallthrough (jne into
// the find, miss jumps back to the shared xor).
//
// The true member is map<NameKeyType, LocomotorTemplate*> (donor
// Locomotor.h); the key arrives as a plain int here (retail takes the
// address of the int parameter straight into _M_find, so no enum-to-int
// temporary exists), and the member is spelled map<int, int> so the emitted
// _M_find call names the rowed const int-int helper 0x388F63 (identical
// tree mechanics); the stored int is cast back to the template pointer.

#include <map>

class LocomotorTemplate;

class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int namekey);

private:
	char m_pad[0xC];
	_STL::map<int, int> m_locomotorTemplates;
};

LocomotorTemplate *LocomotorStore::findLocomotorTemplate(int namekey)
{
	if (namekey == 0)
		return NULL;

	_STL::map<int, int>::iterator it = m_locomotorTemplates.find(namekey);
	if (it == m_locomotorTemplates.end())
		return NULL;
	else
		return (LocomotorTemplate *)(*it).second;
}
