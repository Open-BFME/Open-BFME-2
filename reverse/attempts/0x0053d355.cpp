// ?rva0053D355@ControlBar@@QAEXPAVObject@@_N@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
#include "ascii_string.h"
#include "Lib/Coord3D.h"
namespace _STL { void __cdecl free(void *); }
#include <vector>
#include <map>
// Complete ZH ControlBarCommand.cpp is the semantic guide. Named target WB
// 11180A0, assert file ControlBarCommand.cpp1005..1216, and native
// 53CF65..53D3551008 establish the target deltas and ten-case jump table.
// WB's 11188D0 template-overlay helper always returns null, and retail
// retains the template-query side effect before resetting the overlay to0.
typedef unsigned int UnsignedInt;
class ThingTemplate;
class Player;
class ExitInterface;
class CommandSet { public: const class CommandButton *getCommandButton(int) const; };
enum ObjectStatusTypes { CommandPopulationStatus=100 };
enum ScienceType { CommandPopulationScienceInvalid=-1 };
class Rva0029FCB4 { public: _STL::vector<ScienceType> rva0029FCB4(); };
class Rva0023C6A4 { public: bool rva00200084(); };
class GameLogic; extern GameLogic *TheGameLogic;
class Player { public: bool hasScience(ScienceType) const;
 bool hasAnyRequiredSciences(const _STL::vector<ScienceType>&) const;
 const ThingTemplate *rva002AA857(int); };
class Rva0037EE4C { public: int rva0037EE4C(const ThingTemplate *,int,int); };
class Image; class ModuleData;
class Rva0037EDC6 { public: const Image *rva0037EDC6(int); };
class Rva0037E421 { public: void *rva0037E7A5(int); };
class Rva0033AC7F { public: bool rva0033ACC5(AsciiString&); };
class Rva0035B750 { public: void rva0035B750(const ModuleData *); };
class Rva0035B7D9 { public: void rva0035B7D9(Rva0035B7D9 *,bool); };
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class Rva0053B914 { public: void rva0053B914(); };
class Rva0031B60DOut { public: int start,count; };
class Rva0031B60DOwner { public: Rva0031B60DOut *rva0031B60D(Rva0031B60DOut *); };
class ICoord2D { public: ICoord2D(int,int); int x,y; };
struct BfmeE8 { int x,y; };
struct TemplateCountKey { const ThingTemplate *pointer;
 __forceinline TemplateCountKey() {} __forceinline TemplateCountKey(const ThingTemplate *p):pointer(p){}
 __forceinline bool operator<(const TemplateCountKey &other)const{return pointer<other.pointer;} };
struct CommandPopulationEntry { char unknown[216]; };
struct CommandPlayerView { char unknown00[0x73C]; CommandPopulationEntry *begin,*end,*capacity; };
struct CommandIncrement { int *value; CommandIncrement(int &v):value(&v){} ~CommandIncrement(){ ++*value; } };
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva002D368E { public: void rva002D368E(); };
class Rva002D363EOwner { public: void rva002D363E(int); };
class WindowList;
class Rva0053ED1A { public: void rva0053EFC7(WindowList&); void rva0053EF2E(); };
class CommandExitView {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
 virtual const Coord3D *getRallyPoint() const;
};
extern "C" void *__cdecl memset(void *,int,unsigned int);

