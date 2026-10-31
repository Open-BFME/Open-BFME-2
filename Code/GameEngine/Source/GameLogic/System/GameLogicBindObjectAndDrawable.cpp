// cl: /DNDEBUG /MD
//
// ?bindObjectAndDrawable@GameLogic@@QAEXPAVObject@@PAVDrawable@@@Z retail
// 0x0023CD4A, 29 bytes: the Zero Hour GameLogic.cpp body, which a /O1 build
// places uniquely. Its two calls are the friend binders, pinned from these
// sites: Drawable::friend_bindToObject 0x00274240 (stores the object at
// Drawable +0xFC) and Object::friend_bindToDrawable 0x0029080C.

#include "../../Common/GameLogicObjectLookupView.h"
#include "../../Common/Thing/thing.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_0x37 = 0x37 };
class Module;
class Drawable;
class Player;

class Drawable
{
public:
	void friend_bindToObject( Object *obj );
	void rva00270FAC(bool value);
};

class Object : public Thing, public Snapshot
{
public:
	void rva0028ACEE(int a, int b);
protected: Module *findModule(NameKeyType) const;
public: Module *lookupModule(NameKeyType key) const {return findModule(key);}
	bool isMassSelectable() const;
	Drawable *getDrawable() const;
	Player *getControllingPlayer() const;
	void *rva0028BD3A() const;
	void rva0029041B(Player *player);
	void rva00290496(Player *player);
	void friend_bindToDrawable( Drawable *draw );
	void rva0028B31A(int val);
	bool testStatus(ObjectStatusTypes status) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_next; }

	char m_pad64[0x74 - 0x64];
	ObjectID m_id; // +0x74
	char m_pad78[0x8C - 0x78];
	Object *m_next; // +0x8C
};

// sendObjectDestroyed reaches GameClient::destroyDrawable through slot 0x74 of
// TheGameClient (0x00DFE77C).
class GameClient
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28();
	virtual void destroyDrawable( Drawable *draw );
};

extern GameClient *TheGameClient;

void GameLogic::bindObjectAndDrawable(Object* obj, Drawable* draw)
{
	draw->friend_bindToObject( obj );
	obj->friend_bindToDrawable( draw );
}

// ?sendObjectDestroyed@GameLogic@@QAEXPAVObject@@@Z retail 0x0023CD67, 48
// bytes: the Zero Hour body right after bindObjectAndDrawable (as in
// GameLogic.cpp), its getDrawable the pinned Object::getDrawable 0x005508E2.
void GameLogic::sendObjectDestroyed( Object *obj )
{
	// Because this implementation is a bridge between the Logic and Interface,
	// we must take extra care to handle such cases as when the system it
	// shutting down.
	if(TheGameClient == 0)
		return;

	// destroy the drawable
	Drawable *draw = obj->getDrawable();
	if(draw)
	{
		TheGameClient->destroyDrawable( draw );
	}

	// erase the binding of the drawable to this object
	obj->friend_bindToDrawable( 0 );

}
