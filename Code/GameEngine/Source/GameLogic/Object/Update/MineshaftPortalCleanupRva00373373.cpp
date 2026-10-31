// cl: /O1 /arch:SSE /G7 /MD
// Native Ghidra 00373373..003733B5, 66B, RET0. The rowed 003733B5
// wrapper calls this on its receiver minus20; preserve its opaque pin name.
// Registration strings in GameEngine::init and GameState::init identify
// the existing TheMineshaftPortalNetworkManager provider as the MineshaftPortalNetworkManager.
// Target facts: Object owner+8, portal+34, registration byte+38;
// unregister through 173B RET8 helper003731CB with the controlling player,
// then virtual slot0(flags0) plus global operator delete and clear fields.
// The portal slot's original identity is unresolved; retain its ABI view.
class Player;
enum ObjectID { INVALID_OBJECT_ID = 0 };
class Rva00373B70Contain;
struct Rva00373B70Template
{
	char pad00[0x114];
	unsigned int m_kindOf;
};
class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned int isKindOf6D() const { return m_template->m_kindOf & 0x2000; }
	char pad00[4];
	const Rva00373B70Template *m_template;
	char pad08[0x74 - 0x08];
	ObjectID m_id;
	char pad78[0x250 - 0x78];
	Rva00373B70Contain *m_contain;
	char pad254[0x258 - 0x254];
	char *m_ai;
};
class Rva00373373Portal
{
public:
    virtual void *destroy(unsigned int flags);
    unsigned int id;
    char pad08[4];
    float x, y, z;
};
class MineshaftPortalNetworkManager
{
public:
    void rva003731CB(Rva00373373Portal *portal, Player *player);
};
extern void *TheMineshaftPortalNetworkManager;
#include <new>

class Rva003733B5Base
{
public:
	void Init();
	char m_pad00[0x8];
private:
	Object *owner; // +0x08
	char m_pad0C[0x28];
	Rva00373373Portal *portal; // +0x34
	bool registered; // +0x38
	char m_pad39[0x3];
};

void Rva003733B5Base::Init()
{
    if (registered)
    {
        reinterpret_cast<MineshaftPortalNetworkManager *>(TheMineshaftPortalNetworkManager)
            ->rva003731CB(portal, owner->getControllingPlayer());
        void *released = portal ? portal->destroy(0) : 0;
        ::operator delete(released);
        portal = 0;
        registered = false;
    }
}
