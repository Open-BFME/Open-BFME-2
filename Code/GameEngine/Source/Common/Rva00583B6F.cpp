// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// ?rva00583B6F@Rva00583B6F@@QAEXXZ RVA 0x00583B6F 119B
// Evidence: leaf lane; vtable slot 4 (0x10) of 0x0086FC80 (Rva005843DA) and
//   0x0086FD90 (Rva00586D8E twin); calls rowed Thing::setOrientation 0x0030AB9D
//   and Thing::setPosition 0x0030AA80; circular list walk with x87 float arg.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Thing
{
public:
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
};

class Rva00583B6FIface
{
public:
	virtual void f000(); virtual void f001(); virtual void f002(); virtual void f003();
	virtual void f004(); virtual void f005(); virtual void f006(); virtual void f007();
	virtual void f008(); virtual void f009(); virtual void f010(); virtual void f011();
	virtual void f012(); virtual void f013(); virtual void f014(); virtual void f015();
	virtual void f016(); virtual void f017(); virtual void f018(); virtual void f019();
	virtual void f020(); virtual void f021(); virtual void f022(); virtual void f023();
	virtual void f024(); virtual void f025(); virtual void f026(); virtual void f027();
	virtual void f028(); virtual void f029(); virtual void f030(); virtual void f031();
	virtual void f032(); virtual void f033(); virtual void f034(); virtual void f035();
	virtual void f036(); virtual void f037(); virtual void f038(); virtual void f039();
	virtual void f040(); virtual void f041(); virtual void f042(); virtual void f043();
	virtual void f044(); virtual void f045(); virtual void f046(); virtual void f047();
	virtual void f048(); virtual void f049(); virtual void f050(); virtual void f051();
	virtual void f052(); virtual void f053(); virtual void f054(); virtual void f055();
	virtual void f056(); virtual void f057(); virtual void f058(); virtual void f059();
	virtual void f060(); virtual void f061(); virtual void f062(); virtual void f063();
	virtual void f064(); virtual void f065(); virtual void f066(); virtual void f067();
	virtual void f068(); virtual void f069();
	virtual void vf70(struct Rva00583B6FBuf *buf);
};

class Rva00583B6FFlagObj
{
public:
	char m_pad[0x109];
	unsigned char m_b109;
};

struct Rva00583B6FPayload
{
	char m_pad0[4];
	Rva00583B6FFlagObj *m_flag; // +4
	char m_pad8[0x38 - 8];
	Coord3D m_pos; // +0x38
	float m_orient; // +0x44
};

struct Rva00583B6FNode
{
	Rva00583B6FNode *m_next; // +0
	int m_pad4;
	void *m_data; // +8
};

struct Rva00583B6FList
{
	Rva00583B6FNode *m_sentinel; // +0
};

struct Rva00583B6FBuf
{
	int m_0;
	Rva00583B6FList *m_list; // +4
	Thing *m_thing; // +8
};

class Rva00583B6FHeld
{
public:
	char m_pad0[8];
	Thing *m_thing; // +8
	char m_padC[0x20 - 0xC];
	Rva00583B6FIface m_iface; // +0x20
	char m_pad24[0x120 - 0x24];
	bool m_f120; // +0x120
};

class Rva00583B6F
{
public:
	void rva00583B6F();

private:
	char m_pad0[4]; // +0
	Rva00583B6FHeld *m_held; // +4
};

void Rva00583B6F::rva00583B6F()
{
	Rva00583B6FBuf buf;
	m_held->m_iface.vf70(&buf);
	buf.m_thing = m_held->m_thing;
	Rva00583B6FNode *node = buf.m_list->m_sentinel->m_next;
	if (node != buf.m_list->m_sentinel) {
		do {
			Rva00583B6FPayload *pl = (Rva00583B6FPayload *)node->m_data;
			if (pl != 0 && (pl->m_flag->m_b109 & 8) != 0) {
				buf.m_thing->setOrientation(pl->m_orient);
				buf.m_thing->setPosition(&pl->m_pos);
				m_held->m_f120 = true;
			}
			node = node->m_next;
		} while (node != buf.m_list->m_sentinel);
	}
}
