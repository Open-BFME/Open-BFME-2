// cl: /O1 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#include <vector>
#include "ascii_string.h"
void Rva00030830FreeAllocation(void *);
// Retail2892ED owns a 12B record buffer, consumed at ExperienceLevel+3C.
// Its stride8/string-tail cleanup uses the already rowed _Destroy body48CE25
// and element29D7C2. CameraMarker is only the existing ABI view of that
// shared worker; the target records are FX+AsciiString per the parse table.
// Rename the old object-symbol duplicate owner to this honest neutral dtor.
// Actual125B parent retains Rva002894A2, proven ctor/layout and no vptr reset.
// Game allocator30830 and two-string teardownB6CF1 use established providers.
class CameraMarker { public: ~CameraMarker(); char bytes[8]; };
namespace _STL { template<> void _Destroy<CameraMarker*>(CameraMarker*,CameraMarker*); }
struct Rva002892EDBuffer
{
 CameraMarker *start,*finish,*end;
 // ?Rva002892EDBuffer::~Rva002892EDBuffer absent-from-retail
 __forceinline ~Rva002892EDBuffer()
 {
  if(start) Rva00030830FreeAllocation(start);
 }
};
class Rva002892ED : public Rva002892EDBuffer
{
public:
 __declspec(noinline) ~Rva002892ED();
};
Rva002892ED::~Rva002892ED()
{
 _STL::_Destroy(start,finish);
}
class Rva001E3624
{
public:
 virtual ~Rva001E3624();
private:
 char base[12];
};
struct BfmeStringRecord000B94D2
{
 ~BfmeStringRecord000B94D2();
 char bytes[8];
};
struct Rva002894A2Radius
{
 BfmeStringRecord000B94D2 strings;
 char rest[44];
};
struct Rva002894A2PointerVector
{
 void *start,*finish,*end;
 // ?Rva002894A2PointerVector::~Rva002894A2PointerVector absent-from-retail
 __forceinline ~Rva002894A2PointerVector()
 {
  if(start) Rva00030830FreeAllocation(start);
 }
};
class __declspec(novtable) Rva002894A2 : public Rva001E3624
{
public:
 virtual ~Rva002894A2();
private:
 AsciiString name; // 10
 char words[16];
 std::vector<AsciiString> a,b; // 24,30
 Rva002892ED fx; // 3C
 int value48;
 Rva002894A2PointerVector upgrades; // 4C
 char member58[0x4C];
 Rva002894A2Radius radius; // A4
 char tail[0x30];
};
Rva002894A2::~Rva002894A2()
{
}
