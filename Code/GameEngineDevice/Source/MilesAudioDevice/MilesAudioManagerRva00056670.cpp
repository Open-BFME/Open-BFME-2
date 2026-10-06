// cl: /Ireference/shims/bfme2_ascii /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva00056670@MilesAudioManager@@QAE_NW4ObjectID@@@Z @0x00056670 70B chain: calls 0x00054899 just landed
// Evidence: calls rowed findObjectByID 0x00049DC5 via TheGameLogic ?TheGameLogic@@3PAVGameLogic@@A plus getDrawable 0x005508E2 plus dword getter 0x0055A88B plus rva00054899 0x00054899; prev 0x00056634 next 0x000566B6 MilesAudioManager.
enum ObjectID
{
	ObjectID_Zero = 0
};

class Object;
class Drawable;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
};

class Rva0055A88BDwordField
{
public:
	int get() const;
};

extern GameLogic *TheGameLogic;

class MilesAudioManager
{
public:
	bool rva00054899(ObjectID arg1, int arg2);
	bool rva00056670(ObjectID id);
};

bool MilesAudioManager::rva00056670(ObjectID id)
{
	if (!id)
		return false;
	Object *obj = TheGameLogic->findObjectByID(id);
	int val = 0;
	if (obj)
	{
		Drawable *d = obj->getDrawable();
		if (d)
			val = ((Rva0055A88BDwordField *)d)->get();
	}
	return rva00054899(id, val);
}
