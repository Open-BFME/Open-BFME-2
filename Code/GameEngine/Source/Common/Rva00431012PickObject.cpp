// cl: /DNDEBUG /MD
// ?Rva00431012PickObject@@YAPAVObject@@PAUICoord2D@@PAVRva0035AFE4@@H@Z @0x00431012 69B
// Screen-pick helper (cdecl, 3 args): TheTacticalView slot 9 (pickDrawable(pixel, false,
// pickType), ZH View::pickDrawable) -> Drawable+0xFC object; keeps the object only if
// the relationship-mask predicate 0x0035B010 (local player, object) accepts it.
// Evidence: retail bytes; TheTacticalView 0xDFEA3C and ThePlayerList 0xDFEEE8 +0x10 local
// per ledger neighbours; rowed predicate 0x0035B010 (caller 0x00431048).
struct ICoord2D
{
	int m_x;
	int m_y;
};

class Player;
class Object;

class Rva0035AFE4
{
public:
	bool rva0035B010(Player *p, Object *o);
};

class Drawable
{
public:
	char m_pad[0xFC];
	Object *m_object;
};

class TacticalView
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
	virtual Drawable *pickDrawable(const ICoord2D *pixel, bool forceAttack, int pickType);
};

class PlayerList
{
public:
	unsigned char m_pad00[0x10];
	Player *m_localPlayer;
};

extern TacticalView *TheTacticalView;
extern PlayerList *ThePlayerList;

Object *__cdecl Rva00431012PickObject(ICoord2D *pixel, Rva0035AFE4 *mask, int pickType)
{
	Object *obj = 0;
	Drawable *d = TheTacticalView->pickDrawable(pixel, false, pickType);
	if (d != 0 && d->m_object != 0)
	{
		Player *local = ThePlayerList->m_localPlayer;
		obj = d->m_object;
		if (!mask->rva0035B010(local, obj))
			obj = 0;
	}
	return obj;
}
