// cl: /O1 /G7 /arch:SSE /MD /ICode/GameEngine/Source/Common
#include "GameLogicObjectLookupView.h"

// WB 0x013C7EA0 names AptInGameSideCommandBar::Impl::Update and asserts
// TheGameLogic/ThePlayerList in AptInGameSideCommandBar.cpp:247-248.
// Native 0x005287EA..0x005288B8 establishes the offsets below. The update
// selects a local-player object with kind bit 14, reconciles button visibility
// and fades, then updates each non-null button's owned updater.
class Player;
class Object
{
public:
    Player *getControllingPlayer() const;
};

class BfmeMemberRV;
class BfmeThingRV
{
public:
    BfmeMemberRV *bfmePickRV();
};

class PlayerList;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;

struct SideBarTemplateView
{
    char m_prefix[0x108];
    unsigned char m_kindBits[28];
};

struct SideBarObjectView
{
    char m_prefix[4];
    SideBarTemplateView *m_template;
};

struct SideBarPlayerView
{
    char m_prefix[0x750];
    int m_gate750;
};

class Rva00528349
{
public:
    void rva00528349();
    void rva00528389();
};

class SideBarButtonUpdater
{
public:
    virtual void destroy();
    virtual void update();
};

struct SideBarButtonSlot
{
    void *m_button;
    SideBarButtonUpdater *m_updater;
    int m_key;
};

class AptInGameSideCommandBar
{
public:
    class Impl;
};

class AptInGameSideCommandBar::Impl
{
public:
    void Update();
    bool UpdateButtonVisiblity(Object *object);
private:
    char m_prefix[0x14];
    int m_state;
    void *m_prefixString;
    ObjectID m_selectedObject;
    ObjectID m_displayedObject;
    SideBarButtonSlot m_buttons[15];
    int m_count;
};

void AptInGameSideCommandBar::Impl::Update()
{
    if (m_state == 0)
        return;

    bool visible = false;
    Object *object = m_selectedObject ? TheGameLogic->findObjectByID(m_selectedObject) : 0;
    if (object && (((SideBarObjectView *)object)->m_template->m_kindBits[1] & 0x40)) {
        Player *player = object->getControllingPlayer();
        if (player && player == (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV() &&
            ((SideBarPlayerView *)player)->m_gate750 == 0) {
            m_displayedObject = m_selectedObject;
            visible = UpdateButtonVisiblity(object);
        }
    }

    if (visible) {
        if (m_state != 2 && m_state != 3)
            ((Rva00528349 *)this)->rva00528349();
    } else {
        if (m_state == 2 || m_state == 3)
            ((Rva00528349 *)this)->rva00528389();
    }

    if (m_state != 1 && m_state != 4) {
        for (int i = 0; i < m_count; ++i) {
            SideBarButtonUpdater *updater = m_buttons[i].m_updater;
            if (updater)
                updater->update();
        }
    }
}
