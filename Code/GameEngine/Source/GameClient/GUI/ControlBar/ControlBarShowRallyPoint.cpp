// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /DNDEBUG /MD /EHsc
// ?showRallyPoint@ControlBar@@QAEXPBUCoord3D@@@Z @0x0031B892 264B
// Named WB 0x00C2F300 and native 0x0031B892..0x0031B99A establish
// the identity, dispatch slots and accessed fields. Clean BFME1 ba7ddda7
// ControlBar.cpp supplies the workflow; the old bank supplies its BFME2
// field adaptation. The original nested destroy/find expression preserves
// native vtable evaluation order. Global pointer declarations agree with
// GameClient.cpp, ThingFactory.cpp and PlayerList.cpp actual providers.
#include "ascii_string.h"
#include "Lib/Coord3D.h"

class Drawable
{
public:
	void setPosition(const Coord3D *loc);
	void setIndicatorColor(int color);
};

class Thing
{
public:
	void setOrientation(float angle);
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};

class Rva002CF21B
{
public:
	void *rva002CF21B(void *tmplate, int a, int b);
};

class ThingFactory;
extern ThingFactory *TheThingFactory;

class Rva0055A88BDwordField
{
public:
	int get() const;
};

typedef unsigned int DrawableID;

class RallyGameClientDispatchView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual Drawable *findDrawableByID(DrawableID id);
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot1A(); virtual void slot1B(); virtual void slot1C();
	virtual void destroyDrawable(Drawable *draw);
};

class GameClient;
extern GameClient *TheGameClient;

struct RallyGlobalDataView
{
	char m_pad00[0x94];
	float m_downwindAngle;
	char m_pad98[0x134 - 0x98];
	int m_timeOfDay;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct PlayerColors
{
	char m_pad00[0x280];
	int m_playerColor;
	int m_playerNightColor;
};

struct RallyPlayerListView
{
	char m_pad00[0x10];
	PlayerColors *m_local;
};

class PlayerList;
extern PlayerList *ThePlayerList;

struct DrawableWithStatus
{
	char m_pad00[0x114];
	unsigned int m_status;
};

class ControlBar
{
public:
	void showRallyPoint(const Coord3D *loc);
private:
	char m_pad00[0x74];
	int m_rallyPointDrawableID;
};

void ControlBar::showRallyPoint(const Coord3D *loc)
{
	if (loc == 0)
	{
		if (m_rallyPointDrawableID != 0)
		{
			((RallyGameClientDispatchView *)TheGameClient)->destroyDrawable(((RallyGameClientDispatchView *)TheGameClient)->findDrawableByID(m_rallyPointDrawableID));
			m_rallyPointDrawableID = 0;
		}
	}
	else
	{
		Drawable *marker = 0;
		if (m_rallyPointDrawableID == 0)
		{
			const void *ttn;
			{
				AsciiString markerName("RallyPointMarker");
				ttn = (const void *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&markerName);
			}
			marker = (Drawable *)((Rva002CF21B *)TheThingFactory)->rva002CF21B((void *)ttn, 0, -1);
			if (marker)
			{
				((DrawableWithStatus *)marker)->m_status |= 0x10;
				m_rallyPointDrawableID = ((Rva0055A88BDwordField *)marker)->get();
			}
		}
		else
		{
			marker = ((RallyGameClientDispatchView *)TheGameClient)->findDrawableByID(m_rallyPointDrawableID);
		}
		if (marker)
		{
			marker->setPosition(loc);
			((Thing *)marker)->setOrientation(((RallyGlobalDataView *)TheWritableGlobalData)->m_downwindAngle);
			PlayerColors *player = ((RallyPlayerListView *)ThePlayerList)->m_local;
			if (((RallyGlobalDataView *)TheWritableGlobalData)->m_timeOfDay == 4)
				marker->setIndicatorColor(player->m_playerNightColor);
			else
				marker->setIndicatorColor(player->m_playerColor);
		}
	}
}
