// cl: /O1 /arch:SSE /G7 /MD
// Native Ghidra 00373373..003733B5, 66B, RET0. The rowed 003733B5
// wrapper calls this on its receiver minus20; preserve its opaque pin name.
// Registration strings in GameEngine::init and GameState::init identify
// the existing g_Va00E01EDC provider as the MineshaftPortalNetworkManager.
// Target facts: Object owner+8, portal+34, registration byte+38;
// unregister through 173B RET8 helper003731CB with the controlling player,
// then virtual slot0(flags0) plus global operator delete and clear fields.
// The portal slot's original identity is unresolved; retain its ABI view.
class Player;
class Object
{
public:
    Player *getControllingPlayer() const;
};
class Rva00373373Portal
{
public:
    virtual void *rva00373373Slot0(unsigned int flags);
};
class Rva0037381C
{
public:
    void rva003731CB(Rva00373373Portal *portal, Player *player);
};
extern void *g_Va00E01EDC;
void __cdecl operator delete(void *pointer);

class Rva003733B5Base
{
public:
    void Init();
private:
    char unknown00[8];
    Object *owner;
    char unknown0C[0x34 - 0x0C];
    Rva00373373Portal *portal;
    bool registered;
};

void Rva003733B5Base::Init()
{
    if (registered)
    {
        reinterpret_cast<Rva0037381C *>(g_Va00E01EDC)
            ->rva003731CB(portal, owner->getControllingPlayer());
        void *released = portal ? portal->rva00373373Slot0(0) : 0;
        ::operator delete(released);
        portal = 0;
        registered = false;
    }
}
