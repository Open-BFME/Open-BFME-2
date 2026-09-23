// cl: /O1 /DNDEBUG /MD /GX
//
// ??0KeepObjectDie@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00486D73,
// 165 bytes. Behavior-side ctor completing the KeepObjectDie file-unit
// (ModuleData ctor/proc/factory/poolkey rowed at 0x253B78/0x253B95/0x253BB7/
// 0x486C95; behavior factory rowed at 0x24CBD9 news 0x14 with this pinned
// 2-arg ctor).
//
// Zero Hour donor
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/KeepObjectDie.cpp:
// trivial DieModule-base-only ctor) plus the BFME2-only selectable check the
// retail bytes prove:
// - DieModule base resolves via the established ??0DieModule pin at
//   0x0045CEBD (same base call as the rowed FXListDie ctor at 0x4865DD, whose
//   three vtable stores at +0/+0xC/+0x10 this body repeats).
// - The guard is two direct loads, no isKindOf call: thing+4 is the template
//   (Thing::m_template, as in CreateCrateDie.cpp) and template+0x108 is the
//   kind-flags byte (ThingTemplate::m_kindFlags, as in Handicap.cpp and
//   InGameUI_selectMatchingAcrossMap.cpp); bit 1 is KINDOF_SELECTABLE
//   (second KindOf, per KindOf.h).
// - The name in the message is template+0x64 (ThingTemplate::m_nameString,
//   AsciiString), evaluated first like the GameLODManager debug tail.
// - The reporting tail logs through Debug virtuals plus the matched
//   Debug/StringBase operator<< at 0x000028E8: slot60(), 3-arg slot6C,
//   operator<< with the template name, slot38 literal, slot4C(2). The enabled
//   check resolves via the _bfme_debugReportingEnabled alias pin at
//   0x000387C0; the record call reuses the established Debug::SkipNext pin
//   at 0x00038790. Shape mirrors GameLODManagerGetAudioLODIndex.cpp.
// - TheDebug is extern-undefined (its DIR32 patches from retail, as in
//   Debug_recordCallsite.cpp).

class Thing;
class ModuleData;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &that);

private:
	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
	friend class KeepObjectDie;
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString() {}
};

class Debug
{
public:
	static bool SkipNext(bool skip);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug &slot6C(int first, int second, int third);
};

template <typename T> Debug &operator<<(Debug &debug, const StringBase<T> &text);

extern Debug *TheDebug;

bool _bfme_debugReportingEnabled(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	unsigned char m_beforeName[0x64];
	AsciiString m_nameString;
	unsigned char m_afterName[0x108 - 0x64 - 4];
	unsigned char m_kindFlags;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void *m_vptr;
	ThingTemplate *m_template;

	const ThingTemplate *getTemplate(void) const
	{
		return m_template;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
	ObjectModule(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleInterface
{
public:
	virtual void dieModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModule : public ObjectModule,
	public BehaviorModuleInterface,
	public DieModuleInterface
{
public:
	DieModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DieModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/KeepObjectDie.h
class KeepObjectDie : public DieModule
{
public:
	KeepObjectDie(Thing *thing, const ModuleData *moduleData);
	virtual ~KeepObjectDie();
};

// ??0KeepObjectDie@@QAE@PAVThing@@PBVModuleData@@@Z @0x00486D73
KeepObjectDie::KeepObjectDie(Thing *thing, const ModuleData *moduleData) :
	DieModule(thing, moduleData)
{
	if ((thing->getTemplate()->m_kindFlags & 2) == 0)
	{
		if (_bfme_debugReportingEnabled())
		{
			Debug::SkipNext(true);
			TheDebug->slot60();
			operator<<(TheDebug->slot6C(0, 0, 0), thing->getTemplate()->m_nameString).slot38(": Objects with KeepObjectDie should be KindOf SELECTABLE\n").slot4C(2);
		}
	}
}
