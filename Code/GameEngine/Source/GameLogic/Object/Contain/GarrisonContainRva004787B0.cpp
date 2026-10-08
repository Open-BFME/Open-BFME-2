// cl: /DNDEBUG /MD /EHsc
// ?rva004787B0@GarrisonContain@@QAEXXZ @0x004787B0 160B.
// Slot 5 (offset 0x14) of GarrisonContain 0x008461F8, HordeGarrisonContain
// 0x00846570, TunnelContain 0x00847740 and siblings: shared base spawn.
// Reads count at [this+4]+0xA8 and name at +0xA4 via rowed Rva002D06CA
// through g_009FF000, then creates count Objects via rowed ThingFactory
// newObject with the controlling player's team at +0x2EC and a zeroed
// 0x10 CreateMask, driving Object+0x250 slots 0x98/0x9C. Evidence: vtable
// slot 5 shared across Contain family, callee rows 0x002D06CA 0x0028AFA9
// 0x002D0A23 and import memset 0x006291AE, prev/next TU flags.
class AsciiString;
class ThingTemplate;
class Team;
class Player
{
public:
	char m_pad[0x2EC];
	Team *m_team;
};
class Object;
class Payload
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual bool v38(Object *obj, int a, int b);
	virtual void v39(Object *obj);
};
class Object
{
public:
	virtual ~Object();
	Player *getControllingPlayer() const;
private:
	char m_pad[0x250 - 4];
public:
	Payload *m_250;
};
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};
extern class ThingFactory *TheThingFactory;
struct CreateMask
{
	unsigned char m_data[0x10];
};
class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};
extern "C" void *__cdecl memset(void *dst, int val, unsigned int size);
struct HolderData
{
	char m_pad[0xA4];
	int m_nameOpaque;
	int m_count;
};
class GarrisonContain
{
public:
	virtual ~GarrisonContain();
	void rva004787B0();
private:
	HolderData *m_4;
	Object *m_8;
};
void GarrisonContain::rva004787B0()
{
	HolderData *a = m_4;
	int count = a->m_count;
	if (count <= 0)
		return;
	void *tmpl = ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)&a->m_nameOpaque);
	Object *obj = m_8;
	CreateMask mask;
	for (int i = 0; i < count; ++i)
	{
		memset(&mask, 0, 0x10);
		Player *player = obj->getControllingPlayer();
		Team *team = player->m_team;
		Object *created = ((ThingFactory *)TheThingFactory)->newObject((const ThingTemplate *)tmpl, team, &mask, false);
		Payload *p = obj->m_250;
		if (p)
		{
			if (p->v38(created, 1, 0))
				obj->m_250->v39(created);
		}
	}
}
