// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// platformsdk
// ?rva0023054C@GameEngine@@UAEXXZ, retail 0x0023054C..0x002306B8 (364B): a
// Ghidra-unlisted slot of GameEngine's table 0x00BE71F0 (between the rowed
// isMultiplayerSession and createMessageStream entries). Its teardown
// sequence is Zero Hour's GameEngine::~GameEngine (delete TheMapCache, end
// the results-queue threads, park TheScriptEngine, shut down and delete
// TheSubsystemList, then TheNetwork, TheCommandList, TheNameKeyGenerator and
// TheFileSystem) with BFME 2's extra globals read from retail. Pool objects go
// through slot 0 with a zero flag and a plain operator delete, as elsewhere in
// the ledger (ConnectionManager_reset.cpp). Callees and globals use the
// ledger's existing spellings; the receiver is not touched.

#include <windows.h>

struct BfmePoolDestroyable
{
	virtual void *destroy(unsigned int flags);
};

#define BFME_DELETE_INSTANCE(p) \
	operator delete((p) ? ((BfmePoolDestroyable *)(p))->destroy(0) : 0)

class BfmeDfe6e4;
class BfmeDfe6ec;
class NetworkInterface;
class CommandList;
class Rva00A00958Obj;
class NameKeyGenerator;
class FileSystem;
class ScriptEngine;

#include "../../Include/GameClient/MapCache.h"

#include "../../Include/Common/SubsystemInterfaceList.h"

class GameResultsInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void endThreads();
};

#include "../../Include/Common/Rva00214A8A.h"

class AttributeModifierStore;

// GameLODManager's empty destructor folds into the one-byte body at
// 0x000B3FD0.
#include "../../Include/Common/GameLODManager.h"

extern BfmeDfe6e4 *theBfmeDfe6e4;
extern BfmeDfe6ec *theBfmeDfe6ec;
extern MapCache *TheMapCache;
extern GameResultsInterface *TheGameResultsQueue;
extern ScriptEngine *TheScriptEngine;
extern AttributeModifierStore *TheAttributeModifierStore;
extern SubsystemInterfaceList *TheSubsystemList;
extern GameLODManager *TheGameLODManager;
extern NetworkInterface *TheNetwork;
extern CommandList *TheCommandList;
extern Rva00A00958Obj *g_Rva00A00958;
extern NameKeyGenerator *TheNameKeyGenerator;
extern FileSystem *TheFileSystem;

void Rva00270190Free();										// 0x00270190
void Rva00419A99Cleanup();									// 0x00419A99

#include "../../Include/Common/GameEngine.h"

void GameEngine::rva0023054C()
{
	BFME_DELETE_INSTANCE(theBfmeDfe6e4);
	theBfmeDfe6e4 = 0;

	delete TheMapCache;
	TheMapCache = 0;

	if (TheGameResultsQueue)
		TheGameResultsQueue->endThreads();

	theBfmeDfe6ec = (BfmeDfe6ec *)TheScriptEngine;
	TheScriptEngine = 0;
	if (TheAttributeModifierStore)
		((Rva00214A8A *)TheAttributeModifierStore)->rva00214A8A();

	TheSubsystemList->rva001B51C0();
	delete TheSubsystemList;
	TheSubsystemList = 0;

	delete TheGameLODManager;
	TheGameLODManager = 0;

	BFME_DELETE_INSTANCE(TheNetwork);
	TheNetwork = 0;
	BFME_DELETE_INSTANCE(TheCommandList);
	TheCommandList = 0;
	BFME_DELETE_INSTANCE(g_Rva00A00958);
	g_Rva00A00958 = 0;
	BFME_DELETE_INSTANCE(TheNameKeyGenerator);
	TheNameKeyGenerator = 0;
	BFME_DELETE_INSTANCE(TheFileSystem);
	TheFileSystem = 0;

	Rva00270190Free();
	Rva00419A99Cleanup();
	timeEndPeriod(1);
}
