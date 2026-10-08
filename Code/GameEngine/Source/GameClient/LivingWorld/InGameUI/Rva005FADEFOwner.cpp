// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /EHc- /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native 005FADEF..005FAF3F RET4, 338 bytes; WorldBuilder 0160FA90.
// Controller prefix and virtual dispatch offsets are target facts. Original
// controller and interface names remain unknown. Nonempty input names select
// the existing FAB16 callback factory; empty names select FAB9E.
#include "../../../Common/BattlePromptArmyPanelView.h"
#include "string_base.h"
#include "../../../Common/BattlePromptCallbackPayloadView.h"
class Rva005FAB16;
class Rva005FAB9E;
RvaCloneResult<Rva005FAB16> Rva005FAC5DCreate(const Payload005FAB16 &);
RvaCloneResult<Rva005FAB9E> Rva005FAC8FCreate(const Payload005FAB9E &);
class Rva005773DB
{
public:
    Rva005773DB(const int *);
    ~Rva005773DB() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
private:
    TargetRef00217D4C *m_ptr;
};
struct Rva005D2355In { char pad[0x18]; StringBase<char> name; };
class Image;
const Image *Rva005D2355Get(Rva005D2355In *);
class Rva005FED59;
// Uncalled slot declarations establish ordinals only; their ABIs are unknown.
class BattlePromptOwnerDisplay
{
public:
    virtual void d00();
    virtual void slot01(const Image *);
    virtual void d02();
    virtual void d03();
    virtual void d04();
    virtual void d05();
    virtual void slot06(const Rva005773DB &);
    virtual void d07();
    virtual void slot08();
    virtual void slot09();
};
class BattlePromptOwnerActions
{
public:
    virtual void d00();
    virtual void d01();
    virtual void d02();
    virtual void slot03(const TreeHintRef00217D4C &);
    virtual void slot04();
};
class Rva005F22D2 { public: void rva005F22D2(); };

void Rva005FAF9FOwner::rva005FADEF(Rva005FED59 *child)
{
    void *panel = child;
    if (panel == m_active14) return;
    if (m_active14) {
        m_actions10->slot04();
        m_display0C->slot09();
        ((Rva005FEF65 *)m_active14)->setClipSelected(false);
    }
    m_active14 = panel;
    ((Rva005F22D2 *)m_observers18)->rva005F22D2();
    if (!m_active14) return;

    ((Rva005FEF65 *)m_active14)->setClipSelected(true);
    Rva005D2355In *input = (Rva005D2355In *)((Rva005FEF65 *)m_active14)->m_input14;
    m_display0C->slot01(Rva005D2355Get(input));
    {
        int value = (int)input;
        Rva005773DB hint(&value);
        m_display0C->slot06(hint);
    }
    m_display0C->slot08();

    TreeHintRef00217D4C action;
    if (!input->name.isEmpty()) {
        Payload005FAB16 payload;
        payload.context = m_context08;
        payload.input = input;
        payload.observers = &m_observers18;
        payload.flag = false;
        action = Rva005FAC5DCreate(payload);
    } else {
        Payload005FAB9E payload;
        payload.context = m_context08;
        payload.input = input;
        payload.observers = &m_observers18;
        payload.flag = false;
        action = Rva005FAC8FCreate(payload);
    }
    m_actions10->slot03(action);
}
