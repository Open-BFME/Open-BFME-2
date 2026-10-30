// cl: /MD
//
// ?rva0004550DE@FoundationAIUpdate@@QAEXXZ @0x004550DE, 26 bytes.
// Virtual slot 14 (offset 0x38) of vtable 0x00840608 (primary of
// ??1Rva00455050@@UAE@XZ). Class is FoundationAIUpdate: slot 2 at
// 0x00455070 returns "FoundationAIUpdate", slot 4 at 0x00455167 is the
// FoundationAIUpdate pool key, and the ctor at 0x004551B3 installs this
// vtable. Callee is TheAudio (data 0x009FE6E8, proven by getVolume at
// 0x002E4B2D calling getAudioSettings at +0x134 through it) slot 0x6c
// (removeAudioEvent precedent FlammableUpdate). Body passes m_24 then sets
// it to 1 (AHSV_NoSound). Single caller at 0x00489F01 in unclaimed code.

class Thing;
class ModuleData;
class Object;

class Player;
class ThingTemplate;
struct Coord3D;
enum NameKeyType { NK_UNKNOWN=0 };
enum UpdateSleepTime { UPDATE_SLEEP_NONE=1 };
enum ObjectID { INVALID_ID=0 };
template <int N> class Rva00455B42Slots : public Rva00455B42Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00455B42Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};
class BehaviorModule
{
public:
	Object *getObject() const { return m_object; }
	virtual ~BehaviorModule();
	virtual void gap1();
	virtual void gap2();
	virtual void gap3();
	virtual void gap4();
	virtual void gap5();
	virtual void gap6();
	virtual void gap7();
	virtual void gap8();
	virtual void rva00455B67(Player *oldOwner, Player *newOwner) = 0;
	virtual void gap10();
	virtual void gap11();
	virtual void gap12();
	virtual void gap13();
	virtual void gap14();
	virtual void gap15();
protected:
	const ModuleData *m_moduleData; // +0x04 +0x04
	Object *m_object; // +0x08 +0x08
};
class BehaviorModuleInterface : public Rva00455B42Slots<46>
{
public:
	virtual void rva00455B42(int value) = 0;
};
struct UpdateModuleInterface { virtual UpdateSleepTime update()=0; };
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};
class Rva00C1A690Iface
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual void gap2() = 0;
	virtual bool slot3() const = 0;
	virtual Object *rva00456134(void *unused, const ThingTemplate *tmpl, const Coord3D *pos, float angle,
		Player *owner, int a6) = 0;
	virtual void rva00455374() = 0;
	virtual Object *rva00455B33() = 0;
	virtual Object *slot7(const ThingTemplate *tmpl, const Coord3D *pos, float angle, Player *owner,
		int a5, int a6) = 0;
};

typedef unsigned int AudioHandle;

class Xfer;
class AudioManager
{
public:
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void removeAudioEvent(AudioHandle handle) = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual void _pad37() = 0;
	virtual void _pad38() = 0;
	virtual void _pad39() = 0;
	virtual void _pad40() = 0;
	virtual void _pad41() = 0;
	virtual void _pad42() = 0;
	virtual void _pad43() = 0;
	virtual void _pad44() = 0;
	virtual void _pad45() = 0;
	virtual void _pad46() = 0;
	virtual void _pad47() = 0;
	virtual void _pad48() = 0;
	virtual void _pad49() = 0;
	virtual void _pad50() = 0;
	virtual void _pad51() = 0;
	virtual void _pad52() = 0;
	virtual void _pad53() = 0;
	virtual void _pad54() = 0;
	virtual void _pad55() = 0;
	virtual void _pad56() = 0;
	virtual void _pad57() = 0;
	virtual void _pad58() = 0;
	virtual void _pad59() = 0;
	virtual void _pad60() = 0;
	virtual void _pad61() = 0;
	virtual void _pad62() = 0;
	virtual void _pad63() = 0;
	virtual void _pad64() = 0;
	virtual void _pad65() = 0;
	virtual void _pad66() = 0;
	virtual void _pad67() = 0;
	virtual void _pad68() = 0;
	virtual void _pad69() = 0;
	virtual void _pad70() = 0;
	virtual void _pad71() = 0;
	virtual void _pad72() = 0;
	virtual void _pad73() = 0;
	virtual void _pad74() = 0;
	virtual void _pad75() = 0;
	virtual void _pad76() = 0;
	virtual void _pad77() = 0;
	virtual void _pad78() = 0;
	virtual void _pad79() = 0;
	virtual void _pad80() = 0;
	virtual void _pad81() = 0;
	virtual void _pad82() = 0;
	virtual void _pad83() = 0;
	virtual void _pad84() = 0;
	virtual void _pad85() = 0;
	virtual void _pad86() = 0;
	virtual void _pad87() = 0;
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle) = 0;
};

extern AudioManager *TheAudio;

class FoundationAIUpdate : public UpdateModule, public Rva00C1A690Iface
{
public:
	void rva0004550DE();
	virtual void rva00455B67(Player *oldOwner, Player *newOwner);
 bool isRemovableForConstruction(Object *obj);
 virtual void rva0045537F();
 virtual UpdateSleepTime update();

	virtual void rva00455B42(int value);
	virtual Object *rva00456134(void *unused, const ThingTemplate *tmpl, const Coord3D *pos, float angle,
		Player *owner, int a6);
	virtual void rva00455374();
	virtual Object *rva00455B33();
private:
	void rva0045527A(ObjectID id);
	void rva00455BDD(const ThingTemplate *tmpl, const Coord3D *pos, float angle);
	bool rva00455C98(const ThingTemplate *tmpl, const Coord3D *pos, float angle, Player *owner);
	int m_24;
	ObjectID m_28; // +0x28
	bool m_2C;
public:
	virtual NameKeyType getModuleNameKey() const;
};

void FoundationAIUpdate::rva0004550DE()
{
	TheAudio->removeAudioEvent(m_24);
	m_24 = 1;
}
