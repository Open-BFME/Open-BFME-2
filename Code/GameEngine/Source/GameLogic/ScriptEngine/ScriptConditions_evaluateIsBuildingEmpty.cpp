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
class Rva003E8863ContainedItems;
class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual bool isGarrisonable() const; // +0x10
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
	virtual unsigned int getContainCount(int extra) const; // +0x114
	virtual Rva003E8863ContainedItems getContainedItems() const; // +0x118
};
class Object
{
public:
    // Keep the native +0x250 load inline; omit the competing legacy getter.
    __declspec(dllimport) __forceinline ContainModuleInterface *getContain() const { return m_contain; }
    unsigned char m_pad000[0x250];
    ContainModuleInterface *m_contain;
};
#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;
#include "../../../Include/GameLogic/ScriptConditions.h"
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
