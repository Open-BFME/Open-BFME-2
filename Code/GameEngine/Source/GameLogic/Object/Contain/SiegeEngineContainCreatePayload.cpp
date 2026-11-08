// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047BBA7, 421B: SiegeEngineContain::createPayload, slot 28 of the
// primary vtable 0x00C470F8 installed by the SiegeEngineContain constructor
// 0x0047C21E (the TransportContain::createPayload slot), ending with the
// qualified base call 0x004670D6.
// Body: the BFME 1 port (reference/open-bfme-1/game/GameEngine/Source/
// GameLogic/Object/Contain/SiegeEngineContainCreatePayload.cpp, retail
// 0x0022BA20 there). BFME 2 target evidence: the payload template name and
// count at module data +0x194/+0x198 (the name tested with the out-of-line
// StringBase<char>::isEmpty 0x00001E2F), TheThingFactory template lookup
// 0x002D06CA, the contain interface at Object+0x250 (enableLoadSounds slot
// 0x14C, isValidContainerFor 0x98, addToContain 0x9C), newObject with a
// zeroed 16-byte creation mask and the controlling player's default team
// (+0x2EC), the template's +0x354 seconds times the logic frame rate
// (BfmeLogicFramesPerSecond) as model condition 0xDA's frame count, and the owner's name
// (+0x88) formatted "%s%d" onto each payload.

#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef float Real;

#include <stdio.h>

extern int BfmeLogicFramesPerSecond;

class Team;

#include "../../../../Include/Common/Player.h"

#include "../../../../Include/Common/ThingTemplate.h"
static __forceinline Real templatePayloadSeconds(const ThingTemplate *t) { return t->m_buildFadeInOnCreateTime; }

class Object;

#include "../../../../Include/GameLogic/Module/ContainModule.h"

struct CreateMask
{
	unsigned int m_bits[4];
};

enum ModelConditionFlagType
{
	MODELCONDITION_0DA = 0xDA
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void setSpecialModelConditionState( ModelConditionFlagType type, unsigned int frames );
	// Keep the native +0x250 load inline; omit the competing legacy getter.
	__declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
	unsigned char m_pad00[0x88];
	AsciiString m_name;
	unsigned char m_pad8C[0x250 - 0x8C];
	ContainModuleInterface *m_contain;
};

enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject( const ThingTemplate *tmplate, Team *team, const CreateMask *mask, ObjectID b );
};

extern ThingFactory *TheThingFactory;

// TheThingFactory's template lookup, address-named as rowed.

struct SiegeEngineContainModuleData
{
	unsigned char m_pad00[0x194];
	AsciiString m_payloadTemplateName;
	Int m_initialPayload;
};

class TransportContain
{
public:
	virtual ~TransportContain();
	void createPayload();
protected:
	const SiegeEngineContainModuleData *getSiegeEngineContainModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }
private:
	const SiegeEngineContainModuleData *m_moduleData;
	Object *m_object;
};

class SiegeEngineContain : public TransportContain
{
public:
	virtual void createPayload();
};

void SiegeEngineContain::createPayload()
{
	const SiegeEngineContainModuleData *self = getSiegeEngineContainModuleData();
	Int count = self->m_initialPayload;
	const ThingTemplate *payloadTemplate =
		((const StringBase<char> &)self->m_payloadTemplateName).isEmpty()
			? 0
			: TheThingFactory->findTemplate(self->m_payloadTemplateName);

	Object *owner = getObject();
	ContainModuleInterface *contain = owner->getContain();
	if( contain && payloadTemplate )
	{
		contain->enableLoadSounds( false );
		for( Int i = 0; i < count; ++i )
		{
			CreateMask mask;
			memset( &mask, 0, sizeof( mask ) );
			Object *payload = TheThingFactory->newObject( payloadTemplate, owner->getControllingPlayer()->getDefaultTeam(), &mask, (ObjectID)0 );
			if( contain->isValidContainerFor( payload, true, false ) )
			{
				Int frames = (Int)( templatePayloadSeconds(payloadTemplate) * (Real)BfmeLogicFramesPerSecond );
				if( frames > 0 )
					payload->setSpecialModelConditionState( MODELCONDITION_0DA, frames );

				if( !((const StringBase<char> &)owner->m_name).isEmpty() )
				{
					char name[ 256 ];
					sprintf( name, "%s%d", owner->m_name.str(), i );
					payload->m_name = AsciiString( name );
				}

				contain->addToContain( payload );
			}
		}
		contain->enableLoadSounds( true );
	}

	TransportContain::createPayload();
}
