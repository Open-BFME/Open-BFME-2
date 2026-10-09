// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
class AsciiString;
// Retail Version stores minimum/current bytes and has an inline constructor;
// that constructor form also reproduces the independent stack homes in DoXfer.
struct FarmVersion
{
    FarmVersion(unsigned char min, unsigned char cur) : minimum(min), current(cur) {}
    unsigned char minimum, current;
};
class Xfer{public:virtual~Xfer();virtual bool IsLoading() const;
virtual bool IsStoring() const;
virtual bool IsCRC() const;
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual Xfer &xferVersion(FarmVersion *);
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual Xfer &xferCoord3D(struct Coord3D *);
virtual void slot25();
virtual void slot26();
virtual Xfer& xferAsciiString(AsciiString*);
virtual void slot28();
virtual void slot29();
virtual Xfer &xferUnsignedInt(unsigned int *);
virtual Xfer& xferInt(int*);
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual Xfer &xferBool(bool *);
};
class Player;
namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

struct Rva002A8AB1Record
{
	char pad00[0x160];
	char *m_160raw;
	char pad164[8];
	int m_16C;
};

struct Rva002A8B59Data
{
	char pad00[0x4C];
	float m_4C;
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
	Rva002A8AB1Record *rva002A8AB1(void *key);
	Rva002A8B59Data *rva002A8B59(void *key);
};
extern Rva002A8F24 *g_00DFEEF8;

extern float g_secondsPerLogicFrame;

class Rva002A7389
{
public:
	int get(int v);
};

class Rva002A7461
{
public:
	int rva002A7461();
};


// PlayerList's matched mask/index consumers independently establish index at +0x54.
struct FarmPlayerIndexView
{
    unsigned char unknown[0x54];
    int index;
};
class PlayerList { public: Player *getNthPlayer(int index); };
extern PlayerList *ThePlayerList;
// Existing owned transfer at 0x00573F9F. Only its declaration is needed:
// the retail caller passes the same primary object and its owning player.
class Rva00573F03 { public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void Rva00573F9F(Xfer *, void *);
};
// WB 0x01538EF0 names AIFarm::DoXfer (AIFarm.cpp lines 94..107).
// Retail 0x0059702D..0x005970C9 is slot 12 of vtable RVA 0x00870B38.
// WB names the owning-player field at +0x68 and asserts the incoming owner is null.
// The remaining transferred fields retain offset names until their identities are proved.
class AIFarm
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void updatePriority();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();

    virtual void DoXfer(Xfer *xfer, Player *owner);
private:
    float priority;
    unsigned char unknown08[0x64 - 0x08];
    bool value64;
    unsigned char pad65[3];
    Player *m_owningPlayer;
    int value6c;
    unsigned int value70;
};
void AIFarm::DoXfer(Xfer *xfer, Player *owner)
{
    FarmVersion version(1,1);
    xfer->xferVersion(&version);
    xfer->xferBool(&value64);
    int index=-1;
    if (xfer->IsStoring() && m_owningPlayer)
        index=reinterpret_cast<const FarmPlayerIndexView *>(m_owningPlayer)->index;
    xfer->xferInt(&index);
    if (xfer->IsLoading() && index!=-1)
        m_owningPlayer=ThePlayerList->getNthPlayer(index);
    xfer->xferInt(&value6c);
    xfer->xferUnsignedInt(&value70);
    reinterpret_cast<Rva00573F03 *>(this)->Rva00573F03::Rva00573F9F(xfer,m_owningPlayer);
}

// WB 0x01538BD0 names AIFarm::updatePriority and asserts AIFarm.cpp lines 47..60.
// Retail 0x00596F23..0x00596FF5 establishes slot 5 and the priority float at +4.
void AIFarm::updatePriority()
{
    Rva002A8AB1Record *ai = g_00DFEEF8->rva002A8AB1(m_owningPlayer);
    if (ai->m_16C > 0)
    {
        void *stats = g_00DFEEF8->rva002A8F24(m_owningPlayer);
        unsigned int count = (*(IntMap **)((char *)stats + 0xc))->bucket_count();
        if (count < 1)
            count = 1;
        Rva002A8B59Data *data = g_00DFEEF8->rva002A8B59(m_owningPlayer);
        const float base = g_secondsPerLogicFrame * data->m_4C / (float)count;
        float amount = (float)((Rva002A7389 *)((char *)m_owningPlayer + 0x60))->get(0);
        float ratio = amount / (float)((Rva002A7461 *)((char *)m_owningPlayer + 0x60))->rva002A7461();
        // Preserve retail's two multiplies followed by the base increment.
        float boost = ratio * base;
        boost *= 10.0f;
        boost += base;
        // Retail loads the old priority separately before adding the boost.
        const volatile float &previous = priority;
        float next = previous + boost;
        priority = next < 2000.0f ? next : 2000.0f;
    }
}
