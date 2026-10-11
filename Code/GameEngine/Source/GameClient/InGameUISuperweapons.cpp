// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// InGameUI's superweapon timer bookkeeping: findSWInfo and the virtual
// add/remove/objectChangedTeam family of vftable 0x7FD410.
// Donor: ZH GameEngine/Source/GameClient/InGameUI.cpp (findSWInfo,
// addSuperweapon, objectChangedTeam), same control flow.
// Target evidence for the layout: findSWInfo (0x002A435D, ret 0x10) indexes
// this + (playerIndex + 0x84) * 12, so the per-player superweapon maps (12-byte
// STLport maps) start at +0x630; it calls the shared AsciiString-key tree find
// 0x001F8437, compares the result with the map header, walks the list held in
// the node at +0x14 and matches SuperweaponInfo::m_id at +0x18 (the 0x24-byte
// record built by the ctor 0x0029B74A, vftable 0x7FD028).
// addSuperweapon (0x002A70AE, slot 34): BFME 2 hides the timer when the
// template's required science list (by-value getter 0x0029FCB4) is non-empty
// and the owner has none of it (Player::hasAnyRequiredSciences 0x002AB7FD),
// where ZH tested one science. The record is a plain 0x24-byte new (0x0002FDA0)
// built with ten arguments (no evaReadyPlayed); font, point size and bold come
// from this+0x72C/+0x730/+0x734 and the color from the player's +0x280. The
// per-name list comes from the map subscript 0x002A6A2D and the append is the
// folded four-byte list push_back 0x0005548F. The local science vector carries
// unwind state -1 before its inline teardown because the game's free 0x00030830
// is C++-linkage and may throw: the _STL::free spelling (SidesList castle maps
// idiom) reproduces it; the extern "C" import would be nothrow.
// objectChangedTeam (0x002A43A0, slot 36): the object's id at +0x74 and its
// behavior module list at +0x244; each module's special power comes from slot
// 8 of its BehaviorModuleInterface base at +0xC and the template from slot 6
// of the power; the name is +0x10 of the template's final override
// (Overridable::friend_getFinalOverride 0x00288609). Remove and add go through
// slots 35 and 34. The fallback add tests TheGameLogic's frame (+0x40),
// Object::testStatus 0x0004E536 with status 2 and KINDOF_COMMANDCENTER, bit 1
// of the template's kind-of byte at +0x10A.
// removeSuperweapon (0x002A4975, slot 35): the list erase is the folded
// four-byte list erase 0x00438539, the record goes through ::delete (virtual
// dtor with flag 0, then operator delete 0x0002FD60) and an emptied name entry
// is dropped by the out-of-line tree erase 0x002A408B.
// hide/showObjectSuperweaponDisplayByScript (0x0029E20B / 0x0029E25A, slots
// 39/40): twenty player maps (the loop count is 0x14) walked with
// _M_increment 0x00024250, writing m_hiddenByScript at +0x20.
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <list>
#include <map>
#include <vector>
#define private public
#include <hash_map>
#undef private
#undef free
#include "ascii_string.h"
#include "../Common/GameLogicObjectLookupView.h"
enum ScienceType { SCIENCE_INVALID = -1 };
typedef _STL::vector<ScienceType> ScienceVec;

enum NameKeyType { NAMEKEY_INVALID = 0 };
namespace rts {
template <class T> struct hash {
	size_t operator()(const T &value) const { return (size_t)value; }
};
}
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class DebugStream
{
public:
	virtual void dslot0();
	virtual void dslot1();
	virtual void dslot2();
	virtual void dslot3();
	virtual void dslot4();
	virtual void dslot5();
	virtual void dslot6();
	virtual void dslot7();
	virtual void dslot8();
	virtual void dslot9();
	virtual void dslot10();
	virtual void dslot11();
	virtual void dslot12();
	virtual void dslot13();
	virtual DebugStream &slot38(const char *msg);
	virtual void dslot15();
	virtual void dslot16();
	virtual void dslot17();
	virtual void dslot18();
	virtual void finish(int code);
};

