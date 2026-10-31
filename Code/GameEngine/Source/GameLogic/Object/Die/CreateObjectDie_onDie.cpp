// ?onDie@CreateObjectDie@@UAEXPBVDamageInfo@@@Z
// cl: /FIzh_ascii.h /Ireference/shims/bfme2_createobjectdie /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/diemodule_link /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum /Ireference/shims/moduledata /I.
// stlport
//
// ?onDie@CreateObjectDie@@UAEXPBVDamageInfo@@@Z, retail 0x00485C86 139B (formerly the
// placeholder CreateObjectDieIfEldestKindof::rva00485C86): CreateObjectDie::onDie, slot 0 of
// CreateObjectDie's die-module table 0x00C4A7DC, gated on BFME2's upgrade list; also called by CreateObjectDieIfEldestKindof::onDie (0x00485D11),
// which tail-calls it as `push [ebp+8]; mov ecx,esi; call` -- so the method is __thiscall with
// `this` in ecx and `damageInfo` as its only stack argument (`ret 4`).
//
// Evidence: the literal "CreateObjectDieIfEldestKindof" appears in the caller at 0x00485D11 and
// passes the same `this`; vtable slot 12. Callees are all rowed: findUpgrade 0x0026F26D,
// getControllingPlayer 0x0028AFA9, Player::rva002AB87D 0x002AB87D, Object::hasUpgrade 0x00290D2B,
// GameLogic::findObjectByID 0x00049DC5 and ObjectCreationList::create 0x001F08D3.
// ModuleData view: OCL at +0x38, the upgrade name vector at +0x40 (begin) / +0x44 (end).
//
// Register shape (this is what the bytes pin down, and the reason the naive port mismatched):
// `this` stays live in edi to the very last push, the loop walks the name vector in ebx against
// esi=ModuleData, and the upgrading object is spilled to [ebp-4]. Re-deriving the tail argument
// from `this` rather than reusing the `obj` local is what keeps `this` live across the whole body
// and forces that spill; passing `obj` directly lets the optimiser drop the frame, and the body
// comes out 9 bytes short in a different register allocation.
// 0x00C4A7DC. The canonical base supplies the helper and owner/data offsets.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/GameType.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#define _GAME_LOGIC_H_  // the canonical GameLogic above replaces the Zero Hour copy AIUpdate.h names
extern GameLogic *TheGameLogic;
#include "GameLogic/Module/CreateObjectDie.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"

struct PlayerTeamNode;
class Player
{
public:
	bool rva002AB87D(const UpgradeTemplate *t) const;
	char m_pad00[0x32C];
	PlayerTeamNode *m_head32C; // +0x32C
};

// MSVC enters this override through DieModuleInterface at +0x10, slot 0 of
// 0x00C4A7DC. The base supplies the helper and owner/data offsets.

// ?onDie@CreateObjectDie@@UAEXPBVDamageInfo@@@Z
void CreateObjectDie::onDie(const DamageInfo *damageInfo)
{
	if (!isDieApplicable(damageInfo))
		return;
	Object *obj = m_object;
	const CreateObjectDieModuleData *data = getCreateObjectDieModuleData();
	const AsciiString *cur = data->m_upgradeRequired.begin();
	while (cur != data->m_upgradeRequired.end())
	{
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(*cur);
		if (upgradeTemplate)
		{
			bool ok;
			if (upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER)
				ok = obj->getControllingPlayer()->rva002AB87D(upgradeTemplate);
			else
				ok = obj->hasUpgrade(upgradeTemplate);
			if (!ok)
				return;
		}
		++cur;
	}
	ObjectCreationList *ocl = const_cast<ObjectCreationList *>(data->m_ocl);
	if (ocl == 0)
		return;
	ocl->create(m_object, TheGameLogic->findObjectByID(damageInfo->in.m_sourceID), (void *)0);
}
