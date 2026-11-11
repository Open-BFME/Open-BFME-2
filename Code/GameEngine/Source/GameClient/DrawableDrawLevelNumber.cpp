// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva002778E1@Drawable@@QAEXXZ retail 0x002778E1 (237B): draws a numeral
// over the drawable's icon anchor in the manner of Zero Hour's
// drawGroupNumber. The anchor (0x002775C9) is projected by TheTacticalView
// (+0x160, zero means on screen); the owning object (+0xFC) must answer the
// unrowed 0x0028D900 query; the numeral is TheDisplayStringManager's
// string (+0x40) for min(object +0x04 record's +0x0C count + 1, 9), scaled
// 2.0 x 1.5 (+0x44), coloured with the controlling player's +0x280 colour
// on frames where (TheGameClient frame (+0x7C) + count) & 0xA, else -1, over
// an opaque black drop colour (+0x28), drawn at the screen point with
// TheDrawGroupInfo's +0x14/+0x18 offsets (+0x38) and scaled back to 1 x 1.
// Views follow DrawableDrawVeterancy.cpp; slot names are inferred.
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../Include/GameClient/View.h"
extern View *TheTacticalView;

#include "../../Include/GameClient/DisplayString.h"

class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual DisplayString *getNumeralString(Int number); // +0x40
};
extern DisplayStringManager *TheDisplayStringManager;

#include "../../Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;

struct DrawGroupInfo
{
	char m_pad00[0x14];
	Int m_dropShadowOffsetX; // +0x14
	Int m_dropShadowOffsetY; // +0x18
};
extern DrawGroupInfo *TheDrawGroupInfo;

#include "../../Include/Common/Player.h"

struct ObjectLevelRecord
{
	char m_pad00[0x0C];
	Int m_count; // +0x0C
};

class Object
{
public:
	Bool rva0028D900(Real *a, Real *b);
	Player *getControllingPlayer() const;
	const ObjectLevelRecord *getLevelRecord() const { return m_record; }
private:
	void *m_vtable;
	const ObjectLevelRecord *m_record; // +0x04
};

#include "../../Include/GameClient/Drawable.h"

void Drawable::rva002778E1()
{
	Object *obj = m_object;
	Coord3D pos;
	ICoord2D screen;
	rva002775C9(&pos);
	if (TheTacticalView->worldToScreenTriReturn(&pos, &screen) != 0)
		return;

	Real a, b;
	if (!obj->rva0028D900(&a, &b))
		return;

	Int count = obj->getLevelRecord()->m_count;
	Int number = count + 1;
	if (number > 9)
		number = 9;
	DisplayString *string = TheDisplayStringManager->getNumeralString(number);
	if (string == 0)
		return;

	string->slot17(2.0f, 1.5f);
	Int color;
	if ((TheGameClient->getFrame() + count) & 0xA)
		color = obj->getControllingPlayer()->getPlayerColor();
	else
		color = -1;
	string->setColors(color, 0xFF000000);
	string->draw(screen.x, screen.y, TheDrawGroupInfo->m_dropShadowOffsetX, TheDrawGroupInfo->m_dropShadowOffsetY);
	string->slot17(1.0f, 1.0f);
}
