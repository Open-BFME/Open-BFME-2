// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// PC RespawnUpdate::iniParseDefaultRule; exact name in retail diagnostics.
// Preview RespawnRules crosswalk selected the family; PC C56270 independently
// registers this callback with the rules tree at module offset10C.
// No clean BFME1 or GeneralsMD RespawnUpdate parser body was found. Reuse the
// existing INI parser/exception idioms and STLport tree semantics; reconstruct
// the sequential field checks as real C++ from the full524B PC body.
// BFME2RespawnRuleTree/RespawnRule/RespawnInsertResult are descriptive facades,
// not asserted original type spellings. The tree starts with its header ptr;
// node+10 is the unsigned level key. Find357180 is the already recovered
// unsigned STL tree lookup. Insert4AFB2B is a35B pair-copy wrapper around
// unique insertion4AF4A6; it returns the node and bool (true iff inserted).
// Throw-info anchor refers to the existing retail INIException chain CFE2FC.
#include <string.h>
class INI {
public:
    const char *getNextToken(const char *);
    const char *getNextTokenOrNull(const char *);
    static void parseBool(INI *, void *, void *, const void *);
    static void parseInt(INI *, void *, void *, const void *);
    static void dup_002EF72(INI *, void *, void *, const void *);
    static void parsePercentToReal(INI *, void *, void *, const void *);
    char unused[0x420]; const char *colon;
};
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
struct INIException { char *message; int code; INIException() {} INIException(int argCount, const char *format, ...); };
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct RespawnThrowInfoAnchor { int a,b,c,d; };
static const RespawnThrowInfoAnchor respawnThrowInfoAnchor = {0,0,0,0};
struct RespawnRule {
    unsigned level, cost; int time; float health; bool autoSpawn;
};
// Parser-local initialization avoids emitting a competing constructor for
// the descriptive RespawnRule facade. Both retail parsers inline these stores.
static __forceinline void initializeRespawnRule(RespawnRule &rule, unsigned level=1)
{
    rule.level=level; rule.cost=0; rule.time=0; rule.health=1.0f; rule.autoSpawn=false;
}
class RespawnUpdate;
namespace _STL {
template <class _Key, class _Mapped> struct pair;
template <class _Pair> struct _Select1st;
template <class _Key> struct less;
template <class _Value> class allocator;
template <class _Value> struct _Rb_tree_node;
template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc>
class _Rb_tree {
    template <class _Key_arg>
    _Rb_tree_node<_Value> *_M_find(const _Key_arg &) const;
    friend class ::RespawnUpdate;
};
}
typedef _STL::pair<const unsigned int, void *> RespawnRuleValue;
typedef _STL::_Rb_tree<unsigned int, RespawnRuleValue,
    _STL::_Select1st<RespawnRuleValue>, _STL::less<unsigned int>,
    _STL::allocator<RespawnRuleValue> > RespawnRuleTree;
struct RespawnInsertResult { void *node; bool inserted; };
struct BFME2RespawnRuleTree {
    void *sentinel;
    RespawnInsertResult insert(const RespawnRule &);
};
class RespawnUpdate {
public:
    static void iniParseNewRuleForLevel(INI *, void *, void *, const void *);
    static void iniParseDefaultRule(INI *, void *, void *, const void *);
};
#define THROW0(message) { INIException e; e.INIException::INIException(3,message); _CxxThrowException(&e, (const _s__ThrowInfo *)&respawnThrowInfoAnchor); __assume(0); }
#define THROW1(message,token) { INIException e; e.INIException::INIException(3,message,token); _CxxThrowException(&e, (const _s__ThrowInfo *)&respawnThrowInfoAnchor); __assume(0); }
#define FIELD(key,diagnostic,parser,member) \
    token=ini->getNextToken(ini->colon); \
    if(!token || _strcmpi(token,key)!=0) \
        THROW1("RespawnUpdate::iniParseDefaultRule -- RespawnRules entry expecting '" diagnostic "' entry. You specified %s.",token) \
    if(strcmp(token,key)!=0) \
        THROW1("RespawnUpdate::iniParseDefaultRule -- RespawnRules entry for '" diagnostic "' is case sensitive. You specified %s.",token) \
    INI::parser(ini,instance,&rule.member,0);
void RespawnUpdate::iniParseDefaultRule(INI *ini, void *instance, void *store, const void *) {
    RespawnRule rule;
    initializeRespawnRule(rule);
    BFME2RespawnRuleTree *rules=(BFME2RespawnRuleTree *)store;
    if(((RespawnRuleTree *)rules)->_M_find<unsigned int>(rule.level) != rules->sentinel)
        THROW0("RespawnUpdate::iniParseDefaultRule -- Duplicate RespawnRules entry.")
    const char *token;
    FIELD("AutoSpawn","AutoSpawn:Yes' or 'AutoSpawn:No",parseBool,autoSpawn)
    FIELD("Cost","Cost",dup_002EF72,cost)
    FIELD("Time","Time",parseInt,time)
    FIELD("Health","Health",parsePercentToReal,health)
    rules->insert(rule);
}

