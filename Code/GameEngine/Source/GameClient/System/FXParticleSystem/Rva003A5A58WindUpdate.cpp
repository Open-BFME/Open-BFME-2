// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva003A5A58@Rva003A5A58@@UAEXXZ retail 0x003A5A58..0x003A5D1C
// (708 bytes EH thiscall RET 0). Virtual slot 1 of the CAT_WIND particle
// module vtables 0x00C1B5E0 (DefaultParticleModule<CAT_WIND> the copy
// ctor 0x003AE03D installs it) and 0x00C1CED8 (the concrete module whose
// slot 2 is the rowed clone 0x003ADFFA). WorldBuilder twin 0x00FA8AC0 is
// unnamed but carries the same statements and its TrackingPtr<class
// FXParticleSystem::ParticleSystem> AddTrackingPtr/RemoveTrackingPtr names.
// Body: copy the current particle's (+0x04) +0x3C system handle (rowed
// copy ctor 0x0004CC19; each use falls back to the pinned empty system
// 0x001FCBD7); skip when the system's wind kind (rowed 0x001F53F0) is 1;
// read its angle (rowed 0x001F53CE) and centre (rowed 0x001F385A) offset
// by the attached object's (+0xB4 TheGameLogic findObjectByID; Object
// position +0x38) or attached drawable's (+0xB0 TheGameClient slot 16 then
// rowed Drawable::getPosition) position; inside the radius (rowed
// 0x001F5423) push the particle position along the angle by the strength
// (rowed 0x001F5401 times this+0x10) faded past the inner radius (the same
// rowed getter retail calls twice) and when the system's +0x1C8 wind info
// has a positive +0x5C turbulence add the particle's (rowed 0x001F4D2D)
// wobble along an angle from position z times +0x60 plus the unsigned
// +0x88 age (retail adds both wobble terms to x). The handle is released
// through the pinned 0x0004CBC0 when set. Owner identity is unproven so
// the class carries the address name.
// Codegen notes: the fade takes math.h's float sqrt overload (its inline
// boundary schedules the call's stack pops as retail does); the release
// callee is nothrow (retail stores no -1 state before it); the body sits
// under the wind-kind test rather than after an early return (retail
// restores esi before the release).

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;

#include <math.h>
Real Sin(Real);
Real Cos(Real);

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }

private:
	char m_pad00[0x38];
	Coord3D m_pos;	// +0x38
};

#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Drawable
{
public:
	const Coord3D *getPosition() const;
};

class GameClient
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual Drawable *findDrawableByID(int id);	// slot 16
};
extern GameClient *TheGameClient;

// Rowed accessors of the particle system, each under its own address view.
class Rva001F53F0
{
public:
	int rva001F53F0();
};

class Rva001F553F
{
public:
	float rva001F53CE();
	float rva001F5401();
	float rva001F5423();
};

class Rva001F385A
{
public:
	void rva001F385A(void *out);
};

class Rva001F4D2D
{
public:
	float rva001F4D2D();
};

struct Rva003A5A58WindInfo
{
	char m_pad00[0x5C];
	Real m_turbulence;	// +0x5C
	Real m_turbulenceScale;	// +0x60
};

class ParticleSystem
{
public:
	int getWindKind() { return reinterpret_cast<Rva001F53F0 *>(this)->rva001F53F0(); }
	Real getAngle() { return reinterpret_cast<Rva001F553F *>(this)->rva001F53CE(); }
	Real getStrength() { return reinterpret_cast<Rva001F553F *>(this)->rva001F5401(); }
	Real getRadius() { return reinterpret_cast<Rva001F553F *>(this)->rva001F5423(); }
	void getPosition(Coord3D *out) { reinterpret_cast<Rva001F385A *>(this)->rva001F385A(out); }

	char m_pad000[0xB0];
	int m_attachedDrawable;	// +0xB0
	ObjectID m_attachedObject;	// +0xB4
	char m_pad0B8[0x1C8 - 0xB8];
	Rva003A5A58WindInfo *m_windInfo;	// +0x1C8
};

ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12()
	{
		if (m_system)
			rva0004CBC0();
	}
	void rva0004CBC0() throw();
	ParticleSystem *operator->() const
	{
		ParticleSystem *p = m_system;
		if (!p)
			p = Make001FCBD7();
		return p;
	}

	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class Rva003A5A58Particle
{
public:
	Real getWobble() { return reinterpret_cast<Rva001F4D2D *>(this)->rva001F4D2D(); }

	char m_pad00[0x1C];
	Coord3D m_pos;	// +0x1C
	char m_pad28[0x3C - 0x28];
	RvaSmartPtr12 m_system;	// +0x3C
	char m_pad48[0x88 - 0x48];
	unsigned int m_age;	// +0x88
};

class Rva003A5A58
{
public:
	virtual ~Rva003A5A58();
	virtual void rva003A5A58();

private:
	Rva003A5A58Particle *m_particle;	// +0x04
	char m_pad08[0x10 - 0x08];
	Real m_strength;	// +0x10
};

void Rva003A5A58::rva003A5A58()
{
	RvaSmartPtr12 system(m_particle->m_system);
	if (system->getWindKind() != 1)
	{
		Real angle = system->getAngle();
		Coord3D center;
		system->getPosition(&center);
		ObjectID objectID = system->m_attachedObject;
		if (objectID)
		{
			Object *obj = TheGameLogic->findObjectByID(objectID);
			if (obj)
			{
				center.x += obj->getPosition()->x;
				center.y += obj->getPosition()->y;
				center.z += obj->getPosition()->z;
			}
		}
		else
		{
			int drawableID = system->m_attachedDrawable;
			if (drawableID)
			{
				Drawable *draw = TheGameClient->findDrawableByID(drawableID);
				if (draw)
				{
					const Coord3D *pos = draw->getPosition();
					center.x += pos->x;
					center.y += pos->y;
					center.z += pos->z;
				}
			}
		}

		Coord3D delta;
		delta.x = m_particle->m_pos.x - center.x;
		delta.y = m_particle->m_pos.y - center.y;
		delta.z = m_particle->m_pos.z - center.z;
		Real distSqr = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;

		Real radius = system->getRadius();
		if (radius * radius > distSqr)
		{
			Real strength = system->getStrength() * m_strength;
			Real innerRadius = system->getRadius();
			if (innerRadius * innerRadius < distSqr)
				strength = (1.0f - (sqrt(distSqr) - innerRadius) / (radius - innerRadius)) * strength;
			m_particle->m_pos.x += Cos(angle) * strength;
			m_particle->m_pos.y += Sin(angle) * strength;

			Rva003A5A58WindInfo *info = system->m_windInfo;
			if (info && info->m_turbulence > 0.0f)
			{
				Real wobbleAngle = m_particle->m_pos.z * info->m_turbulenceScale + (Real)m_particle->m_age;
				Real wobble = m_particle->getWobble() * info->m_turbulence;
				m_particle->m_pos.x += Cos(wobbleAngle) * wobble;
				m_particle->m_pos.x += Sin(wobbleAngle) * wobble;
			}
		}
	}
}
