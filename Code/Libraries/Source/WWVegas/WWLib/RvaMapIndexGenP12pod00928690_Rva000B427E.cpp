// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport

// _STL::pair<const Gen_p12pod,int>::pair(const Gen_p12pod&, const int&) is a
// <map> member emitted by the BFME1 donor RvaMapIndexGenP12pod00928690.cpp's
// map<Gen_p12pod,int> instantiation. Retail 0x000B427E copies the 12-byte key
// then stores the int at +0xC; the pair is emitted here by explicit
// instantiation, the donor's map body omitted.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Gen_p12pod
{
	int a[3];
};

template class _STL::pair<const Gen_p12pod, int>;
