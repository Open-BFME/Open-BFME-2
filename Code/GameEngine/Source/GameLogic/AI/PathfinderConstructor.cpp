// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/ini_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// BF1 f98983a7d PathfinderConstructor.cpp and ZH AIPathfind.cpp are semantic
// guides. Target366B 2F6E22..2F6F90 and matched destructor172B 2F213F
// establish Snapshot+4 and seven primary slots; sixteen64B layers+60;
// zone accessed prefix1BA54 at460 plus explicit108 gap;64 strings1BFBC;
// head array1C0BC; tree1C1C0; POD vector1C1CC; heap1D1F0. Original
// names for the seven primary methods and unknown fields remain unresolved.
// Counter volatile stores preserve retail's witnessed initialization ordering.

#include "ascii_string.h"

#include "Common/INI/INI.h"
#include <set>
#include <vector>
typedef unsigned int PathfinderWord;

class PathfindServicesInterface {public: virtual void slot0()=0;virtual void slot1()=0;virtual void slot2()=0;virtual void slot3()=0;virtual void slot4()=0;virtual void slot5()=0;virtual void slot6()=0;};
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

class PathfindLayer
{
public:
	PathfindLayer();
	~PathfindLayer();
	char m_unknown[0x40];
};

class PathfindZoneManager
{
public:
	PathfindZoneManager();
	~PathfindZoneManager();
	char m_unknown[0x1BA54];
};

// Native local registry callback2E7D28 uses its existing ledger name.
// Passing the canonical INI callback type preserves the12B registration ABI.
class BfmeSub939E;
extern void bfmeGo939E(BfmeSub939E *);
typedef void (*INIBlockParse)(INI *);

struct BlockParse;
extern BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse callback;
	__forceinline BlockParse(const char *name, INIBlockParse function) : next(theBlockParseList), token(name), callback(function) { theBlockParseList=this; }
};
extern BlockParse *theBlockParseList;


struct PathfinderCostCellInfo { int x,y; };
struct Rva002F35AFHop { int m_zone; PathfinderCostCellInfo m_position; };
struct Rva002F0D35Record {void *m_value; bool operator<(const Rva002F0D35Record &) const;};
class Rva002F3738 {public: __declspec(noinline) Rva002F3738(); ~Rva002F3738(); private: _STL::vector<Rva002F0D35Record> m_vec; _STL::less<Rva002F0D35Record> m_less; };
Rva002F3738::Rva002F3738() {}


class Pathfinder : public PathfindServicesInterface, public Snapshot
{
public:
	Pathfinder();
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6();
	virtual ~Pathfinder();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
	void rva002F462C();

 char m_prefix[4];
 PathfinderWord m_field0C,m_field10;
 char m_unknown14[0x20];
 PathfinderWord m_field34;
 char m_unknown38[0x20];
 PathfinderWord m_field58,m_field5C;
 PathfindLayer m_layers[16];
 PathfindZoneManager m_zoneManager;
 char gap1BEB4[0x108];
 AsciiString m_strings[64];
 unsigned int m_heads[64];
 char gap1C1BC[4];
 _STL::set<unsigned int> m_set;
 _STL::vector<Rva002F35AFHop> m_vector;
 volatile unsigned int m_word1C1D8,m_word1C1DC;
 char gap1C1E0[0x800];
 volatile unsigned int m_word1C9E0,m_word1C9E4;
 char gap1C9E8[0x800];
 volatile unsigned int m_word1D1E8; unsigned int m_word1D1EC;
 Rva002F3738 m_lastVector;

};

Pathfinder::Pathfinder()
 : m_field0C(0),m_field10(0),m_field34(0),m_field58(0),m_field5C(0),
   m_word1C1D8(0),m_word1C1DC(0),m_word1C9E0(0),m_word1C9E4(0),m_word1D1E8(0),m_word1D1EC(0)
{
 for(int i=0;i<64;++i)m_heads[i]=0;
 rva002F462C();
 static BlockParse pathfinderRegistration("Pathfinder",reinterpret_cast<INIBlockParse>(bfmeGo939E));
 INI ini;
 ini.loadFile(AsciiString("Data\\INI\\Pathfinder.ini"),INI_LOAD_OVERWRITE,(Xfer *)0);
}
