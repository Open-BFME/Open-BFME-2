// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/diemodule_link /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum /Ireference/shims/moduledata /I.
// stlport
//
// ?rva00485C19@StatusBitsEldestFrame@@QAE_NPAVObject@@PBURva00485C19Data@@PBW4NameKeyType@@@Z, retail 0x00485C19 109B:
// eldest-of-kind check of the helper member StatusBitsUpgradeIfEldestKindof keeps at +0x1C and
// CreateObjectDieIfEldestKindof at +0x14. Walks the Object's controlling Player's teams (+0x32C)
// through TeamPrototype::rva0039ED9C with the callback 0x004859A2 and answers whether the Object
// found is the given one (dword +0x74). Returning the condition directly is
// what gives retail's xor eax,eax / inc eax tail.
//
// Evidence: LINK BONUS pin name; called by StatusBitsUpgradeIfEldestKindof 0x004B4AFF and
// CreateObjectDieIfEldestKindof::onDie 0x00485D11 with the module data's eldest-kind block and a
// cached module name key; callees getControllingPlayer 0x0028AFA9 and TeamPrototype 0x0039ED9C.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/GameType.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
#include "GameLogic/Object.h"

struct Rva00485C19Data
{
	int m_00;
};
typedef Int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);
// The callback 0x004859A2 is the rowed findEldest::func.
struct findEldest
{
public:
	static int func(Object *obj, void *userData);
};
class TeamPrototype
{
public:
	Int rva0039ED9C(ObjectIterateFunc func, void *userData);
};
struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};
class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *t) const;
	char m_pad00[0x32C];
	PlayerTeamNode *m_head32C; // +0x32C
};
struct StatusBitsEldestFrame
{
public:
	StatusBitsEldestFrame() { m_cachedFrame = (int)TheGameLogic->getFrame(); }
	StatusBitsEldestFrame *cacheGameLogicFrame(void);
	bool rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key);
private:
	int m_cachedFrame; // +0x00
};
struct Rva00485C19Ctx
{
	Object *m_found;
	int m_best;
	const Rva00485C19Data *m_data;
	NameKeyType m_key;
};
Bool StatusBitsEldestFrame::rva00485C19(Object *obj, const Rva00485C19Data *data, const NameKeyType *key)
{
	PlayerTeamNode **head = &obj->getControllingPlayer()->m_head32C;
	Rva00485C19Ctx ctx;
	ctx.m_found = 0;
	ctx.m_best = -1;
	ctx.m_data = data;
	ctx.m_key = *key;
	for (PlayerTeamNode *it = (*head)->m_next; it != *head; it = it->m_next)
		it->m_value->rva0039ED9C(findEldest::func, &ctx);
	return ctx.m_found != 0 && ctx.m_found->getID() == obj->getID();
}
