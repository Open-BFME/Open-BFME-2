// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x00397F45, 166B: the castle's isPlayerAllowedToPackOrUnpack (named
// by retail's own CAMP log string at 0x00C1A600). True when the player
// already controls the castle object (this+8) or when 0x003973EB allows it;
// with the logic random log enabled (TheGameLogic+0x1B4 > 0 and the log file
// open) it first prints the frame (+0x40), the castle's override name
// (Object+4 -> +0x64), its id (+0x74), the caller's player name (+0x4C) and
// both flags. Shapes as the sibling canUnpack 0x00395F57
// (Code/GameEngine/Source/Common/Rva00395F57CanUnpack.cpp). Owner class name
// not established: address-derived.

#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Common/GameLogicObjectLookupView.h"

typedef int Int;
enum NameKeyType { NK_UNKNOWN = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Module;
class Rva00397FEBInterface;

extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

class Player
{
public:
	char m_pad00[0x4C];
	AsciiString m_name;
};

struct ChainValue
{
	char m_pad00[0x64];
	AsciiString m_value;
	char m_pad68[0x11A - 0x68];
	unsigned char m_flags11A;
};

void *__cdecl rva00397FEB(void *context, unsigned int id, void *target, int mode);

class Object
{
	friend void *__cdecl rva00397FEB(void *context, unsigned int id, void *target, int mode);
protected:
	Module *findModule(NameKeyType) const;
public:
	Player *getControllingPlayer() const;
	void *rva0028BCF4() const;
	void *m_pad00;
	ChainValue *m_chain;
	char m_pad08[0x30];
	Coord3D m_position;
	char m_pad44[0x30];
	Int m_id;
};

extern GameLogic *TheGameLogic;
extern "C" void *theLogicRandomLogFile;

class Rva003973EB
{
public:
	bool rva003973EB(Player *player, Int arg);
};

class Rva00397F45
{
public:
	bool rva00397F45(Player *player, Int arg);

private:
	void *m_vtable;
	const void *m_moduleData;
	Object *m_object;
};

bool Rva00397F45::rva00397F45( Player *player, Int arg )
{
	Object *object = m_object;
	bool alreadyMyCastle = ( player == object->getControllingPlayer() );
	bool playerAllowed = ((Rva003973EB *)this)->rva003973EB( player, arg );

	if( *(const Int *)( (const char *)TheGameLogic + 0x1B4 ) > 0 && theLogicRandomLogFile != 0 )
	{
		const char *playerName = object->getControllingPlayer()->m_name.str();
		Int id = object->m_id;
		const char *castleName = object->m_chain->m_value.str();
		fprintf( theLogicRandomLogFile,
			"CAMP: Frame %d: Castle %s(%d) ::isPlayerAllowedToPackOrUnpack() called by %s -- alreadyMyCastle=%d, playerAllowedToCapture=%d",
			TheGameLogic->getFrame(), castleName, id, playerName,
			alreadyMyCastle, playerAllowed );
	}

	return alreadyMyCastle ? true : playerAllowed;
}

// Native helper 397FEB..3980BF: callers supply four cdecl words. The
// template bit, CastleMemberBehavior key, member +14 and interface slots
// are native evidence; BFME1 createOwnedObject corroborates the factory
// relationship but does not establish the interface's original class name.
class Module { public: char m_pad00[0x14]; void *m_pending; };
class BfmeItemE63 { public: bool checkValid(); };
class Rva00397FEBInterface
{
public:
 virtual void unused0();
 virtual void unused1();
 virtual void unused2();
 virtual bool query();
 virtual void *create(Object *, void *, const Coord3D *, float, Player *, int);
};

void *__cdecl rva00397FEB(void *context, unsigned int id, void *target, int mode)
{
 Object *object = TheGameLogic->findObjectByID((ObjectID)id);
 if (!object || (object->m_chain->m_flags11A & 0x40)) return 0;
 static NameKeyType key = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
 Module *module = object->findModule(key);
 if (!(unsigned char)mode && module && module->m_pending &&
     ((BfmeItemE63 *)module)->checkValid()) return 0;
 Rva00397FEBInterface *factory = (Rva00397FEBInterface *)object->rva0028BCF4();
 if (!factory || factory->query()) return 0;
 return factory->create(object, target, &object->m_position, 0.0f,
                        object->getControllingPlayer(), mode);
}