class Debug
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
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
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void beginReport();
	virtual void slot25();
	virtual void slot26();
	virtual DebugStream &startReport(int a, int b, int c);
};
extern Debug *theDebug;

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
};

class BfmeStringRecord000B94D2
{
public:
	~BfmeStringRecord000B94D2();
	char pad[0x34];
};

class RadiusDecalTemplate : public BfmeStringRecord000B94D2
{
public:
	RadiusDecalTemplate();
	RadiusDecalTemplate(const RadiusDecalTemplate &other);
	RadiusDecalTemplate &operator=(const RadiusDecalTemplate &other);

	static void parseRadiusDecalTemplate(INI *ini, void *instance, void *store, const void *userData);
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return getFO()->m_name; }
private:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	char m_opaque000[0x10];
	AsciiString m_name;						// +0x10
};

class SpecialPowerModuleInterface
{
public:
	virtual void spmi00() = 0;
	virtual void spmi04() = 0;
	virtual void spmi08() = 0;
	virtual void spmi0C() = 0;
	virtual void spmi10() = 0;
	virtual void spmi14() = 0;
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const = 0;	// +0x18
};

class BehaviorModuleInterface
{
public:
	virtual void bmi00() = 0;
	virtual void bmi04() = 0;
	virtual void bmi08() = 0;
	virtual void bmi0C() = 0;
	virtual void bmi10() = 0;
	virtual void bmi14() = 0;
	virtual void bmi18() = 0;
	virtual void bmi1C() = 0;
	virtual SpecialPowerModuleInterface *getSpecialPower() const = 0;	// +0x20
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
private:
	char m_opaque004[0xC - 0x4];
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

enum ObjectStatusTypes { OBJECT_STATUS_UNDER_CONSTRUCTION = 2 };

class ThingTemplate
{
public:
	bool isKindOfCommandCenter() const { return (m_kindOf10A & 2) != 0; }
private:
	char m_opaque000[0x10A];
	unsigned char m_kindOf10A;				// +0x10A, KINDOF_COMMANDCENTER is bit 1
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }
	bool testStatus( ObjectStatusTypes bit ) const;
	bool isKindOfCommandCenter() const { return m_template->isKindOfCommandCenter(); }
private:
	void *m_vtbl;
	const ThingTemplate *m_template;		// +0x04
	char m_opaque008[0x74 - 0x8];
	ObjectID m_id;							// +0x74
	char m_opaque078[0x244 - 0x78];
	BehaviorModule **m_behaviors;			// +0x244
};

extern GameLogic *TheGameLogic;

// Address-named by-value getter of the template's required sciences (rowed
// in Rva0029FCB4.cpp: final override +0x24).
class Rva0029FCB4
{
public:
	ScienceVec rva0029FCB4();
};

class Player
{
public:
	bool hasAnyRequiredSciences( const ScienceVec &sciences ) const;
	int getPlayerColor() const { return m_color; }
private:
	char m_opaque000[0x280];
	int m_color;							// +0x280
};

class PlayerList
{
public:
	Player *getNthPlayer( int i );
};

extern PlayerList *ThePlayerList;

// The SuperweaponInfo ctor as rowed (Rva0029B816Ctor.cpp, address-named).
class Rva0029B816
{
public:
	Rva0029B816( int id, int timestamp, bool hiddenByScript, bool hiddenByScience, bool ready, const AsciiString &font, int pointSize, bool bold, int color, int powerTemplate );
private:
	char m_data[0x24];
};

class SuperweaponInfo
{
public:
	virtual ~SuperweaponInfo();
	__forceinline void deleteInstance() { ::delete this; }
	void *m_nameDisplayString;				// +0x04
	void *m_timeDisplayString;				// +0x08
	int m_color;							// +0x0C
	const SpecialPowerTemplate *m_powerTemplate;	// +0x10
	AsciiString m_powerName;				// +0x14
	ObjectID m_id;							// +0x18
	unsigned int m_timestamp;				// +0x1C
	bool m_hiddenByScript;					// +0x20
	bool m_hiddenByScience;					// +0x21
	bool m_ready;							// +0x22
};

