// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 clean LaserFXNuggetEffects.cpp donor575ba2b04743f190f069805fbdc59936123c45da.
// WB AD51C0/AD4FD0 and native1E04FE/1E05F9 identify both virtual effects.
// BFME2 base148, name148, backwards14C, fallback150; canonical Coord3D.
// Existing BFME2 factory, name-key and laser providers retain their landed names.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

#include "../../../Libraries/Include/Lib/Coord3D.h"

static inline void coordCopy(Coord3D *to, const Coord3D *from) {
 to->x = from->x; to->y = from->y; to->z = from->z;
}
static inline void coordAdd(Coord3D *to, const Coord3D *delta) {
 to->x += delta->x; to->y += delta->y; to->z += delta->z;
}
class Matrix3D;
class ThingTemplate;

class ClientUpdateModule
{
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Drawable
{
public:
	ClientUpdateModule *findClientUpdateModule(NameKeyType key);
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	void *newDrawable(void *thingTemplate, int status, int drawableID);
};

extern ThingFactory *TheThingFactory;

// Native lookup2D06CA uses the existing address-derived owner.



class Object
{
public:
 Drawable *getDrawable() const;
 const Coord3D *getPosition() const { return &m_position; }
 void *m_vptr;

public:
	unsigned char m_pad04[0x34];
	Coord3D m_position;
};

class LaserUpdate : public ClientUpdateModule
{
public:
	void initFromDrawables(void *primary, Drawable *parent, Drawable *target, void *d);
	void initLaser(const Object *parent, const Coord3D *start,
		const Coord3D *end, Int sizeDeltaFrames);
};

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_unreconstructed04[0x144];
};

class LaserFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float,
		const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	AsciiString m_laserName;
	bool m_laserBackwards;
	unsigned char m_padding[3];
	Coord3D m_targetPositionOffsetFallback;
};

// ?doFXObj@LaserFXNugget@@UBEXPBVObject@@0@Z
void LaserFXNugget::doFXObj(const Object *primary, const Object *secondary) const
{
	if (primary)
	{
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(m_laserName);
		Drawable *draw = (Drawable *)TheThingFactory->newDrawable(
			(void *)thingTemplate, DRAWABLE_STATUS_NONE, -1);
		if (draw)
		{
			static NameKeyType key_LaserUpdate =
				TheNameKeyGenerator->nameToKey("LaserUpdate");
			LaserUpdate *update =
				(LaserUpdate *)draw->findClientUpdateModule(key_LaserUpdate);
			if (update)
			{
				if (secondary)
				{
					update->initFromDrawables((void *)primary,
						primary->getDrawable(), secondary->getDrawable(), 0);
				}
				else
				{
					Coord3D position;
					const Coord3D *start = primary->getPosition();
     coordCopy(&position, start);
					coordAdd(&position, &m_targetPositionOffsetFallback);
					if (!m_laserBackwards)
					{
						update->initLaser(primary, start,
							&position, 0);
					}
					else
					{
						update->initLaser(primary, &position,
							start, 0);
					}
				}
			}
		}
	}
}

// ?doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z
void LaserFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *, float,
	const Coord3D *secondary) const
{
	if (primary)
	{
		const ThingTemplate *thingTemplate =
			TheThingFactory->findTemplate(m_laserName);
		Drawable *draw = (Drawable *)TheThingFactory->newDrawable(
			(void *)thingTemplate, DRAWABLE_STATUS_NONE, -1);
		if (draw)
		{
			static NameKeyType key_LaserUpdate =
				TheNameKeyGenerator->nameToKey("LaserUpdate");
			LaserUpdate *update =
				(LaserUpdate *)draw->findClientUpdateModule(key_LaserUpdate);
			if (update)
			{
				Coord3D position;
				if (secondary)
				{
					update->initLaser(0, primary, secondary, 0);
				}
				else
				{
					position.x = primary->x;
					position.y = primary->y;
					position.z = primary->z;
					coordAdd(&position, &m_targetPositionOffsetFallback);

					if (!m_laserBackwards)
					{
						update->initLaser(0, primary, &position, 0);
					}
					else
					{
						update->initLaser(0, &position, primary, 0);
					}
				}
			}
		}
	}
}
