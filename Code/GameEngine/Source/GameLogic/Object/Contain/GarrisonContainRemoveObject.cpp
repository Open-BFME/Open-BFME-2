// cl: /DNDEBUG /MD /EHsc
// ?removeObjectFromGarrisonPoint@GarrisonContain@@IAEXPAVObject@@H@Z @0x00477E82
// (132B): GarrisonContain::removeObjectFromGarrisonPoint, BFME1 donor
// GameEngine/Source/GameLogic/Object/Contain/GarrisonContainTrackTargets.cpp.
// Identity via 40-slot 0x14 loop over [esi+0x100] comparing [eax+0x74] (Object ID),
// bounds -1/0x28, four zero-stores, dec [esi+0x420] (m_garrisonPointsInUse) and
// Thing::setPosition([esi+8]+0x38) row 0x0030AA80; callers 0x00478850/0x004788CE.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	const Coord3D *getPosition() const { return (const Coord3D *)((const char *)this + 0x38); }
private:
	unsigned char m_pad[0x38];
	Coord3D m_pos;
};

class Object : public Thing
{
public:
	int getID() const { return *(const int *)((const char *)this + 0x74); }
private:
	unsigned char m_pad44_74[0x74 - sizeof(Thing)];
	int m_id;
	unsigned char m_tail[4];
};

typedef int ObjectID;

struct GarrisonPointData
{
	ObjectID objectID;
	ObjectID targetID;
	unsigned int placeFrame;
	unsigned int lastEffectFrame;
	void *effect;
};

class B0 { public: virtual void b0(); int m_pad4; Object *m_object; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	virtual ~OpenContain();
};

class GarrisonContain : public OpenContain
{
protected:
	void removeObjectFromGarrisonPoint(Object *occupant, int pointIndex);
private:
	unsigned char m_padFC100[0x100 - 0xFC];
	GarrisonPointData m_garrisonPointData[40];
	int m_garrisonPointsInUse;
};

void GarrisonContain::removeObjectFromGarrisonPoint(Object *occupant, int pointIndex)
{
	if (!occupant)
		return;
	if (pointIndex == -1)
	{
		for (int candidateIndex = 0; candidateIndex < 40; ++candidateIndex)
		{
			if (m_garrisonPointData[candidateIndex].objectID == occupant->getID())
				removeObjectFromGarrisonPoint(occupant, candidateIndex);
		}
		return;
	}
	if (pointIndex < 0 || pointIndex >= 40)
		return;
	m_garrisonPointData[pointIndex].objectID = 0;
	m_garrisonPointData[pointIndex].targetID = 0;
	m_garrisonPointData[pointIndex].placeFrame = 0;
	m_garrisonPointData[pointIndex].lastEffectFrame = 0;
	--m_garrisonPointsInUse;
	occupant->setPosition(m_object->getPosition());
}
