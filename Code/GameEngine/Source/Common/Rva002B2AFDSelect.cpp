// cl: /O1 /MD /EHsc
// ?rva002B2AFD@Rva002B2AFD@@QAEHXZ, retail 0x002B2AFD, 48 bytes.
// Selector: if selection locked or TheGameLogic check fails, return
// TheWritableGlobalData field +0xe84, else TheGameLogic field +0x118.
// Evidence: call isSelectionLocked; jne alt; TheGameLogic->rva002034E9;
// jne alt; mov eax,[TheGameLogic]; mov eax,[eax+0x118]; ret; alt:
// mov eax,[TheWritableGlobalData]; mov eax,[eax+0xe84]; ret.
// Caller at 0x0038030D takes min with another int. Honest address name.
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};
class Rva002034E9Host
{
public:
	bool rva002034E9();
};
#include "GameLogicObjectLookupView.h"

// The canonical GameLogic header pads over the fields read here; they
// are reached through a view of the real TheGameLogic.
struct GameLogicFieldView
{
	char m_pad[0x118];
	int m_118;
};
extern GameLogic *TheGameLogic;
#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
class Rva002B2AFD
{
public:
	int rva002B2AFD();
};
int Rva002B2AFD::rva002B2AFD()
{
	if (((BfmeSelectionState *)this)->isSelectionLocked() || ((Rva002034E9Host *)TheGameLogic)->rva002034E9())
		return TheWritableGlobalData->m_initialMaxRingLevel;
	return ((GameLogicFieldView *)TheGameLogic)->m_118;
}

// Native visitor table at VA 0x00BFE090 contains the single entry 0x006B31DB.
// Target objects supply a state object at +0x78; its +0x2C is compared with 2.
// The callback's established int ABI carries that pointer-sized value.
// Original visitor identity and the meaning of its state remain open.
#include "../../Include/GameLogic/LivingWorldBattle.h"
#include "../../Include/GameLogic/ArmySummary.h"
class Rva003F498ACallback { public: virtual bool invoke(int)=0; ~Rva003F498ACallback() {} };
// ??0Rva002B31DB@@QAE@XZ, retail 0x002B31D2 (9B): this class's implicit
// default constructor, emitted out of line here as in retail (the uncalled
// copy right before invoke; it only installs vtable 0x007FE090).
class Rva002B31DB : public Rva003F498ACallback {
public:
 virtual bool invoke(int);
 ~Rva002B31DB() {}
};
bool Rva002B31DB::invoke(int value)
{
 ArmySummary *state=*(ArmySummary **)((char *)value+0x78);
 if (state->field2C==2) state->rva0040CA09();
 return true;
}

// Revived native2B4AF8..2B4B3D69B and40CA98..40CAC545B.
// Existing managerB0 and guardB5, single-slot callbackBFE090, and
// independently rowed2B31DB/40CA09 establish the traversal/transition.
// Display160 and GameLogic2034E9 guard the global call. Original names
// and full layouts remain unknown. Lookup20E5BB and singleton are now
// provided by real recovered code; no new pin or duplicated callback.
class Rva003F468D;
class Rva0020E6B7RegionManager { public: Rva003F468D *rva0020E6B7(); };
class Rva002B4AF8 {
public: void rva002B4AF8();
 char pad[0xb0]; Rva0020E6B7RegionManager *manager;
 unsigned char fieldB4; bool fieldB5;
};
void Rva002B4AF8::rva002B4AF8()
{
 if (!fieldB5) {
  LivingWorldBattle *battle=(LivingWorldBattle *)manager->rva0020E6B7();
  if (battle) {
   Rva002B31DB visitor;
   battle->rva003F498A(&visitor);
  }
 }
}

// Display slot 88 (+0x160) reads the bool at +0xD8, tested as a byte.
#include "../../Include/GameClient/Display.h"
class GameLogic;
extern GameLogic *TheGameLogic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0040CA98 { public: void rva0040CA98(); };
void Rva0040CA98::rva0040CA98()
{
 if (!TheDisplay->slot88() && ((Rva002034E9Host *)TheGameLogic)->rva002034E9())
  ((Rva002B4AF8 *)TheLivingWorldLogic)->rva002B4AF8();
}
