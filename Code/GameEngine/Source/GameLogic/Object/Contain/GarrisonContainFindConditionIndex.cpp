// cl: /DNDEBUG /MD /EHsc
// ?findConditionIndex@GarrisonContain@@IAEHXZ @0x00477E50 50B.
// GarrisonContain condition query sibling of put 0x00477DA1 and remove 0x00477E82.
// Evidence: BFME1 donor GarrisonContain.cpp findConditionIndex same m_object
// plus-0x08 plus body damage switch pristine-0 damaged-1 really-2 rubble-2
// else minus-1; BFME2 body at plus-0x254 via retail lea; slot 0x20
// getDamageState; chain lane after put landing.
enum BodyDamageType
{
    BODY_PRISTINE = 0,
    BODY_DAMAGED = 1,
    BODY_REALLYDAMAGED = 2,
    BODY_RUBBLE = 3
};
enum
{
    GARRISON_POINT_PRISTINE = 0,
    GARRISON_POINT_DAMAGED = 1,
    GARRISON_POINT_REALLY_DAMAGED = 2,
    GARRISON_INDEX_INVALID = -1
};
class BodyModule
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual BodyDamageType getDamageState();
};
class ObjectBodyView
{
public:
    unsigned char m_pad[0x254];
    BodyModule *m_body;
};
class B0 { public: virtual void b0(); int m_pad4; ObjectBodyView *m_object; };
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
    int findConditionIndex();
};
int GarrisonContain::findConditionIndex()
{
    ObjectBodyView *obj = m_object;
    BodyModule *body = obj->m_body;
    BodyDamageType damage = body->getDamageState();
    int index = GARRISON_INDEX_INVALID;
    switch (damage) {
    case BODY_PRISTINE:
        index = GARRISON_POINT_PRISTINE;
        break;
    case BODY_DAMAGED:
        index = GARRISON_POINT_DAMAGED;
        break;
    case BODY_REALLYDAMAGED:
    case BODY_RUBBLE:
        index = GARRISON_POINT_REALLY_DAMAGED;
        break;
    default:
        break;
    }
    return index;
}