class GameWindow {
public:
    int winHide(bool); bool winIsHidden(); int winEnable(bool);
    unsigned int winSetStatus(unsigned int); unsigned int winClearStatus(unsigned int);
    unsigned int winGetStatus();
};
enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class CommandWindowManagerView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
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
    virtual GameWindow *getWindow(GameWindow *, int);
};
class CommandContainView {
public:
    virtual void slot0();
    virtual void *asOpenContain();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
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
    virtual int getContainMax();
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
    virtual bool displayedOnControlBar();
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
    virtual int getContainCount(int);
};
struct CommandProductionEntry { char unknown00[0x14]; float percent; };
class CommandProductionView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
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
    virtual const CommandProductionEntry *firstProduction();
};
class Object {
public:
    void *rva0028BC58(int);
    bool isLocallyControlled() const;
    Player *getControllingPlayer() const;
    const AsciiString *rva00290E67() const;
    ThingTemplate *rva002911B7();
    bool testStatus(ObjectStatusTypes) const;
    ExitInterface *getObjectExitInterface() const;
};
struct CommandObjectView {
    char unknown00[4]; const char *objectTemplate;
    char unknown08[0x250-8]; CommandContainView *contain;
};
struct CommandDrawableView { char unknown00[0xFC]; Object *object; };
class BfmeMemberRV { public: bool bfmeAskRV(); };
class PlayerList;
extern PlayerList *ThePlayerList;
struct CommandPlayerListView { char unknown00[0x10]; BfmeMemberRV *localPlayer; };
class Gen_003bcb40 { public: void m(int); };
class CommandButton {
public:
    const ThingTemplate *rva0035B570() const;
    void rva0035B5C2(Object *,bool);
    unsigned int options() const { return *(const unsigned int *)((const char *)this + 0x1C); }
    int type() const { return *(const int *)((const char *)this + 0x14); }
    bool enabled() const { return *((const unsigned char *)this + 0x105) != 0; }
};
void *GadgetButtonGetData(GameWindow *);
void GadgetButtonSetDisallowed(GameWindow *, int);
void GadgetCheckLikeButtonSetVisualCheck(GameWindow *, bool);
void Rva003284ED(GameWindow *, int);
void Rva003284B9(GameWindow *, int, int);
class Rva002A7DDEArg;
class Rva002A7DDE { public: bool rva002A7DDE(Rva002A7DDEArg *); };
class ControlBar;
extern ControlBar *TheControlBar;
class ControlBar {
public:
    void rva0053CF65();
    void rva0053D355(Object *,bool);
    void rva0053BB16(Object *,CommandSet *);
    void rva0031B641(GameWindow *,const CommandButton *);
    const CommandButton *findCommandButton(const AsciiString &);
    void showRallyPoint(const Coord3D *);
    void rva0031D230();
    int rva0053BD66(const CommandButton *, GameWindow *, Object *, float *, bool) const;
private:
    char unknown00[0x50]; GameWindow *queueParent;
    char unknown54[0x6C-0x54]; CommandDrawableView *selected;
    char unknown70[0x80-0x70]; int lastInventoryCount;
    char unknown84[0xDC-0x84]; GameWindow *windows[32];
    char unknown15C[0x208-0x15C]; int clockColor;
    char unknown20C[0x2A0-0x20C]; Rva0053ED1A *overlaySink;
    char unknown2A4[4]; _STL::vector<BfmeE8> ranges;
};
// ?rva0053CF65@ControlBar@@QAEXXZ
void ControlBar::rva0053CF65()
{
    Object *obj = 0;
    if (selected) obj = selected->object;
    CommandContainView *contain = obj ? ((CommandObjectView *)obj)->contain : 0;
    if (contain && contain->getContainMax() > 0 && lastInventoryCount != contain->getContainCount(0)) {
        lastInventoryCount = contain->getContainCount(0);
        rva0031D230();
    }
    CommandProductionView *production = obj ? (CommandProductionView *)obj->rva0028BC58(0) : 0;
    if (queueParent->winIsHidden() == false) {
        ((Gen_003bcb40 *)this)->m(0);
        if (production) {
            const CommandProductionEntry *entry = production->firstProduction();
            if (entry) {
                static unsigned int winID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonQueue01");
                GameWindow *window = ((CommandWindowManagerView *)TheWindowManager)->getWindow(queueParent, winID);
                Rva003284B9(window, (int)entry->percent, clockColor);
            }
        }
    }
    bool locallyControlled = obj ? obj->isLocallyControlled() : false;
    for (int i = 0; i < 32; ++i) {
        GameWindow *win = windows[i];
        if (!win) continue;
        const CommandButton *command = (const CommandButton *)GadgetButtonGetData(win);
        if (!command) continue;
        float percent = 0;
        int availability = rva0053BD66(command, win, obj, &percent, false);
        bool disable = false;
        bool forceVisible = false;
        bool spectator = false;
        if (!locallyControlled) {
            if (((CommandPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV()) {
                spectator = true;
                if (availability != 0 && availability != 3 && availability != 4) {
                    forceVisible = true;
                    availability = 0;
                }
            } else disable = true;
        }
        if (availability == 3 && win->winIsHidden()) continue;
        if (availability == 0 && (command->options() & 0x00400000) && !forceVisible)
            availability = 3;
        win->winClearStatus(0x00400000);
        win->winClearStatus(0x01000000);
        win->winClearStatus(0x40000000);
        win->winClearStatus(0x80000000);
        GadgetButtonSetDisallowed(win, 0);
        if (command->type() == 0x10 && (locallyControlled || disable)) {
            if (obj && (*(const unsigned int *)(((CommandObjectView *)obj)->objectTemplate + 0x11C) & 0x80000000) && availability == 0) {
                win->winEnable(false);
                win->winClearStatus(8);
                win->winSetStatus(0x80000000);
            } else {
                win->winSetStatus(8);
                win->winSetStatus(0x01000000);
                if (availability == 3) win->winHide(true);
            }
            continue;
        }
        bool hide = false;
        int color = 0;
        switch (availability) {
        case 3: hide = true; break;
        case 0: case 4: case 8:
            win->winEnable(false); win->winSetStatus(0x80000000);
            if (availability == 4) GadgetButtonSetDisallowed(win, 1);
            if (availability == 8) win->winSetStatus(0x01000000);
            break;
        case 5:
            color = clockColor; win->winEnable(false); win->winSetStatus(0x00400000); break;
        case 6: case 7:
            win->winEnable(false); win->winSetStatus(0x01000000); break;
        case 9:
            color = clockColor; win->winEnable(true); win->winSetStatus(0x00400000); break;
        default: win->winEnable(true); break;
        }
        if (color < 1.0f && !spectator) Rva003284B9(win, (int)(percent * 100.0f), color);
        if (disable && (win->winGetStatus() & 8)) {
            win->winEnable(false); win->winSetStatus(0x40000000);
        }
        win->winHide(hide);
        if (!command->enabled()) win->winEnable(false);
        command->rva0035B570();
        Rva003284ED(win, 0);
        if (command->options() & 0x400) {
            if (availability == 2) GadgetCheckLikeButtonSetVisualCheck(win, true);
            else GadgetCheckLikeButtonSetVisualCheck(win, false);
        }
    }
}

// Complete named WB1117000/ControlBarCommand.cpp391..579 and clean BFME1
// ba7ddda7 populateCommand guide the workflow. Native53D355..53DA531790
// independently establishes the target ranges, two revival passes and offsets.
// ?rva0053D355@ControlBar@@QAEXPAVObject@@_N@Z
void ControlBar::rva0053D355(Object *obj,bool refresh)
{
    Player *player=obj->getControllingPlayer();
    ((Rva0053B914 *)this)->rva0053B914();
    CommandSet *set=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(obj->rva00290E67());
    ThingTemplate *overrideRecord=obj->rva002911B7();
    if(overrideRecord) set=(CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8((AsciiString *)((char *)overrideRecord+0x70));
    if(!set){ if(theRadarWindowOverrideSource)((Rva002D368E *)theRadarWindowOverrideSource)->rva002D368E(); return; }
    if(ranges.empty()) {
        ranges.push_back(reinterpret_cast<const BfmeE8 &>(ICoord2D(0,*(int *)((char *)set+0x94))));
    }
    Rva0031B60DOut range;
    ((Rva0031B60DOwner *)this)->rva0031B60D(&range);
    int i;
    for(i=0;i<32;++i){
        if(windows[i]){
            const CommandButton *button=0;
            if(i<range.count) button=set->getCommandButton(i+range.start);
            if(!button) windows[i]->winHide(true);
            else {
                if(obj->testStatus(CommandPopulationStatus)){
                    AsciiString *name=(AsciiString *)((char *)button+0x48);
                    if(!((StringBase<char> *)name)->isEmpty()){
                        const CommandButton *alternate=TheControlBar->findCommandButton(*name);
                        if(alternate)button=alternate;
                    }
                }
                ((CommandButton *)button)->rva0035B5C2(obj,false);
            }
            rva0031B641(windows[i],button);
        }
    }
    CommandContainView *contain=((CommandObjectView *)obj)->contain;
    if(contain&&contain->displayedOnControlBar())rva0053BB16(obj,set);
    int revivalIndex=0,templateIndex=0;
    CommandPlayerView *pv=(CommandPlayerView *)player;
    int entryCount=((_STL::vector<CommandPopulationEntry> *)((char *)player+0x73C))->size();
    unsigned char used[32];
    memset(used,0,32);
    _STL::map<TemplateCountKey,int> counts;
    for(i=0;i<range.count;++i){
        const CommandButton *button=set->getCommandButton(i+range.start);
        char *b=(char *)button;
        if(!button||!*(bool *)(b+0x106))continue;
        if(button->options()&0x80000){if(windows[i])windows[i]->winHide(true);continue;}
        if(contain&&*(bool *)(b+0x107)){
            void *open=contain->asOpenContain();
            if(open&&!*(bool *)((char *)open+0xDE))continue;
        }
        if(button->type()==0x2E){
            CommandIncrement increment(templateIndex);
            if(!((Rva002A7DDE *)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)obj)){
                if(windows[i])windows[i]->winHide(true);continue;
            }
            const ThingTemplate *key=player->rva002AA857(templateIndex);
            int nth=counts[*(TemplateCountKey *)&key]; counts[*(TemplateCountKey *)&key]=nth+1;
            int index=-1;
            if(key)index=((Rva0037EE4C *)((char *)player+0x738))->rva0037EE4C(key,-1,nth);
            const Image *image=((Rva0037EDC6 *)((char *)player+0x738))->rva0037EDC6(index);
            Rva0033AC7F *textTemplate=(Rva0033AC7F *)((Rva0037E421 *)((char *)player+0x738))->rva0037E7A5(index);
            if(image&&textTemplate&&!((Rva0023C6A4 *)TheGameLogic)->rva00200084()){
                used[index]=1;
                ((Rva0035B750 *)button)->rva0035B750((const ModuleData *)image);
                AsciiString text;
                if(textTemplate->rva0033ACC5(text))*(AsciiString *)(b+0x7C)=text;
                if(windows[i])rva0031B641(windows[i],button);
                ((AsciiString *)(b+0x7C))->clear();
                *(int *)(b+0xC0)=index;
            }else *(int *)(b+0xC0)=-1;
            ++revivalIndex;
        }
        if(button->type()==0x10)continue;
        if(windows[i]){
            windows[i]->winHide(false);windows[i]->winEnable(true);
            if(*(bool *)(b+0x101))windows[i]->winSetStatus(0x4000000);
            else windows[i]->winClearStatus(0x4000000);
        }
        if((button->options()&0x80)&&*(void **)(b+0x44)){
            _STL::vector<ScienceType> sciences=((Rva0029FCB4 *)*(void **)(b+0x44))->rva0029FCB4();
            if(!sciences.empty()){
                if(!player->hasAnyRequiredSciences(sciences)){if(windows[i])windows[i]->winHide(true);}
                else{
                    int best=-1;
                    _STL::vector<ScienceType> &list=*(_STL::vector<ScienceType> *)(b+0xA4);
                    for(unsigned j=0;j<list.size();++j){if(player->hasScience(list[j]))best=j;else break;}
                    if(best!=-1){
                        ScienceType science=list[best];
                        const CommandButton *candidate=*(const CommandButton **)((char *)this+0x2C);
                        for(;candidate;candidate=*(const CommandButton **)((char *)candidate+0x18)){
                            _STL::vector<ScienceType> &clist=*(_STL::vector<ScienceType> *)((char *)candidate+0xA4);
                            if(candidate->type()==0x19&&!clist.empty()&&clist[0]==science)
                                ((Rva0035B7D9 *)button)->rva0035B7D9((Rva0035B7D9 *)candidate,true);
                        }
                    }
                }
            }
        }
    }
    if(((Rva002A7DDE *)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg *)obj)){
        revivalIndex=0;
        int limit=((Rva0023C6A4 *)TheGameLogic)->rva00200084()?range.count:((entryCount<range.count)?entryCount:range.count);
        for(i=0;i<limit;++i){
            const CommandButton *button=set->getCommandButton(i+range.start);
            char *b=(char *)button;
            if(!button||!*(bool *)(b+0x106)||button->type()!=0x2E)continue;
            if(((Rva0023C6A4 *)TheGameLogic)->rva00200084()&&(button->options()&0x40))continue;
            CommandIncrement increment(revivalIndex);
            if(used[revivalIndex])continue;
            const Image *image=((Rva0037EDC6 *)((char *)player+0x738))->rva0037EDC6(revivalIndex);
            Rva0033AC7F *textTemplate=(Rva0033AC7F *)((Rva0037E421 *)((char *)player+0x738))->rva0037E7A5(revivalIndex);
            if(image&&textTemplate){
                ((Rva0035B750 *)button)->rva0035B750((const ModuleData *)image);
                AsciiString text;
                if(textTemplate->rva0033ACC5(text))*(AsciiString *)(b+0x7C)=text;
                if(windows[i])rva0031B641(windows[i],button);
                ((AsciiString *)(b+0x7C))->clear();
                *(int *)(b+0xC0)=revivalIndex;
            }else *(int *)(b+0xC0)=-1;
        }
    }
    if(obj->isLocallyControlled()||!((CommandPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV()){
        ExitInterface *exit=obj->getObjectExitInterface();
        if(exit)showRallyPoint(((CommandExitView *)exit)->getRallyPoint());
    }
    rva0053CF65();
    ((Rva002D363EOwner *)theRadarWindowOverrideSource)->rva002D363E((int)obj);
    if(overlaySink){
        if(!obj->isLocallyControlled()&&((CommandPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV()){
            overlaySink->rva0053EF2E();return;
        }
        _STL::vector<GameWindow *> list;
        ((_STL::vector<const ModuleData *> *)&list)->reserve(32);
        for(int k=0;k<32;++k){GameWindow *window=windows[k];if(window)
            ((_STL::vector<const ModuleData *> *)&list)->push_back(reinterpret_cast<const ModuleData *const &>(window));}
        overlaySink->rva0053EFC7(*(WindowList *)&list);
    }
}

