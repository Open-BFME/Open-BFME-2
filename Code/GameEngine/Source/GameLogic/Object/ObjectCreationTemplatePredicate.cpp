// cl: -DNDEBUG -DWIN32 -MD -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object

#include "ascii_string.h"

class ThingTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
// The lookup itself is the BfmeThingFactory facade (const return, proven by
// the retail body at 0x00137E80).
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};

extern BfmeThingFactory *TheThingFactory;

class Player
{
public:
	bool canBuild( const ThingTemplate *thingTemplate ) const;
};

// Zero Hour's ObjectTypes::canBuildAny (Common/ObjectTypes.cpp): the
// skirmish prerequisite condition at 0x003E49B8 calls it per player of the
// mask, and its callee 0x002ABEF1 is the rowed Player::canBuild.
class ObjectTypes
{
public:
	bool canBuildAny( Player *player );

private:
	unsigned char m_unmodelled_000[ 8 ];
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

bool ObjectTypes::canBuildAny( Player *player )
{
	for ( AsciiString *i = m_begin; i != m_end; ++i )
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate( *i );
		if ( thingTemplate && player->canBuild( thingTemplate ) )
			return true;
	}

	return false;
}
