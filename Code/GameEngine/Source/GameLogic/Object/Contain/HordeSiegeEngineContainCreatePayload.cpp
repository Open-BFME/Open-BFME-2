// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0047CB89, 388B: HordeSiegeEngineContain::createPayload, the
// TransportContain::createPayload override of the HordeSiegeEngineContain
// primary vtable (ends with the qualified base call 0x004670D6).
// Body: the BFME 1 port (reference/open-bfme-1/game/GameEngine/Source/
// GameLogic/Object/Contain/HordeSiegeEngineContainCreatePayload.cpp, retail
// 0x0024A350 there), laid out from the matched sibling
// SiegeEngineContain::createPayload (0x0047BBA7). BFME 2 target evidence: the
// payload template name and count at module data +0x194/+0x198 (looked up
// without the sibling's emptiness test or null-template guard), the contain
// interface at Object+0x250 (enableLoadSounds slot 0x14C, isValidContainerFor
// 0x98), newObject with a zeroed 16-byte creation mask and the controlling
// player's default team (+0x2EC), the template's +0x354 seconds times the
// logic frame rate (BfmeLogicFramesPerSecond) as model condition 0xDA's frame count, the
// owner's name (+0x88) formatted "%s%d" onto each payload, and the rider add
// run as OpenContain's +0x20 interface slot 39 (pinned 0x00464830), qualified.

#include <string.h>
#include "ascii_string.h"
#include <stdio.h>

typedef int Int;
typedef float Real;

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


#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Iface00
{
	SLOT08(f00,f01,f02,f03,f04,f05,f06,f07)
	SLOT08(f08,f09,f0A,f0B,f0C,f0D,f0E,f0F)
	SLOT08(f10,f11,f12,f13,f14,f15,f16,f17)
	virtual void f18(); virtual void f19(); virtual void f1A(); virtual void f1B();
	const void *m_moduleData;
	Object *m_object;
};
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20
{
	SLOT08(g00,g01,g02,g03,g04,g05,g06,g07)
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	SLOT08(g16,g17,g18,g19,g20,g21,g22,g23)
	SLOT08(g24,g25,g26,g27,g28,g29,g30,g31)
	virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37(); virtual void g38();
	virtual void addToContain(Object *obj) = 0;
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0x9E0 - 0x38]; };

class OpenContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
{
public:
	virtual void addToContain(Object *obj);
};


struct HordeSiegeEngineContainModuleData
{
	unsigned char m_pad00[0x194];
	AsciiString m_payloadTemplateName;
	Int m_initialPayload;
};

class TransportContain : public OpenContain
{
public:
	void createPayload();
};

class HordeSiegeEngineContain : public TransportContain
{
public:
	virtual void createPayload();
};

void HordeSiegeEngineContain::createPayload()
{
	const HordeSiegeEngineContainModuleData *self = (const HordeSiegeEngineContainModuleData *)m_moduleData;
	Int count = self->m_initialPayload;
	const ThingTemplate *payloadTemplate = TheThingFactory->findTemplate( self->m_payloadTemplateName );

	Object *owner = m_object;
	ContainModuleInterface *contain = owner->getContain();
	if( contain )
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

				OpenContain::addToContain( payload );
			}
		}
		contain->enableLoadSounds( true );
	}

	TransportContain::createPayload();
}
