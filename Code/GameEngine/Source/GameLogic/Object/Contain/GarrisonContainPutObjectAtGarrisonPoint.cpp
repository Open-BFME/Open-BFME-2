// cl: /DNDEBUG /MD /EHsc
// ?putObjectAtGarrisonPoint@GarrisonContain@@IAEXPAVObject@@W4ObjectID@@HH@Z @0x00477DA1 175B.
// GarrisonContain placement sibling of removeObjectFromGarrisonPoint 0x00477E82.
// Evidence: BFME1 donor GarrisonContain.cpp putObjectAtGarrisonPoint same
// null plus 0x28 plus 3 bounds plus occupied check plus points[cond][point]
// copy plus setPosition row plus ID stores plus TheGameLogic frame plus inc;
// layout plus-0x100 data plus-0x420 count plus-0x424 points from remove TU.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
class Thing
{
public:
    void setPosition(const Coord3D *pos);
};
class Object : public Thing
{
public:
    int getID() const { return *(const int *)((const char *)this + 0x74); }
};
enum ObjectID { GarrisonContainObjectIDZero = 0 };
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
class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicFrameView
{
    char m_pad[0x40];
    unsigned int m_frame;
};
enum
{
    MAX_GARRISON_POINTS = 40,
    MAX_GARRISON_POINT_CONDITIONS = 3
};
class GarrisonContain : public OpenContain
{
protected:
    void putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int pointIndex);
private:
    unsigned char m_padFC100[0x100 - 0xFC];
    GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS];
    int m_garrisonPointsInUse;
    Coord3D m_points[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS];
};
void GarrisonContain::putObjectAtGarrisonPoint(Object *obj, ObjectID targetID, int conditionIndex, int pointIndex)
{
    if (obj == 0 || pointIndex < 0 || pointIndex >= MAX_GARRISON_POINTS
        || conditionIndex < 0 || conditionIndex >= MAX_GARRISON_POINT_CONDITIONS) {
        return;
    }
    if (m_garrisonPointData[pointIndex].objectID != 0) {
        return;
    }
    const Coord3D &pt = m_points[conditionIndex][pointIndex];
    Coord3D pos;
    pos.x = pt.x;
    pos.y = pt.y;
    pos.z = pt.z;
    obj->setPosition(&pos);
    m_garrisonPointData[pointIndex].objectID = (ObjectID)obj->getID();
    m_garrisonPointData[pointIndex].targetID = targetID;
    m_garrisonPointData[pointIndex].placeFrame = ((GameLogicFrameView *)TheGameLogic)->m_frame;
    ++m_garrisonPointsInUse;
}
