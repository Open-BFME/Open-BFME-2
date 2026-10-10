// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?evaluateBuildingEntered@ScriptConditions@@IAE_NPAVParameter@@0@Z @0x003E3FFE (123B): unit-player ownership check via +0x250 slot 0x144 mask
// Evidence: neighbours ScriptConditions_evaluateNamedUnit and evaluateIsBuildingEmpty same flags
// rowed getUnitNamed 0x003588E7 pin rva00357B82 rowed getPlayerFromMask getEachPlayerFromMask
// globals TheScriptEngine ThePlayerList caller 0x003EAE3B.
class Parameter;
class Player;
class Rva003E3FFEFace
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
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78();
	virtual void s79();
	virtual void s80();
	virtual int getMask();
};
class Object
{
public:
	unsigned char m_pad[0x250];
	Rva003E3FFEFace *m_face;
};
class PlayerList
{
public:
	Player *getPlayerFromMask(int mask);
	Player *getEachPlayerFromMask(int &maskToAdjust);
};
extern PlayerList *ThePlayerList;
class ScriptEngine
{
public:
	Object *getUnitNamed(Parameter *p);
	int rva00357B82(Parameter *p);
};
extern ScriptEngine *TheScriptEngine;
class ScriptConditions
{
protected:
	bool evaluateBuildingEntered(Parameter *pPlayerParm, Parameter *pUnitParm);
};

bool ScriptConditions::evaluateBuildingEntered(Parameter *pPlayerParm, Parameter *pUnitParm)
{
	Object *obj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (!obj) {
		return false;
	}
	Rva003E3FFEFace *face = obj->m_face;
	if (!face) {
		return false;
	}
	int ownerMask = face->getMask();
	if (!ownerMask) {
		return false;
	}
	Player *owner = ThePlayerList->getPlayerFromMask(ownerMask);
	if (!owner) {
		return false;
	}
	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	while (mask) {
		Player *p = ThePlayerList->getEachPlayerFromMask(mask);
		if (owner == p) {
			return true;
		}
	}
	return false;
}
