// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &other);
};

class AssetReference
{
public:
	AssetReference(const AssetReference &other);
};

class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
};

class Rva0028F68F
{
public:
	Rva0028F68F(const Rva0028F68F &other);
};

class Rva002390CB
{
public:
	Rva002390CB(const Rva002390CB &other);
};

class Gen_005e9a20
{
public:
	Gen_005e9a20(const Gen_005e9a20 &other);
};

class Rva00064640Record
{
public:
	Rva00064640Record(const Rva00064640Record &other);
};

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
template<> void _Construct<RvaSmartPtr12, RvaSmartPtr12>(RvaSmartPtr12 *dest, const RvaSmartPtr12 &source) throw() { new (dest) RvaSmartPtr12(source); }
template<> void _Construct<AssetReference, AssetReference>(AssetReference *dest, const AssetReference &source) throw() { new (dest) AssetReference(source); }
template<> void _Construct<WeaponTemplateSetHead, WeaponTemplateSetHead>(WeaponTemplateSetHead *dest, const WeaponTemplateSetHead &source) throw() { new (dest) WeaponTemplateSetHead(source); }
template<> void _Construct<Rva0036CA00Str, Rva0036CA00Str>(Rva0036CA00Str *dest, const Rva0036CA00Str &source) throw() { new (dest) Rva0036CA00Str(source); }
template<> void _Construct<Rva0028F68F, Rva0028F68F>(Rva0028F68F *dest, const Rva0028F68F &source) throw() { new (dest) Rva0028F68F(source); }
template<> void _Construct<Rva002390CB, Rva002390CB>(Rva002390CB *dest, const Rva002390CB &source) throw() { new (dest) Rva002390CB(source); }
template<> void _Construct<Gen_005e9a20, Gen_005e9a20>(Gen_005e9a20 *dest, const Gen_005e9a20 &source) throw() { new (dest) Gen_005e9a20(source); }
template<> void _Construct<Rva00064640Record, Rva00064640Record>(Rva00064640Record *dest, const Rva00064640Record &source) throw() { new (dest) Rva00064640Record(source); }
template<> void _Construct<Rva003AD160, Rva003AD160>(Rva003AD160 *dest, const Rva003AD160 &source) throw() { new (dest) Rva003AD160(source); }
template<> void _Construct<Rva003A6F70, Rva003A6F70>(Rva003A6F70 *dest, const Rva003A6F70 &source) throw() { new (dest) Rva003A6F70(source); }
}
