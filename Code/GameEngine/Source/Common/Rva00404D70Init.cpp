// cl: /DNDEBUG /DBFME_SB_CLEAR_DECL /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
// ?init@VictorySystem@@UAEXXZ @0x004055F2 146B
// Evidence: chain lane calls just-landed 0x00404BC5 ctor; reads ecx thiscall void; constructs AsciiString Default via rowed 0x00037BA0 then record via rowed 0x00404BC5 then push_back rowed 0x004055BB with releaseBuffer rowed 0x00036410; floats from 0x00BBB8D8 0x00BC2428 0x00BC7A54; vector at +0x120; neighbours share Rva00404D70 layout.
// Like the sibling parameter lookup, retain calls to the existing native
// record-vector push_back worker: the real STLport vector supplies the
// three-pointer layout and push_back stays a declaration bound to the kept
// provider. VictorySystem is the approved TU's view (VictorySystem.cpp); the
// +0x120 parameter vector is read as the record vector, as newMap does.
// init never reaches the 0xA8-byte root cell at +0x78 (Rva00404781.h), so it
// stays opaque here.
typedef bool Bool;
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include <vector>
#include "ascii_string.h"

class Xfer;

struct Rva0040538FElement
{
public:
	char bytes[24]; // +0x00
};

typedef _STL::_Vector_base<Rva0040538FElement,_STL::allocator<Rva0040538FElement> > VictoryParameterBase;

struct Rva00405350:public VictoryParameterBase {__forceinline Rva00405350():VictoryParameterBase(_STL::allocator<Rva0040538FElement>()){}~Rva00405350();Rva0040538FElement*first(){return _M_start;}Rva0040538FElement*last(){return _M_finish;}};

class CellGrid;

class VictorySystem:public SubsystemInterface,public Snapshot {
public:VictorySystem();void rva00404B03();virtual ~VictorySystem();virtual void init();virtual void reset();virtual void update();virtual void LoadPostProcess(){}virtual const char*GetSnapshotName()const{return "VictorySystem";}virtual void DoXfer(Xfer*);virtual void newMap();
 float cellSize10;unsigned field14;float firstScale18,secondScale1c,field20,field24;
 int playerParameterIndex28[20];char root78[0xA8];Rva00405350 parameters120;
 CellGrid*grids12c[2];bool initialized134;unsigned activeGrid138,currentPlayer13c;
};

struct BfmeStringRecord00404BF3
{
	AsciiString text; // +0x00
	float f0; // +0x04
	float f1; // +0x08
	float f2; // +0x0C
	float f3; // +0x10
	float f4; // +0x14
	BfmeStringRecord00404BF3(const AsciiString &s);
};

namespace _STL {
template <> void vector<BfmeStringRecord00404BF3>::push_back(const BfmeStringRecord00404BF3 &);
}

extern float g_Va00BBB8D8;
extern float g_Va00BC2428;
extern float g_00BC7A54;
// g_00BC7A54: matched references place it at VA 0xbc7a54 (retail .rdata value 5e+02f).
float g_00BC7A54 = 5e+02f;

void VictorySystem::init()
{
	BfmeStringRecord00404BF3 rec(AsciiString("Default"));
	float a = g_Va00BC2428;
	float b = g_Va00BBB8D8;
	float c = g_00BC7A54;
	rec.f4 = a;
	rec.f0 = b;
	rec.f1 = b;
	rec.f3 = c;
	rec.f2 = b;
	reinterpret_cast<_STL::vector<BfmeStringRecord00404BF3> *>(&parameters120)->push_back(rec);
}

// ?g_Va00BC2428@@3MA: matched references place it at VA 0xbc2428; also referenced as ?g_cloudBreakRadiusDefault@@3MA.
float g_Va00BC2428 = 1e+01f;
