// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv888.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingEYF::bfmeGoEYF 0x0030DE61 (37B), bfmeGoEYE
// 0x0030E2C9 (35B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.

// EA's GlobalData (Common/GlobalData.h) is only forward declared here; this
// global is retail 0x012ED5C8, defined once in
// GameEngine/Source/Common/GlobalData.cpp, so it must be spelled
// GlobalData * (class, not struct) to mangle to the same name.  The local
// view above supplies the member this TU reads.
class GlobalData;

extern GlobalData *TheWritableGlobalData;
void *__cdecl bfmeMakeEYA(unsigned int a, unsigned int b);


extern "C" char *bfmeTabEYC[];
extern "C" unsigned char bfmeStrAEYC[];
extern "C" unsigned char bfmeStrBEYC[];


struct BfmeNodeEYE
{
	void bfmeRunEYE();
	unsigned char m_bfmeHead[4];
	BfmeNodeEYE *m_bfmeNext;
};

struct BfmeListEYE
{
	BfmeNodeEYE *m_bfmeHead;
};

// retail 0x012ED5DC: the one global pointer defined as `int *` in
// Common/Rva00087480Get.cpp. The local view below supplies the member this
// TU reads, exactly as for TheWritableGlobalData above.
extern class BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
extern void *g_bfmeCurEYE;

void __cdecl bfmeGoEYE(void *a)
{
	g_bfmeCurEYE = a;
	for (BfmeNodeEYE *n = reinterpret_cast<BfmeListEYE *>((*(int **)&BfmeTheMapObjectListHolder))->m_bfmeHead; n; n = n->m_bfmeNext)
		n->bfmeRunEYE();
}

// 0x0030E2EC / 0x0030E2F5 (9B each), retail's next two bodies after
// bfmeGoEYE: clear / set bit 0x10 of the dword at +0x44, then tail-jump to
// bfmeRunEYE (0x0030DEAE) on the same this. The pair matches Open-BFME-1's
// S3FlagForwarders.cpp (Gen_00088B60::bfmeClearForward / bfmeForward) in
// shape; original class and method names are unknown, so the class is
// address-named.
class Rva0030E2ECFlags
{
public:
	void rva0030E2EC();
	void rva0030E2F5();

private:
	unsigned char m_bfmeHead[0x44];
	unsigned int m_bfmeFlags;
};

void Rva0030E2ECFlags::rva0030E2EC()
{
	m_bfmeFlags &= ~0x10U;
	reinterpret_cast<BfmeNodeEYE *>(this)->bfmeRunEYE();
}

void Rva0030E2ECFlags::rva0030E2F5()
{
	m_bfmeFlags |= 0x10U;
	reinterpret_cast<BfmeNodeEYE *>(this)->bfmeRunEYE();
}

struct BfmeNodeEYF
{
	unsigned char m_bfmeHead[4];
	BfmeNodeEYF *m_bfmeNext;
};

// The callee at 0x0030DC85 is rowed as the map-object chunk reader
// (MapObjectReadRva0030DC85.cpp); called by that row's name and signature.
class DataChunkInput;
struct DataChunkInfo;
class Rva0030DBD5;
Rva0030DBD5 *__cdecl Rva0030DC85ReadMapObject(DataChunkInput &file, DataChunkInfo *info);

struct BfmeThingEYF
{
	bool bfmeGoEYF(void *a, void *b);
	unsigned char m_bfmeHead[0xc];
	BfmeNodeEYF *m_bfmeHead2;
};

bool BfmeThingEYF::bfmeGoEYF(void *a, void *b)
{
	BfmeNodeEYF *n = (BfmeNodeEYF *)Rva0030DC85ReadMapObject(*(DataChunkInput *)a, (DataChunkInfo *)b);
	if (n)
	{
		m_bfmeHead2->m_bfmeNext = n;
		m_bfmeHead2 = n;
	}
	return true;
}


void __cdecl bfmeFreeEYG(void *p, unsigned int n);


