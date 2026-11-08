// cl: /DNDEBUG /MD
//
// ?setProducer@Object@@QAEXPAV1@@Z,
// retail 0x0028AFD2, 21 bytes. Dedicated TU.
// Stores the producer's object ID (Object+0x74) into this+0x78, or zero when
// given null. Proven by the SpawnBehavior::onDie body at 0x0045F7B5 (push 0 +
// call) per the BFME1 donor SpawnBehavior.cpp:170, plus 31 further raw
// callers game-wide. Sibling at 0x0028AFE7 writes the same ID to +0x7C.

typedef int Color;

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/TeamBFME2.h"

#include "../../../Include/GameClient/Drawable.h"

enum TimeOfDay
{
	TIME_OF_DAY_NIGHT = 4
};

#include "../../../Include/Common/GlobalData.h"
extern class GlobalData *TheWritableGlobalData;

inline Color GameMakeColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

class Object
{
public:
	void setProducer(Object *producer);
	void setBuilder(const Object *producer);
	void setCustomIndicatorColor(Color c);
	void removeCustomIndicatorColor();
	Color getIndicatorColor() const;
	Color getNightIndicatorColor() const;
	void rva0028D253();

	__declspec(dllimport) __forceinline const Team *getTeam() const { return m_team; }

private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
	ObjectID m_producerID; // +0x78
	ObjectID m_7C; // +0x7C (sibling target at 0x0028AFE7)
	unsigned char m_pad80[0x84 - 0x80];
	Drawable *m_drawable; // +0x84
	unsigned char m_pad88[0x304 - 0x88];
	Team *m_team; // +0x304 (rowed getControllingPlayer 0x0028AFA9)
	unsigned char m_pad308[0x30C - 0x308];
	Color m_indicatorColor; // +0x30C
};

// ?setProducer@Object@@QAEXPAV1@@Z
void Object::setProducer(Object *producer)
{
	m_producerID = producer ? producer->m_id : (ObjectID)0;
}

void Object::setBuilder(const Object *producer)
{
	m_7C = producer ? producer->m_id : (ObjectID)0;
}

// The four indicator-color bodies follow setBuilder in Zero Hour's
// Object.cpp and in retail: setCustomIndicatorColor 0x0028AFFC (34B),
// removeCustomIndicatorColor 0x0028B01E (8B), getIndicatorColor 0x0028B026
// (42B) and getNightIndicatorColor 0x0028B050 (42B). Drawable::changedTeam
// 0x002742AC is the drawable call: it picks getNightIndicatorColor when
// TheGlobalData's time of day is 4 (night) and getIndicatorColor otherwise.
// The color getters end in the GameMakeColor(0, 0, 0, 255) default that the
// conditional jumps reach, so the 6-byte tails at 0x0028B04A and 0x0028B074
// are not functions of their own.
void Object::setCustomIndicatorColor(Color c)
{
	if (m_indicatorColor != c)
	{
		m_indicatorColor = c;
		if (m_drawable)
			m_drawable->changedTeam();
	}
}

void Object::removeCustomIndicatorColor()
{
	setCustomIndicatorColor(0);
}

Color Object::getIndicatorColor() const
{
	if (m_indicatorColor == 0)
	{
		const Team *myTeam = getTeam();
		if (myTeam)
		{
			const Player *player = myTeam->getControllingPlayer();
			if (player)
			{
				return player->getPlayerColor();
			}
		}
		return GameMakeColor(0, 0, 0, 255);
	}
	else
	{
		return m_indicatorColor;
	}
}

Color Object::getNightIndicatorColor() const
{
	if (m_indicatorColor == 0)
	{
		const Team *myTeam = getTeam();
		if (myTeam)
		{
			const Player *player = myTeam->getControllingPlayer();
			if (player)
			{
				return player->m_nightColor;
			}
		}
		return GameMakeColor(0, 0, 0, 255);
	}
	else
	{
		return m_indicatorColor;
	}
}

// ?rva0028D253@Object@@QAEXXZ @0x0028D253 (47B): hands the drawable the
// time-of-day indicator color, the choice Drawable::changedTeam makes, but
// from the Object side and without the drawable's slot-13 call.
void Object::rva0028D253()
{
	Drawable *draw = m_drawable;
	if (draw)
	{
		if (TheWritableGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
			draw->setIndicatorColor(getNightIndicatorColor());
		else
			draw->setIndicatorColor(getIndicatorColor());
	}
}
