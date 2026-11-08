// cl: /O1 /DNDEBUG /MD /EHsc
// ?CanSelectDrawable@@YA_NPBVDrawable@@_N@Z @0x0042FA63 300B: selection gate for selectFriends. Evidence: donor SelectionXlatCanSelectDrawable plus retail callers 0x0042FE95 0x00430F98, rowed callees, TheWindowManager TheTacticalView.
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Include/GameClient/View.h"

enum ObjectStatusTypes;
enum KindOfType;

#include "../../../Include/Common/ThingTemplate.h"

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isKindOf(KindOfType kind) const;
	Bool isSelectable() const;
	Bool isLocallyControlled() const;

public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	int m_id;
	unsigned char m_pad78[0x438 - 0x78];
	unsigned char m_priv438;
	unsigned char m_sup439;
};

#include "../../../Include/GameClient/Drawable.h"

class Rva00270260
{
public:
	Bool rva00270260();
};


#include "../../../Include/GameClient/Bfme2GameWindow.h"


extern View *TheTacticalView;

#include "../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

Bool CanSelectDrawable(const Drawable *draw, Bool dragSelecting)
{
	if (draw == 0 || draw->m_object == 0)
		return false;
	const Object *obj = draw->m_object;
	if ((obj->m_priv438 & 1) != 0)
	{
		ThingTemplate *thingTemplate = obj->m_template;
		if (thingTemplate->m_keepSelectableWhenDead == 0)
		{
			if ((thingTemplate->m_kindof[1] & (1U << 26)) == 0)
				return false;
		}
	}
	{
		ThingTemplate *thingTemplate = obj->m_template;
		if ((thingTemplate->m_kindof[0] & 2) == 0)
		{
			if ((thingTemplate->m_kindof[2] & (1U << 4)) != 0)
				return false;
		}
		if ((thingTemplate->m_kindof[4] & (1U << 6)) != 0)
			return false;
	}
	if (((Rva00270260 *)draw)->rva00270260())
		return false;
	GameWindow *window = 0;
	if (TheWindowManager != 0)
	{
		const Coord3D *pos = ((Drawable *)draw)->getPosition();
		ICoord2D screen;
		TheTacticalView->worldToScreenTriReturn(pos, &screen);
		window = TheWindowManager->getWindowUnderCursor(screen.x, screen.y, false);
	}
	while (window != 0)
	{
		if ((window->winGetStatus() & 0x10000) == 0)
			return false;
		window = window->winGetParent();
	}
	if (dragSelecting)
	{
		UnsignedInt f = obj->m_template->m_kindof[0];
		if ((f & 0x80) != 0)
			return false;
		if ((f & 0x4000) != 0)
		{
			if (obj->isKindOf((KindOfType)0x49))
				return false;
		}
	}
	if (obj->testStatus((ObjectStatusTypes)3))
		return false;
	if (obj->m_sup439 != 0)
		return false;
	if (!obj->isSelectable())
		return false;
	if (dragSelecting && !obj->isLocallyControlled())
		return false;
	return true;
}
