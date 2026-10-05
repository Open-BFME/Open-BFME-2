// cl: /O1 /DNDEBUG /MD
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
};

class GameLogic
{
public:
	void bindObjectAndDrawable( Object *obj, Drawable *draw );
};

void GameLogic::bindObjectAndDrawable(Object* obj, Drawable* draw)
{
	draw->friend_bindToObject( obj );
	obj->friend_bindToDrawable( draw );
}