// Per-level sibling: retail diagnostics and PC C56280 identify RVA4AFE6C.
// Preserve literal/logic quirks: only AutoSpawn uses case-insensitive dispatch;
// Health repeats the Cost duplicate error; the Time duplicate format has two
// %d conversions but retail supplies one value. Unknown keys are skipped.
#define THROW2(message,a,b) { INIException e; e.INIException::INIException(3,message,a,b); _CxxThrowException(&e, (const _s__ThrowInfo *)&respawnThrowInfoAnchor); __assume(0); }
void RespawnUpdate::iniParseNewRuleForLevel(INI *ini, void *instance, void *store, const void *) {
    RespawnRule defaultRule;
    initializeRespawnRule(defaultRule);
    BFME2RespawnRuleTree *rules=(BFME2RespawnRuleTree *)store;
    void *node=(void *)((RespawnRuleTree *)rules)->_M_find<unsigned int>(defaultRule.level);
    if(node==rules->sentinel) THROW0("RespawnUpdate::iniParseNewRuleForLevel -- You cannot parse a 'RespawnEntry' before 'RespawnRules'. Please add a 'RespawnRules' -- which represents level 1.")
    defaultRule=*(const RespawnRule *)((const char *)node+0x10);
    RespawnRule rule;
    initializeRespawnRule(rule,0);
    const char *token=ini->getNextToken(ini->colon);
    if(!token || _strcmpi(token,"Level")!=0) THROW1("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry expecting 'Level' entry. You specified %s.",token)
    if(strcmp(token,"Level")!=0) THROW1("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry for 'Level' is case sensitive. You specified %s.",token)
    INI::dup_002EF72(ini,instance,&rule.level,0);
    if(((RespawnRuleTree *)rules)->_M_find<unsigned int>(rule.level) != rules->sentinel) THROW1("RespawnUpdate::iniParseNewRuleForLevel -- Multiple 'RespawnEntry' with the same level of %d. You may only have one!",rule.level)
    rule.autoSpawn=defaultRule.autoSpawn;
    rule.cost=defaultRule.cost;
    rule.time=defaultRule.time;
    rule.health=defaultRule.health;
    token=ini->getNextTokenOrNull(ini->colon);
    bool gotAuto=false,gotCost=false,gotTime=false,gotHealth=false;
    while(token) {
        if(_strcmpi(token,"AutoSpawn")==0) {
            if(gotAuto) THROW1("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'AutoSpawn:Yes' or 'AutoSpawn:No' exists multiple times. Please remove one!",rule.level)
            if(strcmp(token,"AutoSpawn")!=0) THROW2("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'AutoSpawn:Yes' or 'AutoSpawn:No' is case sensitive. You specified %s.",rule.level,token)
            INI::parseBool(ini,instance,&rule.autoSpawn,0);
            gotAuto=true;
        } else if(strcmp(token,"Cost")==0) {
            if(gotCost) THROW1("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Cost' exists multiple times. Please remove one!",rule.level)
            if(strcmp(token,"Cost")!=0) THROW2("RespawnUpdate::iniParseNewRuleForLevel -- RespawnRules Level:%d entry for 'Cost' is case sensitive. You specified %s.",rule.level,token)
            INI::dup_002EF72(ini,instance,&rule.cost,0);
            gotCost=true;
        } else if(strcmp(token,"Time")==0) {
            if(gotTime) THROW1("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d Level:%d entry for 'Cost' exists multiple times. Please remove one!",rule.level)
            if(strcmp(token,"Time")!=0) THROW2("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Time' is case sensitive. You specified %s.",rule.level,token)
            INI::parseInt(ini,instance,&rule.time,0);
            gotTime=true;
        } else if(strcmp(token,"Health")==0) {
            if(gotHealth) THROW1("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Cost' exists multiple times. Please remove one!",rule.level)
            if(strcmp(token,"Health")!=0) THROW2("RespawnUpdate::iniParseNewRuleForLevel -- RespawnEntry Level:%d entry for 'Health' is case sensitive. You specified %s.",rule.level,token)
            INI::parsePercentToReal(ini,instance,&rule.health,0);
            gotHealth=true;
        }
        token=ini->getNextTokenOrNull(ini->colon);
    }
    rules->insert(rule);
}
