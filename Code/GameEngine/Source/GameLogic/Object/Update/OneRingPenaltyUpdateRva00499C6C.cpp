// cl: /GX /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/moduledata
// stlport
// ?rva00499C6C@OneRingPenaltyUpdate@@AAEXXZ @0x00499C6C 172B: private helper on the
// primary this; stamps +0x28/+0x30 from TheGameLogic frame, runs the ring +0x31
// gate with status 0x12 and emotion (5,0,1), plays the module-data +0x20 audio
// event through TheAudio slot 0x64, then runs BfmeC987::bfmeGo987C on this.
// Evidence: caller 0x00499D23 (OneRingPenaltyUpdate) ECX=this; rowed callees
// 0x0028F4BC 0x00374815 0x0023DB0E 0x0028EC68 0x002DA461 0x002D9A43 0x00499C46;
// vtable TheAudio +0x64; INI-free; neighbours OneRingPenaltyUpdateSlot0/Update.
#include "Common/BfmeAudioEventPrefix136.h"

typedef unsigned int UnsignedInt;

enum ObjectStatusTypes
{
	OBJECT_STATUS_12 = 0x12
};

class Rva00373EC6
{
public:
	void rva00374815();
	char m_pad00[0x31];
	bool m_31; // +0x31 +0x31
};

#include "../../../Common/Thing/thing.h"
enum ObjectID;
enum ObjectStatusTypes;
class Team;
class AIUpdateInterface;
class Rva00373EC6;
enum DamageType { DAMAGE_SNIPER = 8 };
enum DeathType { DEATH_NORMAL = 0 };
class Object : public Thing
{
public:
	void kill(DamageType damageType, DeathType deathType);
	bool rva0028F518();
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	Rva00373EC6 *rva0028F4BC();
	void rva0028EC68(int kind, void *payload, int flag);
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	unsigned char m_pad60[0x74 - 0x60];
public:
	ObjectID m_id74; // +0x74
private:
	unsigned char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
public:
	Team *m_team304; // +0x304
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/GameAudio.h"
extern AudioManager *TheAudio;

#include "../../../../Include/GameLogic/Module/BfmeC987.h"

#include "OneRingPenaltyModuleDataView.h"

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

#include "../../../../Include/GameLogic/Module/UpdateModule.h"


#include "../../../../Include/GameLogic/Module/OneRingPenaltyUpdate.h"

void OneRingPenaltyUpdate::rva00499C6C()
{
	UnsignedInt frame = TheGameLogic->getFrame();
	const OneRingPenaltyUpdateModuleData *data = reinterpret_cast<const OneRingPenaltyUpdateModuleData *>(getModuleData());
	m_28 = 0;
	Object *obj = m_object;
	m_30 = frame;
	Rva00373EC6 *ring = obj->rva0028F4BC();
	if (ring != 0 && ring->m_31)
	{
		ring->rva00374815();
		obj->setStatus((ObjectStatusTypes)0x12, false);
		obj->rva0028EC68(5, 0, 1);
		const OpaqueRefElement4 *ref = &data->m_discoveredSound;
		if (ref->referent != 0)
		{
			BfmeAudioEventPrefix136 evt(*ref, obj->m_id74);
			TheAudio->addAudioEvent(&evt);
		}
	}
	((BfmeC987 *)this)->bfmeGo987C();
}
