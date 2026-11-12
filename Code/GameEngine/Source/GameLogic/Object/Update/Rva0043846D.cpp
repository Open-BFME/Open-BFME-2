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

#include "../../../../Include/GameClient/Drawable.h"

extern int BfmeLogicFramesPerSecond;

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

// The converged retail slot is owned by GlobalData; this view supplies only
// the three offsets independently read by the target body.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva0043846DGlobalData
{
	char pad[0x11D0];
	float x;
	float y;
	unsigned int phase;
};

#include "../../../../Include/GameLogic/Module/Rva0043846D.h"

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
	Rva0043846DGlobalData *global = reinterpret_cast<Rva0043846DGlobalData *>(TheWritableGlobalData);
	float phase = (float)global->phase / BfmeLogicFramesPerSecond;
	drawable->rva00275DCE(mode, global->x, global->y, phase);
}
