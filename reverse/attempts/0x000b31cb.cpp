// ?rva000B31CB@Rva000B31CB@@QAEXIH@Z
// partial score=0.9 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
//
// ?rva000B31CB@Rva000B31CB@@QAEXIH@Z, retail 0x000B31CB, 155 bytes, ret 8.
// W3D draw radius-decal creation sibling of 0x000B508A / 0x000B3271: when the global flag
// at +0x9A5 is set and the owning object (Drawable+0xFC) belongs to the local player
// (ThePlayerList +0x10, skipped when there is no list), it takes the scale default (global
// float 0x00BC5CCC) or the float at +0x20 of the record behind +0x14/+0xDC, reads the
// object's visual position through the rowed 0x0028D4E0 into the by-value Coord3D and calls
// the rowed RadiusDecalTemplate creator 0x0033121F on the template at +0x1E0 with the decal
// at +0x1D0. Evidence: target bytes and the rowed callees; names are neutral views.
class Object;
// Private view of the canonical Coord3D: the constructor takes the visual position straight
// into the by-value argument slot, as the retail call does.
struct Coord3D
{
	float x;
	float y;
	float z;
	Coord3D(Object *object);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
class PlayerList;
extern PlayerList *ThePlayerList;
class Player;

struct Rva000B31CBGlobals
{
	char m_pad[0x9A5];
	unsigned char m_flag9A5;
};

struct Rva000B31CBPlayerList
{
	char m_pad[0x10];
	Player *m_local;
};

class RadiusDecal
{
public:
	char m_data[16];
};

class RadiusDecalTemplate
{
public:
	void rva0033121F(Coord3D pos, unsigned selected, int color, RadiusDecal *out, float scale);
};

class Object
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
	virtual const Coord3D *rva0028D4E0(Coord3D *out, Coord3D *normal);
	Player *getControllingPlayer() const;
};

class Drawable
{
public:
	char m_pad[0xFC];
	Object *m_object;
};

struct Rva000B31CBScale
{
	char m_pad[0x20];
	float m_scale20;
};

struct Rva000B31CBHolder
{
	char m_pad[0xDC];
	Rva000B31CBScale *m_scaleSource;
};

class Rva000B31CB
{
public:
	void rva000B31CB(unsigned int selected, int color);
private:
	int m_pad0;
	int m_pad4;
	Drawable *m_drawable;
	char m_padC[8];
	Rva000B31CBHolder *m_holder;
	char m_pad18[0x1D0 - 0x18];
	RadiusDecal m_decal;
	RadiusDecalTemplate m_template;
};

__forceinline Coord3D::Coord3D(Object *object)
{
	object->Object::rva0028D4E0(this, 0);
}

void Rva000B31CB::rva000B31CB(unsigned int selected, int color)
{
	if (!((Rva000B31CBGlobals *)TheWritableGlobalData)->m_flag9A5)
		return;
	Object *object = m_drawable->m_object;
	if (!object)
		return;
	if (ThePlayerList)
	{
		Player *local = ((Rva000B31CBPlayerList *)ThePlayerList)->m_local;
		if (object->getControllingPlayer() != local)
			return;
	}
	float scale = 1.0f;
	if (m_holder)
	{
		Rva000B31CBScale *source = m_holder->m_scaleSource;
		if (source)
			scale = source->m_scale20;
	}
	m_template.rva0033121F(Coord3D(object), selected, color, &m_decal, scale);
}
