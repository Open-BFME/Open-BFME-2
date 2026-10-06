// cl: /DNDEBUG /MD
//
// ?bindObjectAndDrawable@GameLogic@@QAEXPAVObject@@PAVDrawable@@@Z retail
// 0x0023CD4A, 29 bytes: the Zero Hour GameLogic.cpp body, which a /O1 build
// places uniquely. Its two calls are the friend binders, pinned from these
// sites: Drawable::friend_bindToObject 0x00274240 (stores the object at
// Drawable +0xFC) and Object::friend_bindToDrawable 0x0029080C.

class Object;

class Drawable
{
public:
	void friend_bindToObject( Object *obj );
};

class Object
{
public:
	void friend_bindToDrawable( Drawable *draw );
	Drawable *getDrawable() const;
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

class GameLogic
{
public:
	void bindObjectAndDrawable( Object *obj, Drawable *draw );
	void sendObjectDestroyed( Object *obj );
};

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
