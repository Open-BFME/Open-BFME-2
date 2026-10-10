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
// logic frame rate (g_009BA4E4) as model condition 0xDA's frame count, the
// owner's name (+0x88) formatted "%s%d" onto each payload, and the rider add
// run as OpenContain's +0x20 interface slot 39 (pinned 0x00464830), qualified.

#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl sprintf( char *buffer, const char *format, ... );

extern const int g_009BA4E4;

class Team;

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
	unsigned char m_pad00[0x2EC];
	Team *m_defaultTeam;
};

class ThingTemplate
{
public:
	unsigned char m_pad00[0x354];
	Real getPayloadSeconds() const { return m_payloadSeconds; }
	Real m_payloadSeconds;
};

class Object;

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0a();
	virtual void slot0b();
	virtual void slot0c();
	virtual void slot0d();
	virtual void slot0e();
	virtual void slot0f();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1a();
	virtual void slot1b();
	virtual void slot1c();
	virtual void slot1d();
	virtual void slot1e();
	virtual void slot1f();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual bool isValidContainerFor( const Object *obj, bool checkCapacity, bool bfmeFlag );
	virtual void addToContain( Object *obj );
	virtual void slot28();
	virtual void slot29();
	virtual void slot2a();
	virtual void slot2b();
	virtual void slot2c();
	virtual void slot2d();
	virtual void slot2e();
	virtual void slot2f();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3a();
	virtual void slot3b();
	virtual void slot3c();
	virtual void slot3d();
	virtual void slot3e();
	virtual void slot3f();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4a();
	virtual void slot4b();
	virtual void slot4c();
	virtual void slot4d();
	virtual void slot4e();
	virtual void slot4f();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void enableLoadSounds( bool enable );
};

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

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject( const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b );
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
	virtual void rva00464830(Object *obj) = 0;
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
	virtual void rva00464830(Object *obj);
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
			Object *payload = TheThingFactory->newObject( payloadTemplate, owner->getControllingPlayer()->getDefaultTeam(), &mask, false );
			if( contain->isValidContainerFor( payload, true, false ) )
			{
				Int frames = (Int)( payloadTemplate->getPayloadSeconds() * (Real)g_009BA4E4 );
				if( frames > 0 )
					payload->setSpecialModelConditionState( MODELCONDITION_0DA, frames );

				if( !((const StringBase<char> &)owner->m_name).isEmpty() )
				{
					char name[ 256 ];
					sprintf( name, "%s%d", owner->m_name.str(), i );
					payload->m_name = AsciiString( name );
				}

				OpenContain::rva00464830( payload );
			}
		}
		contain->enableLoadSounds( true );
	}

	TransportContain::createPayload();
}