enum { MAX_PLAYER_COUNT = 20 };

typedef _STL::list<SuperweaponInfo *> SuperweaponList;
typedef _STL::map<AsciiString, SuperweaponList> SuperweaponMap;

class InGameUI
{
public:
	virtual ~InGameUI();
#define SLOT(N) virtual void slot##N();
	SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08)
	SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16)
	SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
	SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32)
	SLOT(33)
#undef SLOT
	virtual void addSuperweapon( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate );	// slot 34
	virtual bool removeSuperweapon( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate );
	virtual void objectChangedTeam( const Object *obj, int oldPlayerIndex, int newPlayerIndex );
	virtual void slot37();
	virtual void slot38();
	virtual void hideObjectSuperweaponDisplayByScript( const Object *obj );	// slot 39
	virtual void showObjectSuperweaponDisplayByScript( const Object *obj );	// slot 40

	static void parseNamedRadiusDecalTemplate(INI *ini, void *instance, void *store, const void *userData);
protected:
	SuperweaponInfo *findSWInfo( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate );

	char m_opaque004[0x630 - 0x4];
	SuperweaponMap m_superweapons[MAX_PLAYER_COUNT];	// +0x630, one 12-byte map per player
	char m_opaque720[0x72C - 0x720];
	AsciiString m_superweaponNormalFont;	// +0x72C
	int m_superweaponNormalPointSize;		// +0x730
	bool m_superweaponNormalBold;			// +0x734
	char m_opaque735[0x874 - 0x735];
	_STL::hash_map<NameKeyType, RadiusDecalTemplate, rts::hash<NameKeyType> > m_radiusCursorTemplates;
};

// ?findSWInfo@InGameUI@@IAEPAVSuperweaponInfo@@HABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
SuperweaponInfo *InGameUI::findSWInfo( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate )
{
	SuperweaponMap::iterator mapIt = m_superweapons[playerIndex].find( powerName );
	if( mapIt != m_superweapons[playerIndex].end() )
	{
		for( SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt )
		{
			if( (*listIt)->m_id == id )
				return *listIt;
		}
	}
	return 0;
}

// ?addSuperweapon@InGameUI@@UAEXHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
void InGameUI::addSuperweapon( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate )
{
	if( powerTemplate == 0 )
		return;

	SuperweaponInfo *swInfo = findSWInfo( playerIndex, powerName, id, powerTemplate );
	if( swInfo != 0 )
		return;

	const Player *player = ThePlayerList->getNthPlayer( playerIndex );
	ScienceVec sciences = ((Rva0029FCB4 *)powerTemplate)->rva0029FCB4();
	bool hiddenByScience = !sciences.empty() && !player->hasAnyRequiredSciences( sciences );

	SuperweaponInfo *info = (SuperweaponInfo *)new Rva0029B816( id, -1, false, hiddenByScience, false,
		m_superweaponNormalFont, m_superweaponNormalPointSize, m_superweaponNormalBold,
		player->getPlayerColor(), (int)powerTemplate );

	m_superweapons[playerIndex][powerName].push_back( info );
}

// ?objectChangedTeam@InGameUI@@UAEXPBVObject@@HH@Z
void InGameUI::objectChangedTeam( const Object *obj, int oldPlayerIndex, int newPlayerIndex )
{
	// if we already had it listed, remove and re-add it
	if( obj && oldPlayerIndex >= 0 && newPlayerIndex >= 0 )
	{
		ObjectID id = obj->getID();
		AsciiString powerName;
		for( BehaviorModule **m = obj->getBehaviorModules(); *m; ++m )
		{
			SpecialPowerModuleInterface *sp = (*m)->getSpecialPower();
			if( !sp )
				continue;

			const SpecialPowerTemplate *powerTemplate = sp->getSpecialPowerTemplate();
			powerName = powerTemplate->getName();

			SuperweaponMap::iterator mapIt = m_superweapons[oldPlayerIndex].find( powerName );
			bool found = false;
			if( mapIt != m_superweapons[oldPlayerIndex].end() )
			{
				for( SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt )
				{
					if( (*listIt)->m_id == id )
					{
						removeSuperweapon( oldPlayerIndex, powerName, id, powerTemplate );
						addSuperweapon( newPlayerIndex, powerName, id, powerTemplate );
						found = true;
						break;
					}
				}
			}
			if( !found )
			{
				if( TheGameLogic->getFrame() == 0 && !obj->testStatus( OBJECT_STATUS_UNDER_CONSTRUCTION ) &&
					obj->isKindOfCommandCenter() == false )
					addSuperweapon( newPlayerIndex, powerName, id, powerTemplate );
			}
		}
	}
}

