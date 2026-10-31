// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272DBB@Drawable@@QAEXPAVObject@@@Z, retail 0x00272DBB, 51 bytes.
// Guarded draw-module walk: when the Object arg is non-null and
// isKindOf(0x45), walk this+0x14C modules calling slot 0xF4.
// Evidence: same +0x14C walk as Drawable siblings 0x00272393/0x002723C0/
// 0x002723ED; rowed ?isKindOf@Object@@QBE_NW4KindOfType@@@Z at 0x0006F039;
// unblocks 0x0027566B; caller at 0x002756F0.

#include "../../Include/GameClient/DrawableBFME2.h"
#include "DrawableFieldsView.h"
typedef bool Bool;
enum KindOfType;

class Object
{
public:
	Bool isKindOf(KindOfType kind) const;
};


void Drawable::rva00272DBB(Object *obj)
{
	if (obj == 0)
		return;
	if (!obj->isKindOf((KindOfType)0x45))
		return;
	DrawModule **modules =
		*reinterpret_cast<DrawModule ***>((unsigned char *)this + 0x14C);
	for (DrawModule **p = modules; *p; ++p)
		(*p)->slotF4();
}
