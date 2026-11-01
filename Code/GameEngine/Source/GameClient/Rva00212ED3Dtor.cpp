// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00212ED3@@QAE@XZ, retail 0x00212AEF..0x00212ED3 (996 B, EH), and
// ??1Rva00212ED3@@QAE@XZ, retail 0x00212ED3 (503 B): the 0x1F0-byte member at
// LivingWorldManager+0x14. Built WITHOUT /Oa: /Oa let the scheduler hoist the
// EH state-0x12 store above the c8/e4/e8/ec float stores. The default texture
// pointer is a file static (non-aliased TU static), so its load still hoists
// above the 2nd/3rd colour copies without /Oa. kA/kB are the TU-local const
// floats retail keeps at 0x7E4558/0x7E455C (WB 0xB5C7A0 loads e8/ec from
// adjacent globals). Global names are descriptive, not original identifiers.
#include "ascii_string.h"
#include <vector>
#include "../../../Libraries/Include/Lib/Coord3D.h"
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
}
#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"
struct Rva00212ED3Ref {
 OpaqueRefCounted *m_ptr;
 Rva00212ED3Ref():m_ptr(0){}
 ~Rva00212ED3Ref(){if(m_ptr)m_ptr->Release_Ref();}
};
struct LivingWorldDefaultTriple {float a,b,c;};
const float kA=3.0f, kB=6.0f;
static const char *BfmeLivingWorldDefaultTexture="EXLaser.tga";
LivingWorldDefaultTriple BfmeLivingWorldDefaultTriple1={1.0f,0.2f,0.2f};
LivingWorldDefaultTriple BfmeLivingWorldDefaultTriple2={0.97f,0.64f,0.15f};
LivingWorldDefaultTriple BfmeLivingWorldDefaultTriple3={0.97f,0.64f,0.15f};
__forceinline void zeroCoord(Coord3D &pos){pos.x=0;pos.y=0;pos.z=0;}
class Rva00212ED3:public AsciiString {
public:Rva00212ED3(); ~Rva00212ED3();
private:
 struct InitialValue {unsigned value; InitialValue():value(20){}} word04;
 Coord3D coord08;
 int word14;
 float float018;
 float float01c;
 float float020;
 float float024;
 Coord3D coord028;
 AsciiString str034;
 Coord3D coord038;
 float float044;
 float float048;
 Coord3D coord04c;
 float float058;
 float float05c;
 Coord3D coord060;
 float float06c;
 float float070;
 Coord3D coord074;
 AsciiString str080;
 AsciiString str084;
 AsciiString str088;
 AsciiString str08c;
 AsciiString str090;
 AsciiString str094;
 AsciiString str098;
 AsciiString str09c;
 AsciiString str0a0;
 AsciiString str0a4;
 AsciiString str0a8;
 AsciiString str0ac;
 AsciiString str0b0;
 AsciiString str0b4;
 AsciiString str0b8;
 AsciiString str0bc;
 AsciiString str0c0;
 float float0c4;
 float float0c8;
 float float0cc;
 float float0d0;
 float float0d4;
 float float0d8;
 float float0dc;
 float float0e0;
 unsigned word0e4;
 float float0e8;
 float float0ec;
 LivingWorldDefaultTriple triple0f0;
 LivingWorldDefaultTriple triple0fc;
 LivingWorldDefaultTriple triple108;
 AsciiString str114;
 AsciiString str118;
 AsciiString str11c;
 Coord3D coord120;
 Coord3D coord12c;
 float float138;
 unsigned word13c;
 unsigned word140;
 unsigned word144;
 Rva00212ED3Ref ref148;
 Rva00212ED3Ref ref14c;
 Rva00212ED3Ref ref150;
 AsciiString str154;
 AsciiString str158;
 unsigned word15c;
 Coord3D coord160;
 Coord3D coord16c;
 unsigned word178;
 AsciiString str17c;
 AsciiString str180;
 AsciiString str184;
 _STL::vector<AsciiString> strings188;
 Coord3D coord194;
 unsigned word1a0;
 float float1a4;
 float float1a8;
 float float1ac;
 bool flag1b0;
 char pad1b1[3];
 float float1b4;
 float float1b8;
 float float1bc;
 float float1c0;
 float float1c4;
 float float1c8;
 unsigned word1cc;
 unsigned word1d0;
 unsigned word1d4;
 unsigned word1d8;
 unsigned word1dc;
 unsigned word1e0;
 unsigned word1e4;
 unsigned word1e8;
 bool flag1ec;
 char tail[3];
};
Rva00212ED3::Rva00212ED3()
 : AsciiString(),
   float018(2500.0f),
   float01c(-2000.0f),
   float020(0.8f),
   float024(0.0f),
   float044(0.0f),
   float048(0.0f),
   float058(0.0f),
   float05c(0.0f),
   float06c(0.0f),
   float070(0.0f),
   float0c4(0.01f),
   float0c8(3.0f),
   float0cc(0.0f),
   float0d0(100.0f),
   float0d4(100.0f),
   float0d8(100.0f),
   float0dc(5.0f),
   float0e0(40.0f),
   word0e4(100),
   float0e8(kA),
   float0ec(kB),
   triple0f0(BfmeLivingWorldDefaultTriple1),
   triple0fc(BfmeLivingWorldDefaultTriple2),
   triple108(BfmeLivingWorldDefaultTriple3),
   str114(BfmeLivingWorldDefaultTexture),
   float138(1.0f),
   word13c(1),
   word140(10),
   word144(150),
   word15c(20),
   word178(200),
   str180("bordercloud"),
   word1a0(3),
   float1a4(1.0f),
   float1a8(-1.0f),
   float1ac(2.0f),
   flag1b0(false),
   float1b4(0.75f),
   float1b8(0.75f),
   float1bc(0.01f),
   float1c0(0.82f),
   float1c4(200.0f),
   float1c8(3.0f),
   word1cc(100),
   word1d4(0),
   word1d8(10),
   word1dc(11),
   word1e0(25),
   word1e4(10),
   word1e8(10),
   flag1ec(false)
{
 coord038.x=coord038.y=coord038.z=0.0f;
 coord04c.x=coord04c.y=coord04c.z=0.0f;
 coord060.x=coord060.y=coord060.z=0.0f;
 coord074.x=coord074.y=coord074.z=0.0f;
 coord12c.x=coord12c.y=coord12c.z=0.0f;
 word1d0=0xC8000000;
 coord028.x=0; coord028.y=0; coord028.z=0;
 zeroCoord(coord120);
 zeroCoord(coord160);
 zeroCoord(coord16c);
 zeroCoord(coord194);
}

Rva00212ED3::~Rva00212ED3() {}
