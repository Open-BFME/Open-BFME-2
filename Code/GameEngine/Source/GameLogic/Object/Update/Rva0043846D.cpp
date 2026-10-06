// cl: /O1 /DNDEBUG /MD /GX-
// ?rva0043846D@Rva0043846D@@QAEXPAVObject@@@Z @0x0043846D (133B):
// Target Ghidra boundary is 133 bytes; disassembly ends exactly at ret 4.
// Thiscall body checks the Object flag byte at +0x119, conditionally asks
// Object::rva002931F5(false), requires its Drawable getter, calls the rowed
// 0x004383EB helper with the same this pointer and Object, then passes that
// result plus GlobalData coordinates +0x11D0/+0x11D4 and unsigned +0x11D8 / 5
// to the Drawable method at 0x00275DCE. The outer class and function name are
// address-derived; exact identity is unknown.
struct Rva0043846DObjectFlags
{
	char pad[0x115];
	unsigned char flags;
};

class Drawable
{
public:
	void rva00275DCE(int mode, float x, float y, float phase);
};

extern int g_00DBA4E4;

class Object
{
public:
	Object *rva002931F5(bool checkProducer);
	Drawable *getDrawable() const;
	char pad[4];
	Rva0043846DObjectFlags *m_flags;
};

class Rva004383EB
{
public:
	int rva004383EB(Object *obj);
};

struct Rva0043846DGlobalData
{
	char pad[0x11D0];
	float x;
	float y;
	unsigned int phase;
};

class Rva0043846D
{
public:
	void rva0043846D(Object *obj);
};

void Rva0043846D::rva0043846D(Object *obj)
{
	if (obj == 0)
		return;
	if ((obj->m_flags->flags & 0x20) == 0 && obj->rva002931F5(false) != 0)
		return;
	Drawable *drawable = obj->getDrawable();
	if (drawable == 0)
		return;
	int mode = reinterpret_cast<Rva004383EB *>(this)->rva004383EB(obj);
	Rva0043846DGlobalData *global = *(Rva0043846DGlobalData *const *)0x00DFE758;
	float phase = (float)global->phase / g_00DBA4E4;
	drawable->rva00275DCE(mode, global->x, global->y, phase);
}
