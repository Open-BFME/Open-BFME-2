// cl: -DNDEBUG -DWIN32 -MD /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport

#include <vector>

#include "Common/Snapshot.h"

#include "ascii_string.h"

class Xfer;

class ThingTemplate;

// 0x002D06CA is rowed as ThingFactory::findTemplate (ThingFactory.cpp);
// the facade view is replaced so the call resolves to the rowed body
// instead of the unrowed BfmeThingFactory spelling (sole U on this unit).
class ThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};
extern ThingFactory *TheThingFactory;

class Player
{
public:
	bool canBuild( const ThingTemplate *thingTemplate ) const;
};

// Zero Hour's ObjectTypes::canBuildAny (Common/ObjectTypes.cpp): the
// skirmish prerequisite condition at 0x003E49B8 calls it per player of the
// mask, and its callee 0x002ABEF1 is the rowed Player::canBuild.
class __declspec(novtable) ObjectTypes : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual ~ObjectTypes();
	bool canBuildAny( Player *player );
private:
	AsciiString m_listName;
	_STL::vector<AsciiString> m_objectTypes;
public:
	bool isInSet(const AsciiString &name) const;
	void addObjectType(const AsciiString &objectType);
};

// Retail walks the vector's begin/end pointers (this+0x08/+0x0C) directly.
bool ObjectTypes::canBuildAny( Player *player )
{
	for ( AsciiString *i = (AsciiString *)((void **)this)[2]; i != (AsciiString *)((void **)this)[3]; ++i )
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate( *i );
		if ( thingTemplate && player->canBuild( thingTemplate ) )
			return true;
	}

	return false;
}
