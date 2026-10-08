// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /ICode/Libraries/Include/Lib
// stlport
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f GameClient/InGameUI.cpp
// and GeneralsMD InGameUI.cpp provide the selection any/all semantic guide.
// Native29CBA6..29CC19 RET12: TheInGameUI slot73 yields the selected list,
// list payload+8 is Drawable, Object isDrawable+FC, and the only direct call
// is the independently rowed ActionManager::canOverrideSpecialPowerDestination.
#include "Coord3D.h"
#include <list>
class Object;
class Drawable {
public:
    char unknown00[0xFC];
    Object *object;
};
typedef _STL::list<Drawable *> DrawableList;
enum SpecialPowerType;
class ActionManager {
public:
    bool canOverrideSpecialPowerDestination(Object *, const Coord3D *, int, int);
};
extern ActionManager *TheActionManager;
class InGameUI {
public:
    enum SelectionRules { SELECTION_ANY, SELECTION_ALL };
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
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual const DrawableList *getAllSelectedDrawables() const;
    bool canSelectedObjectsOverrideSpecialPowerDestination(const Coord3D *, SelectionRules, SpecialPowerType) const;
};
extern InGameUI *TheInGameUI;
bool InGameUI::canSelectedObjectsOverrideSpecialPowerDestination(const Coord3D *loc, SelectionRules rule, SpecialPowerType spType) const
{
    int count = 0;
    int qualify = 0;
    const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
    for (DrawableList::const_iterator it = selected->begin(); it != selected->end(); ++it) {
        Drawable *other = *it;
        Object *object = other->object;
        ActionManager *manager = TheActionManager;
        ++count;
        if (manager->canOverrideSpecialPowerDestination(object, loc, spType, 0)) {
            if (rule == SELECTION_ANY)
                return true;
            ++qualify;
        }
    }
    if (rule == SELECTION_ALL && count > 0 && qualify == count)
        return true;
    return false;
}
