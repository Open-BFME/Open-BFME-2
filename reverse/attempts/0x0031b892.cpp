// ?showRallyPoint@ControlBar@@QAEXPBUCoord3D@@@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?showRallyPoint@ControlBar@@QAEXPBUCoord3D@@@Z @0x0031B892 264B
// Evidence: ZH donor ControlBar.cpp showRallyPoint plus BFME1 ControlBar.cpp BfmeRallyPoint shape; RallyPointMarker literal plus Drawable setPosition setOrientation setIndicatorColor plus +0x74 id plus +0x114 status plus caller 0x0031C042.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

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

extern Rva002D06CA *g_009FF000;

class Rva0055A88BDwordField
{
public:
	int get() const;
};

typedef unsigned int DrawableID;

class ClientFrameSubsystem
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

extern ClientFrameSubsystem *TheGameClient;

struct GlobalData
{
	char m_pad00[0x94];
	float m_downwindAngle;
	char m_pad98[0x134 - 0x98];
	int m_timeOfDay;
};

extern GlobalData *TheWritableGlobalData;

struct PlayerColors
{
	char m_pad00[0x280];
	int m_playerColor;
	int m_playerNightColor;
};

struct PlayerList
{
	char m_pad00[0x10];
	PlayerColors *m_local;
};

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

// ?showRallyPoint@ControlBar@@QAEXPBUCoord3D@@@Z present-unmatched
void ControlBar::showRallyPoint(const Coord3D *loc)
{
	if (loc == 0)
	{
		if (m_rallyPointDrawableID != 0)
		{
			Drawable *found = TheGameClient->findDrawableByID(m_rallyPointDrawableID);
			TheGameClient->destroyDrawable(found);
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
				ttn = (const void *)g_009FF000->rva002D06CA(&markerName);
			}
			marker = (Drawable *)((Rva002CF21B *)g_009FF000)->rva002CF21B((void *)ttn, 0, -1);
			if (marker)
			{
				((DrawableWithStatus *)marker)->m_status |= 0x10;
				m_rallyPointDrawableID = ((Rva0055A88BDwordField *)marker)->get();
			}
		}
		else
		{
			marker = TheGameClient->findDrawableByID(m_rallyPointDrawableID);
		}
		if (marker)
		{
			marker->setPosition(loc);
			((Thing *)marker)->setOrientation(TheWritableGlobalData->m_downwindAngle);
			PlayerColors *player = ThePlayerList->m_local;
			if (TheWritableGlobalData->m_timeOfDay == 4)
				marker->setIndicatorColor(player->m_playerNightColor);
			else
				marker->setIndicatorColor(player->m_playerColor);
		}
	}
}
