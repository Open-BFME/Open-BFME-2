// cl: /O2 /MD /EHsc
// Original Redwood6 APT0.19.03 private records identify the 102-byte constructor
// and its AptCIH* argument. PC caller6E2CBB reaches6E00E0. The native body allocates
// a20-byte AptPseudoCIH_t through the existing chain pool and initializes it with
// four zero arguments. Original PDB members give pControl/pControlInfo/next/prev/depth;
// the already rowed helper6F6A50 independently uses those exact offsets.
// Later APT3.02.02 AptDisplayListState.h (SHA256 prefix e2a3eac8055aa6ff) retains
// this constructor pattern; its expanded node layout is NOT used here.
// Native FuncInfo962A08 has one unwind action7A9070: sized delete20 via6D8680.
class AptCIH;
struct AptControl;
struct AptCharacter;
struct AptPseudoData_t;
class Rva006DB160 { public: void *allocBlock(int); };
class Rva006DB270 { public: void freeBlock(void *, int); };
extern Rva006DB270 *g_pChainBlockAllocator;
struct AptPseudoCIH_t {
 AptPseudoCIH_t(AptControl *, int, int, AptCharacter *);
 static void *operator new(unsigned int size) {return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock((int)size);}
 static void operator delete(void *, unsigned int);
 AptControl *pControl;
 AptPseudoData_t *pControlInfo;
 AptPseudoCIH_t *pNext,*pPrev;
 int nDepth;
};
class AptPseudoDisplayList {
public:
 AptPseudoDisplayList(AptCIH *);
private:
 AptPseudoCIH_t *pHead;
 AptCIH *pParentCIH;
};
AptPseudoDisplayList::AptPseudoDisplayList(AptCIH *pParent) {
 pHead=new AptPseudoCIH_t(0,0,0,0);
 pParentCIH=pParent;
}

// Bind the independently named original ABI to the existing byte-verified
// address-derived providers. The fourth constructor word is a character pointer.
#pragma comment(linker, "/alternatename:??0AptPseudoCIH_t@@QAE@PAUAptControl@@HHPAUAptCharacter@@@Z=??0Rva006F6A50@@QAE@PAXHHH@Z")
#pragma comment(linker, "/alternatename:??3AptPseudoCIH_t@@SAXPAXI@Z=?Rva006D8680Free@@YAXPAXH@Z")
typedef char AptPseudoCIHSize[sizeof(AptPseudoCIH_t)==20 ? 1 : -1];
typedef char AptPseudoDisplayListSize[sizeof(AptPseudoDisplayList)==8 ? 1 : -1];
