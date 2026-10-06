// cl: /DNDEBUG /MD
//
// ?rva0037441E@Rva0037441E@@QAEXXZ @0x0037441E 80B.
// BehaviorModule method: m_object at +8 null-checked, module data +0x10
// tested via rowed ?test@Rva00331682Holder 0x00331682 at Object+0x94,
// controlling player via rowed ?getControllingPlayer@Object 0x0028AFA9
// compared to ThePlayerList+0x10, drawable via rowed ?getDrawable@Thing
// 0x005508E2 null-checked, then float g_Va00BBB8D8 to Drawable+0x358.
// Evidence: packet callees all rowed, prev/next Rva003743CF/Rva00373EC6
// show BehaviorModule layout +4/+8, ThePlayerList and g_Va00BBB8D8 names
// from packet externs in use.
class Rva00331682Holder
{
public:
	bool test(const void *other) const;
};

class Player;
class Drawable
{
public:
	unsigned char m_pad[0x358];
	float m_358;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class PlayerList
{
public:
	unsigned char m_pad[0x10];
	Player *m_10;
};

extern PlayerList *ThePlayerList;
extern float g_Va00BBB8D8;

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad[0x94];
	Rva00331682Holder m_holder;
};

class Rva0037441EModuleData
{
public:
	unsigned char m_pad[0x10];
	int m_vals[4];
};

class Rva0037441E
{
public:
	void rva0037441E();
private:
	const void *m_00;
	const Rva0037441EModuleData *m_moduleData;
	Object *m_object;
};

void Rva0037441E::rva0037441E()
{
	Object *object = m_object;
	if (object == 0)
		return;
	const void *other = (const void *)((const char *)m_moduleData + 0x10);
	if (!object->m_holder.test(other))
		return;
	Player *expected = ThePlayerList->m_10;
	Player *actual = object->getControllingPlayer();
	if (actual != expected)
		return;
	Drawable *drawable = ((Thing *)object)->getDrawable();
	if (drawable == 0)
		return;
	drawable->m_358 = g_Va00BBB8D8;
}
