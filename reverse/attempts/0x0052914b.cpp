// ?update@Rva0052914B@@QAEXPAVObject@@@Z
// partial score=0.99 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// Native 52914B..529318 RET4: cached cost-modifier UI update. WB unnamed
// 13C9D90 in PalantirCommandInterface.cpp and the independently rowed cost
// getter, visibility callback, Player and Apt providers establish its purpose.
// Target facts: object template bit80 at108; module data flag128; state bytes
// 4/5/6 and cached words8/C; GameText virtual slot40 returns the format holder.
// The formatting value is prepared on the stack before the two-argument text
// fetch, not passed as a third fetch argument. The APT key is an AsciiString,
// proven independently by its StringBase<char> constructor and setter ABI.
// The original state-class/method names remain unknown. All storage views and
// the v16 label below are descriptive; no reference layout is asserted.
#include "unicode_string.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Player;
struct CostDataView { char prefix[0x128]; unsigned char percent; };
class Module { public: void *vptr; CostDataView *data; };
struct ObjectTemplateCostView { char prefix[0x108]; unsigned char kind; };
class Object {
public:
    Player *getControllingPlayer() const;
    Module *findModule(NameKeyType) const;
    void *vptr; ObjectTemplateCostView *definition;
};
class Rva002A7DDEArg;
class Rva002A7DDE { public: bool rva002A7DDE(Rva002A7DDEArg *); };
extern class PlayerList *ThePlayerList;
class Rva00528C65 { public: AsciiString rva00528C65() const; int rva00528C85(Player *); };
class Rva00528BDD { public: void rva00528BDD(); };
class Rva00222A8BTarget {
public: void invoke(void *, const char *, int, const char *, void *, void *, void *, void *);
};
class BfmeAptWindowManager { public: void bfmeSetText(const AsciiString &, const UnicodeString &, bool); };
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameTextInterface {
public:
#define V(n) virtual void pad##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
virtual const UnicodeString &v16(const AsciiString &, bool *);
};
extern GameTextInterface *TheGameText;
class Rva0052914B {
public: void update(Object *);
private: void *owner; bool visible, valid; unsigned char percent; char padding; int unused, cachedValue;
};
void Rva0052914B::update(Object *object)
{
    if (!(object->definition->kind & 0x80)) {
        if (visible) ((Rva00528BDD *)this)->rva00528BDD();
        return;
    }
    static NameKeyType key = TheNameKeyGenerator->nameToKey("CostModifierUpgrade");
    Module *module = object->findModule(key);
    Player *player = object->getControllingPlayer();
    if (module && player && ((Rva002A7DDE *)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)object)) {
        if (!visible) {
            ((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(owner, "ShowCostModifierUpgradeInterface", 0, 0, 0, 0, 0, 0);
            visible = true;
            valid = false;
        }
        unsigned char usePercent = module->data->percent;
        AsciiString format = ((Rva00528C65 *)module)->rva00528C65();
        int value = ((Rva00528C65 *)module)->rva00528C85(player);
        if (valid) {
            if (usePercent != percent || (!usePercent && unused != 0) || value != cachedValue)
                valid = false;
        }
        if (!valid) {
            UnicodeString text;
            text.format(&TheGameText->v16(format, 0), value);
            static AsciiString target("APT:CostModifierUpgrade");
            g_bfmeAptWindowManager->bfmeSetText(target, text, 0);
            percent = usePercent;
            valid = true;
            unused = 0;
            cachedValue = value;
        }
    } else if (visible) ((Rva00528BDD *)this)->rva00528BDD();
}
