// cl: /O2 /MD /EHsc
// ?Rva006CFAB0@@YAXH@Z retail 0x006CFAB0..0x006CFCCE (542 bytes).
// Apt core shutdown: the counterpart of the Apt.cpp initializer at
// 0x006CF230. Evidence: its own assert strings "bInitialized" (line 0x20E)
// and "gpPool" (lines 0x20F and 0x226) carry the Apt.cpp source path; it
// tears down exactly the pool objects the initializer allocates (linker
// 0x18 bytes at E176F8 / manager 4 bytes at E176CC / playback checkpoints
// 0x1C bytes at E176EC / root 0xB4 bytes at E176D0 / value vectors 0x10
// bytes at E17714 and E17710) through destructor plus chain-block
// freeBlock(ptr size) calls and clears bInitialized at E17700 last.
// The single int argument is forwarded to AptValueShutdown (0x006DC7C0).
// Callee names come from their ledger rows or symbol pins; the two pinned
// virtual-destructor spellings are called qualified (retail calls them
// directly) through views of the stored objects.

class Rva006DB270 {public:void freeBlock(void *,int);};
extern Rva006DB270 *g_pChainBlockAllocator;

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptInitAtE17700,g_bfmeAptBreakOnAssertAtDDC01C;
extern unsigned char g_00E18348;
#define CHECK(e,s,l) do{if(!(e)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}}while(0)

class AptMath {public:static void ClipStackShutdown();};
class AptAnimationPoolData {public:void PreDestroy();};
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
void rva006CE1C0(int);

#define POOL_DELETE static void operator delete(void *p,unsigned n){g_pChainBlockAllocator->freeBlock(p,n);}
class Rva006CFA30 {public:class Members {public:~Members();POOL_DELETE char pad[0x18];};};
class AptLinker;
extern AptLinker *g_bfmeAptLinkerAtE176F8;
class Rva006D1090 {public:~Rva006D1090();POOL_DELETE int head;};
class Rva00893030Manager;
extern Rva00893030Manager *g_rva00893030Manager;
class Rva006CEA60 {public:virtual ~Rva006CEA60();};
// Deletion views: their inline destructors forward to the pinned complete
// destructors so the delete expressions keep retail's operand copy.
class Rva006CEA60Delete {public:~Rva006CEA60Delete(){((Rva006CEA60 *)this)->Rva006CEA60::~Rva006CEA60();}POOL_DELETE char pad[0x1c];};
class Rva006CEB10Playback;
extern Rva006CEB10Playback *g_aptPlaybackCheckpoints;
class Rva006E6060Root {public:~Rva006E6060Root();};
class Rva006E6430Delete {public:~Rva006E6430Delete(){((Rva006E6060Root *)this)->~Rva006E6060Root();}POOL_DELETE char pad[0xb4];};

void AptValueShutdown(int);
void rva008B8B80ReleaseAll();
class AptDate {public:static void CleanNativeFunctions();};
void rva008A4630ReleaseGlobals();
void rva008A47B0ReleaseGlobals();
void bfmeGo1062B();
void rva008B2BD0ReleaseGlobals();
void bfmeGo1083A();
void bfmeGo1082C();
void bfmeGo1082B();
void rva008A48D0ReleaseGlobals();
void d_008acac0();
void rva008A98B0ReleaseAll();
void Rva006E97A0();
class AptGC {public:static void CleanAll();};
void Rva00898D60Invoke();

class AptValueVector {public:void ReleaseValues();void rva006E6D50();};
class AptValueVectorDelete {public:~AptValueVectorDelete(){((AptValueVector *)this)->rva006E6D50();}POOL_DELETE char pad[0x10];};
extern AptValueVector *g_releaseVectorAtE17710;
extern AptValueVector *g_aptOptionalValueVector;
class EAStringC {void *data;public:void rva006D3470();};
extern EAStringC g_eaStringAtE177D4;
void Rva0070D9F0Shutdown();
void Rva006D37F0Clear();
struct AptActionInterpreter {void rva006FEB50();};
extern AptActionInterpreter g_aptDateInterpreter;
class AptBoolean {public:static void ClearPool();};
class AptInteger {public:static void ClearPool();};
class AptFloat {public:static void ClearPool();};
class StringPool {public:static void ClearTemporaryPool();};

void Rva006CFAB0(int arg)
{
	CHECK(g_bfmeAptInitAtE17700,"bInitialized",0x20e);
	CHECK(g_bfmeAptPtrAtE176D0,"gpPool",0x20f);
	g_00E18348=1;
	AptMath::ClipStackShutdown();
	((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->PreDestroy();
	rva006CE1C0(1);
	delete (Rva006CFA30::Members *)g_bfmeAptLinkerAtE176F8;
	delete (Rva006D1090 *)g_rva00893030Manager;
	delete (Rva006CEA60Delete *)g_aptPlaybackCheckpoints;
	AptValueShutdown(arg);
	rva008B8B80ReleaseAll();
	AptDate::CleanNativeFunctions();
	rva008A4630ReleaseGlobals();
	rva008A47B0ReleaseGlobals();
	bfmeGo1062B();
	rva008B2BD0ReleaseGlobals();
	bfmeGo1083A();
	bfmeGo1082C();
	bfmeGo1082B();
	rva008A48D0ReleaseGlobals();
	d_008acac0();
	rva008A98B0ReleaseAll();
	Rva006E97A0();
	AptGC::CleanAll();
	Rva00898D60Invoke();
	g_releaseVectorAtE17710->ReleaseValues();
	CHECK(g_bfmeAptPtrAtE176D0,"gpPool",0x226);
	delete (Rva006E6430Delete *)g_bfmeAptPtrAtE176D0;
	g_bfmeAptPtrAtE176D0=0;
	if(g_aptOptionalValueVector)delete (AptValueVectorDelete *)g_aptOptionalValueVector;
	g_aptOptionalValueVector=0;
	g_eaStringAtE177D4.rva006D3470();
	Rva0070D9F0Shutdown();
	g_releaseVectorAtE17710->ReleaseValues();
	delete (AptValueVectorDelete *)g_releaseVectorAtE17710;
	g_releaseVectorAtE17710=0;
	Rva006D37F0Clear();
	g_aptDateInterpreter.rva006FEB50();
	AptBoolean::ClearPool();
	AptInteger::ClearPool();
	AptFloat::ClearPool();
	StringPool::ClearTemporaryPool();
	g_bfmeAptInitAtE17700=0;
}
#undef CHECK
