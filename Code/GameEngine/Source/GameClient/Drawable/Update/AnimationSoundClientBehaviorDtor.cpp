// cl: /DNDEBUG /MD /EHsc
// ??1AnimationSoundClientBehavior@@UAE@XZ @0x004C9DC9 80B
// AnimationSound dtor: restores derived primary 0xC5EE80 plus +0x0C
// 0xC5EE74, unlists this through the 0x00A032D0 container via rowed
// remove 0x00432F23 when present, restores intermediate primary 0xBEFE48
// and calls the fold base at 0x0049B47C via the Rva0049B47C pin (packet
// annotates the WindModuleInfo row at the same fold address). Layout via
// PrimaryP (Rva0049B47C padded to 0x0C with empty dtor) plus iface at +0x0C.
// Donor: BFME1 AnimationSoundClientBehaviorDestructors.cpp:48 (BFME2 adds
// remove plus Wind fold base; follow retail). Caller is slot-0 ??_G at
// 0x004C9F45; slot 4 -> 0x004C9EF3 uses class-name string
// "AnimationSoundClientBehavior". Shape follows CastleMemberBehaviorDtor.

class Rva00432F23Node
{
public:
	char m_pad00[0x14];
	Rva00432F23Node *m_next; // +0x14
	Rva00432F23Node *m_prev; // +0x18
};

class AnimationSoundModuleManager
{
public:
	void rva00432EC0(Rva00432F23Node*);
	void rva00432E5D(Rva00432F23Node*);
	void remove(Rva00432F23Node *node);
	void rva00432F7D(Rva00432F23Node *node);
};

extern AnimationSoundModuleManager *TheAnimationSoundModuleManager;
// TheAnimationSoundModuleManager: VA 0xe032d0 (zero-filled .bss).
AnimationSoundModuleManager * TheAnimationSoundModuleManager;

struct ModuleData;
class Drawable;
class Rva0049B47C
{
public:
    virtual ~Rva0049B47C();
    const ModuleData *data;
    Drawable *drawable;
};

// PrimaryP here is NOT the kept PrimaryP (Rva0049B47CThreeVptrDerived.cpp,
// Rva0049B47C plus MiBase1, two bases): this one is Rva0049B47C alone
// (single base, padded to 0x0C with empty dtor) plus iface at +0x0C.
// Same invented name, different layouts, so renamed to avoid the COMDAT
// clash; the row inlines this dtor and keeps its bytes.
class Rva004C9DC9Primary : public Rva0049B47C
{
public:
    ~Rva004C9DC9Primary() {}
};

class Rva004C9E33Iface
{
public:
    virtual void rva004C9E33() = 0;
    virtual void rva004C9E48() = 0;
};

class AnimationSoundClientBehavior : public Rva004C9DC9Primary, public Rva004C9E33Iface
{
public:
    virtual ~AnimationSoundClientBehavior();
    virtual void rva004C9E33();
    virtual void rva004C9E48();
    void updateAnimationSounds();
    float rangeSquared;
    Rva00432F23Node *next;
    Rva00432F23Node *prev;
};

AnimationSoundClientBehavior::~AnimationSoundClientBehavior()
{
    if (TheAnimationSoundModuleManager)
        TheAnimationSoundModuleManager->remove((Rva00432F23Node *)this);
}
