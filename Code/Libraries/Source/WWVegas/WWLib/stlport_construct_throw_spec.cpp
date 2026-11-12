// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// Throw()-specialized STLport _Construct<T> placement-copy helpers (18 bytes),
// same-shape siblings of the rowed _Construct<BfmeObject872> at 0x0002CF8A9
// (see Object872Copy.cpp). The throw() specification suppresses the EH frame,
// leaving a frameless null-guarded tail call into T's own rowed copy ctor.
// Each T is declared minimally (declared-only copy ctor, matching the
// struct/class-ness of its rowed copy ctor); no member is ever touched.
#include <memory>
#include <new>

#include "../../../../GameEngine/Include/Common/RvaSmartPtr12.h"

#include "../../../../GameEngine/Include/Common/AssetReference.h"

#include "../../../../GameEngine/Include/Common/WeaponTemplateSetHead.h"

#include "../../../../GameEngine/Include/Common/Rva0036CA00Str.h"

class Rva00263895Member
{
public:
	Rva00263895Member(const Rva00263895Member &other);
};

#include "../../../../GameEngine/Include/Common/Rva002390CB.h"

class Gen_005e9a20
{
public:
	Gen_005e9a20(const Gen_005e9a20 &other);
};

#include "../../../../GameEngine/Include/Common/Rva00064640Record.h"

class Rva003AD160
{
public:
	Rva003AD160(const Rva003AD160 &other);
};

class Rva003A6F70
{
public:
	Rva003A6F70(const Rva003A6F70 &other);
};

namespace _STL {
template<> inline void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *dest, const RvaSmartPtr12 &source) throw() { new (dest) RvaSmartPtr12(source); }
template<> inline void _Construct<AssetReference, AssetReference>(AssetReference *dest, const AssetReference &source) throw() { new (dest) AssetReference(source); }
template<> void _Construct<WeaponTemplateSetHead, WeaponTemplateSetHead>(WeaponTemplateSetHead *dest, const WeaponTemplateSetHead &source) throw() { new (dest) WeaponTemplateSetHead(source); }
template<> inline void _Construct<Rva0036CA00Str, Rva0036CA00Str>(Rva0036CA00Str *dest, const Rva0036CA00Str &source) throw() { new (dest) Rva0036CA00Str(source); }
template<> void _Construct<Rva00263895Member, Rva00263895Member>(Rva00263895Member *dest, const Rva00263895Member &source) throw() { new (dest) Rva00263895Member(source); }
template<> inline void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *dest, const Rva002390CB &source) throw() { new (dest) Rva002390CB(source); }
template<> void _Construct<Gen_005e9a20, Gen_005e9a20>(Gen_005e9a20 *dest, const Gen_005e9a20 &source) throw() { new (dest) Gen_005e9a20(source); }
template<> inline void _Construct<Rva00064640Record, Rva00064640Record>(Rva00064640Record *dest, const Rva00064640Record &source) throw() { new (dest) Rva00064640Record(source); }
template<> void _Construct<Rva003AD160, Rva003AD160>(Rva003AD160 *dest, const Rva003AD160 &source) throw() { new (dest) Rva003AD160(source); }
template<> void _Construct<Rva003A6F70, Rva003A6F70>(Rva003A6F70 *dest, const Rva003A6F70 &source) throw() { new (dest) Rva003A6F70(source); }
}

template void _STL::_Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *, const RvaSmartPtr12 &);
template void _STL::_Construct<Rva002390CB, Rva002390CB>(Rva002390CB *, const Rva002390CB &);
template void _STL::_Construct<Rva0036CA00Str, Rva0036CA00Str>(Rva0036CA00Str *, const Rva0036CA00Str &);
template void _STL::_Construct<Rva00064640Record, Rva00064640Record>(Rva00064640Record *, const Rva00064640Record &);
template void _STL::_Construct<AssetReference, AssetReference>(AssetReference *, const AssetReference &);
