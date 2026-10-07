// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0GroupOrder@@QAE@XZ at retail 0x005488C5 (36B). The
// intermediate GroupOrder base is 0x18 bytes: vtable 0xC6A520
// at +0, a vector member at +4 built through the ICF-folded empty
// _Vector_base at 0x211E58, and nulls at +0x10/+0x14. Its only callers are
// the six group orders the factory 0x00354EFC creates (formerly rowed as
// SpecialPowerModuleData; the real SpecialPower base is 0x004930A0). The
// name GroupOrder is inferred from those six class names. The vector
// element type is invisible in retail bytes (the base call folds for every
// spelling); it is modeled as AsciiString after the SpawnBehavior
// precedent, which resolves with zero new pins. Six derived group-order
// ctors call this base (see ChangeStanceGroupOrderCtor.cpp).
extern "C" const void *const vtbl_00C6A520[];  // ??_7GroupOrder@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C6A520=??_7GroupOrder@@6B@")

#include <vector>

#include "ascii_string.h"

class GroupOrder
{
public:
	GroupOrder();

private:
	void *m_vtable; // +0
	_STL::vector<AsciiString> m_stringList; // +4
	void *m_unused10; // +0x10
	void *m_unused14; // +0x14
};

// ??0GroupOrder@@QAE@XZ @0x5488C5
GroupOrder::GroupOrder()
	: m_vtable(reinterpret_cast<void *>(((unsigned int)vtbl_00C6A520)))
{
	m_unused10 = NULL;
	m_unused14 = NULL;
}