// ?removeSuperweapon@InGameUI@@UAE_NHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
bool InGameUI::removeSuperweapon( int playerIndex, const AsciiString &powerName, ObjectID id, const SpecialPowerTemplate *powerTemplate )
{
	SuperweaponMap::iterator mapIt = m_superweapons[playerIndex].find( powerName );
	if( mapIt != m_superweapons[playerIndex].end() )
	{
		SuperweaponList &swList = mapIt->second;
		for( SuperweaponList::iterator listIt = swList.begin(); listIt != swList.end(); ++listIt )
		{
			if( (*listIt)->m_id == id )
			{
				SuperweaponInfo *info = *listIt;
				swList.erase( listIt );
				info->deleteInstance();
				if( swList.size() == 0 )
					m_superweapons[playerIndex].erase( mapIt );
				return true;
			}
		}
	}
	return false;
}

// ?hideObjectSuperweaponDisplayByScript@InGameUI@@UAEXPBVObject@@@Z
void InGameUI::hideObjectSuperweaponDisplayByScript( const Object *obj )
{
	ObjectID objID = obj->getID();
	for( int playerIndex = 0; playerIndex < MAX_PLAYER_COUNT; ++playerIndex )
	{
		for( SuperweaponMap::iterator mapIt = m_superweapons[playerIndex].begin(); mapIt != m_superweapons[playerIndex].end(); ++mapIt )
		{
			for( SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt )
			{
				if( (*listIt)->m_id == objID )
					(*listIt)->m_hiddenByScript = true;
			}
		}
	}
}

// ?showObjectSuperweaponDisplayByScript@InGameUI@@UAEXPBVObject@@@Z
void InGameUI::showObjectSuperweaponDisplayByScript( const Object *obj )
{
	ObjectID objID = obj->getID();
	for( int playerIndex = 0; playerIndex < MAX_PLAYER_COUNT; ++playerIndex )
	{
		for( SuperweaponMap::iterator mapIt = m_superweapons[playerIndex].begin(); mapIt != m_superweapons[playerIndex].end(); ++mapIt )
		{
			for( SuperweaponList::iterator listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt )
			{
				if( (*listIt)->m_id == objID )
					(*listIt)->m_hiddenByScript = false;
			}
		}
	}
}

// ?parseNamedRadiusDecalTemplate@InGameUI@@SAXPAVINI@@PAX1PBX@Z
void InGameUI::parseNamedRadiusDecalTemplate(INI *ini, void *instance, void *store, const void *userData)
{
	AsciiString templateName;
	INI::parseAsciiString(ini, 0, &templateName, 0);

	NameKeyType key = TheNameKeyGenerator->nameToKey(templateName);
	InGameUI *ui = (InGameUI *)instance;

	typedef _STL::hash_map<NameKeyType, int, rts::hash<NameKeyType> > NameKeyIntMap;
	if (((const NameKeyIntMap *)&ui->m_radiusCursorTemplates)->find(key) != ((const NameKeyIntMap *)&ui->m_radiusCursorTemplates)->end())
	{
		if (bfmeRva000387C0())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->beginReport();
			theDebug->startReport(0, 0, 0).slot38("Error, duplicate RadiusCursorTemplate \"").slot38(templateName.str()).slot38("\" found in InGameUI.ini!").finish(2);
		}
	}

	RadiusDecalTemplate decal;
	RadiusDecalTemplate::parseRadiusDecalTemplate(ini, 0, &decal, 0);
	ui->m_radiusCursorTemplates[key] = decal;
}
