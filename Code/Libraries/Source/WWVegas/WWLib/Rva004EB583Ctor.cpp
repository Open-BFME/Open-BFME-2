// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004EB5E9@@QAE@H@Z @0x004EB583 102B
// Target: ctor installs VA 0x00C62928; slot 0 reaches destructor 0x004EB5E9
// through deleting wrapper 0x004EB778. The destructor proves pointer elements
// at +8/+0x1C; +0x28 retains its compatible BfmeE16 view. All three headers
// use the folded vector-base constructor 0x00211E58. Scalar initializers and
// the shared serial counter reproduce the complete 102-byte retail body.
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"
class Cleanup4EB5E9;
extern int g_00E044A0;
// g_00E044A0: matched references place it at VA 0xe044a0 (zero-filled .bss).
int g_00E044A0;
class Rva004EB5E9 {
public:
 Rva004EB5E9(int value);
 virtual ~Rva004EB5E9();
private:
 int count;
 _STL::vector<Cleanup4EB5E9 *> owned8;
 Cleanup4EB5E9 *single;
 int unknown18;
 _STL::vector<Cleanup4EB5E9 *> owned1C;
 _STL::vector<BfmeE16> data28;
 int unknown34,unknown38,unknown3C,unknown40,uniqueID,argument;
};

Rva004EB5E9::Rva004EB5E9(int v)
 : count(0), owned8(_STL::allocator<Cleanup4EB5E9 *>()), single(0), unknown18(0),
   owned1C(_STL::allocator<Cleanup4EB5E9 *>()), data28(_STL::allocator<BfmeE16>()),
   unknown34(0), unknown38(-1), unknown3C(0), unknown40(-1),
   uniqueID(g_00E044A0++), argument(v)
{
}
