// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateIsBuildingEmpty@ScriptConditions@@IAE_NPAVParameter@@@Z
// @0x003E4079 54B. ZH donor: GeneralsMD ScriptConditions.cpp
// evaluateIsBuildingEmpty. Target evidence: the evaluateCondition jump table
// (0x007EC5C0) sends case 78 here, which initConditionTemplates names
// NAMED_BUILDING_IS_EMPTY. BFME2 differences: the unit lookup takes the
// Parameter (rowed getUnitNamed 0x003588E7), the contain module sits at
// Object +0x250, and the contain count is vslot +0x114 with one extra zero
// argument whose meaning is not asserted.
#include "ascii_string.h"
class Parameter
{
public:
    const AsciiString &getString() const { return m_string; }
    unsigned char m_beforeInt[8]; int m_int; float m_real; AsciiString m_string;
    unsigned char m_afterString[8];
};
class ContainModuleInterface
{
public:
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual void s48();
    virtual void s49();
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void s54();
    virtual void s55();
    virtual void s56();
    virtual void s57();
    virtual void s58();
    virtual void s59();
    virtual void s60();
    virtual void s61();
    virtual void s62();
    virtual void s63();
    virtual void s64();
    virtual void s65();
    virtual void s66();
    virtual void s67();
    virtual void s68();
    virtual unsigned int getContainCount(int extra) const; // +0x114
};
class Object
{
public:
    ContainModuleInterface *getContain() const { return m_contain; }
    unsigned char m_pad000[0x250];
    ContainModuleInterface *m_contain;
};
class ScriptEngine
{
public:
    Object *getUnitNamed(Parameter *);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
    bool evaluateIsBuildingEmpty(Parameter *);
};
bool ScriptConditions::evaluateIsBuildingEmpty(Parameter *pItemParm)
{

    Object *theBuilding = TheScriptEngine->getUnitNamed(pItemParm);
    if (!theBuilding) {
        return false;
    }

    ContainModuleInterface *contain = theBuilding->getContain();
    if (!contain) {
        return false;
    }
    if (contain->getContainCount(0) > 0) {
        return false;
    }
    return true;
}
