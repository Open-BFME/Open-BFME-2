// cl: /DNDEBUG /MD /EHsc
// ?Rva0043B2A4Clear@@YGXW4ObjectID@@H@Z @0x0043B2A4 44B
// Evidence: calls rowed findObjectByID 0x49DC5 getDrawable 0x5508E2 rva00271C79 0x271C79; TheGameLogic; callers 0x43B7BC 0x43B810 ret8.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class Drawable;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Rva00271C68
{
public:
	void rva00271C79(int value);
};

class Drawable : public Rva00271C68
{
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

void __stdcall Rva0043B2A4Clear(ObjectID id, int value)
{
	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj == 0)
		return;
	Drawable *d = obj->getDrawable();
	if (d == 0)
		return;
	d->rva00271C79(value);
}
