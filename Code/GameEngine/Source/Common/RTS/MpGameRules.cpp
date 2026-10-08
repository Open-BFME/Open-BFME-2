// cl: /O1 /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// MpGameRules defaults: WB GetDefaults at 0x013FC240 and AptMpGameRules callers.
// Descriptor and option tables reproduce retail data; preserve the existing caller ABI.
extern "C" void *__cdecl memset(void *, int, unsigned int);

struct RuleChoice {
    const char *label;
    int value;
};
struct RuleCombo {
    int id;
    const RuleChoice *choices;
    int count;
    int defaultIndex;
};
struct RuleCheck {
    int id;
    bool value;
};

static const RuleChoice ruleChoices0[] = {
    {"VALUE:Value",500},
    {"VALUE:Value",750},
    {"VALUE:Value",1000},
    {"VALUE:Value",1200},
    {"VALUE:Value",1400},
    {"VALUE:Value",1600},
    {"VALUE:Value",1800},
    {"VALUE:Value",2000},
    {"VALUE:Value",2500},
    {"VALUE:Value",3000},
    {"VALUE:Value",4000}
};
static const RuleCombo ruleCombo0 = {4,ruleChoices0,11,2};
static const RuleChoice ruleChoices1[] = {
    {"VALUE:ThirdX",33},
    {"VALUE:HalfX",50},
    {"VALUE:1X",100},
    {"VALUE:2X",200},
    {"VALUE:4X",400},
    {"VALUE:8X",800},
    {"VALUE:100X",10000}
};
static const RuleCombo ruleCombo1 = {3,ruleChoices1,7,2};
static const RuleChoice ruleChoices2[] = {
    {"VALUE:NoTimer",0},
    {"VALUE:Seconds",5},
    {"VALUE:Seconds",10},
    {"VALUE:Seconds",30},
    {"VALUE:Seconds",45},
    {"VALUE:Seconds",60},
    {"VALUE:Seconds",120},
    {"VALUE:Seconds",180},
    {"VALUE:Seconds",500}
};
static const RuleCombo ruleCombo2 = {6,ruleChoices2,9,0};
static const RuleChoice ruleChoices3[] = {
    {"VALUE:AutoResolveAndRTS",0},
    {"VALUE:AutoResolve",1},
    {"VALUE:RTS",2}
};
static const RuleCombo ruleCombo3 = {7,ruleChoices3,3,0};
static const RuleChoice ruleChoices4[] = {
    {"VALUE:AutoResolve",0},
    {"VALUE:RTS",1}
};
static const RuleCombo ruleCombo4 = {8,ruleChoices4,2,0};
static const RuleChoice ruleChoices5[] = {
    {"VALUE:Dynamic",0},
    {"VALUE:Quick",1}
};
static const RuleCombo ruleCombo5 = {9,ruleChoices5,2,0};
static const RuleCheck ruleChecks[]={{0,true},{2,true},{1,false}};
static const RuleCombo *mode0Combos[]={&ruleCombo0,&ruleCombo1};
static const RuleCheck *mode0Checks[]={&ruleChecks[0],&ruleChecks[1],&ruleChecks[2]};
static const RuleCombo *mode1Combos[]={&ruleCombo2,&ruleCombo3,&ruleCombo4,&ruleCombo5};
static const RuleCheck *mode1Checks[]={&ruleChecks[0],&ruleChecks[1]};

__declspec(noinline) int Rva00559F7EGet(int a)
{
	switch (a) {
	case 0: return 2;
	case 1: return 4;
	default: return 0;
	}
}

__declspec(noinline) int Rva00559F95Get(int a)
{
	switch (a) {
	case 0: return 3;
	case 1: return 2;
	default: return 0;
	}
}


__declspec(noinline) const RuleCombo * const *Rva00559F48Get(int mode) {
    switch (mode) {
    case 0: return mode0Combos;
    case 1: return mode1Combos;
    default: return 0;
    }
}

__declspec(noinline) const RuleCheck * const *Rva00559F63Get(int mode) {
    switch (mode) {
    case 0: return mode0Checks;
    case 1: return mode1Checks;
    default: return 0;
    }
}

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct RulesOverrideView {
    char padding[0x9D4];
    unsigned char bits;
};

void Rva00559FAC(int mode, void *store) {
    memset(store, 255, 40);
    if (mode == -1)
        return;

    int comboCount = Rva00559F7EGet(mode);
    const RuleCombo * const *combos = Rva00559F48Get(mode);
    for (int i = 0; i < comboCount; ++i) {
        const RuleCombo *cur = combos[i];
        if (cur)
            ((int *)store)[cur->id] = cur->choices[cur->defaultIndex].value;
    }

    int checkCount = Rva00559F95Get(mode);
    const RuleCheck * const *checks = Rva00559F63Get(mode);
    for (int j = 0; j < checkCount; ++j) {
        const RuleCheck *cur = checks[j];
        ((int *)store)[cur->id] = cur->value;
    }

    if (((RulesOverrideView *)TheWritableGlobalData)->bits & 3) {
        if (((int *)store)[0] != -1)
            ((int *)store)[0] = 0;
    }
}

#include "unicode_string.h"
class GameTextInterface;
extern GameTextInterface *TheGameText;
// Only the proven dispatch slot is viewed; TheGameText retains its established type.
class RuleTextInterfaceView {
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
 virtual UnicodeString fetch(const char *, bool *);
};
static const char *ruleStringTags[]={"RULE:AllowCustomHeroes","RULE:ClanGame","RULE:AllowRingHeroes","RULE:CommandPointFactor","RULE:InitialResources","RULE:MapRevealMode","RULE:StrategicPhaseTimer","RULE:BattleType","RULE:BattleChoice","RULE:AutoResolveType"};
UnicodeString Rva0055A04C(int rule) {
 if((unsigned int)rule>=10)return UnicodeString((const unsigned short*)L"Invalid Rule");
 return ((RuleTextInterfaceView*)TheGameText)->fetch(ruleStringTags[rule],0);
}
