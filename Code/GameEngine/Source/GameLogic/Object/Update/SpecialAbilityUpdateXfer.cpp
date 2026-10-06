// cl: /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// ?xfer@SpecialAbilityUpdate@@MAEXPAVXfer@@@Z, retail 0x0044F996, 402 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0083FBA8 (class of rowed
// ??1SpecialAbilityUpdate@@UAE@XZ in SpecialAbilityUpdateDtor.cpp).
//
// Donor: ZH SpecialAbilityUpdate.cpp xfer (Version plus base UpdateModule
// xfer plus bool/uint/ObjectID/Coord/int/list/entries/bool/user/bool/float)
// plus BFME2 FlammableUpdateXfer recipe (base UpdateModule xfer via rowed
// 0x0044DF9F then IsLightCRC early-out via Xfer slot 0x10 then Version(1,3)
// via Xfer slot 0x28 reusing [ebp+8] then TheAudio xferAudioHandle at
// AudioManager slot 0x160 for two handles plus version-gated tail).
// Layout is the rowed 0x88-byte class from ctor 0x0044EF5E and friendNew
// 0x0024A847 (UpdateModule base 0x20 plus trailing vptr at +0x20 giving
// +0x24 start plus list<int> at +0x64 plus uint at +0x68 plus float at +0x70
// plus 9 bools plus two audio handles plus gated Coord/uint/int tail).
// Callers include 0x00490CA4 0x00492606 0x00492E31 0x00494E78 0x0049C425.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef unsigned int AudioHandle;

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

#define TheAudio (*(AudioManager *const *)0x00DFE6E8)

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

typedef _STL::list<int> ListInt;

Xfer *Rva0036ABAFXfer(Xfer *xfer, ListInt *list);

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual void updateSlot(); };

class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class SpecialTrailing { public: virtual void trailingSlot(); };

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad00[0x1C];
	int m_val1C;
};
class TextureClass;
class MaterialPassClass
{
public:
	TextureClass *Peek_Texture(int i) const;
};
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum WeaponLockType
{
	WEAPONLOCK_LOCKED = 1
};
class Object
{
public:
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	char m_pad00[0x330];
	MaterialPassClass m_pass330;
};
struct ModuleDataFull
{
	char m_pad00[0x38];
	Overridable *m_override38;
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialTrailing
{
public:
	void rva0044F72E();
protected:
	virtual void xfer(Xfer *xfer);
	void validateSpecialObjects();

private:
	int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	AudioHandle m_34;
	AudioHandle m_38;
	unsigned int m_3C;
	ObjectID m_40;
	Coord3DBase m_44;
	Coord3DBase m_50;
	int m_5C;
	int m_60;
	ListInt m_64;
	unsigned int m_68;
	unsigned int m_6C;
	float m_70;
	bool m_74;
	unsigned int m_78;
	bool m_7C;
	bool m_7D;
	bool m_7E;
	bool m_7F;
	bool m_80;
	bool m_81;
	bool m_82;
	bool m_83;
	unsigned int m_84;
};

void SpecialAbilityUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 3);
	*xfer == version;
	*xfer == m_74;
	*xfer == m_3C;
	*xfer == m_28;
	XferObjectID(xfer, &m_40);
	*xfer == m_44;
	*xfer == m_5C;
	*xfer == m_24;
	*xfer == m_2C;
	Rva0036ABAFXfer(xfer, &m_64);
	*xfer == m_68;
	*xfer == m_7D;
	xfer->XferRawBytes(&m_30, 4);
	*xfer == m_7E;
	*xfer == m_7F;
	*xfer == m_80;
	*xfer == m_81;
	*xfer == m_70;
	*xfer == m_82;
	*xfer == m_83;
	*xfer == m_7C;
	TheAudio->xferAudioHandle(xfer, &m_34);
	TheAudio->xferAudioHandle(xfer, &m_38);
	if (version.m_minimum > 1) {
		*xfer == m_78;
		*xfer == m_50;
	}
	if (version.m_minimum >= 3) {
		*xfer == m_60;
	}
}

void SpecialAbilityUpdate::validateSpecialObjects()
{
	ListInt::iterator it = m_64.begin();
	while (it != m_64.end()) {
		ListInt::iterator prev = it;
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*it);
		++it;
		if (!obj) {
			m_64.erase(prev);
			--m_68;
		}
	}
}

void SpecialAbilityUpdate::rva0044F72E()
{
	const ModuleDataFull *md = (const ModuleDataFull *)m_moduleData;
	Overridable *holder = md->m_override38;
	int zero = 0;
	for (ListInt::iterator it = m_64.begin(); it != m_64.end(); ++it) {
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*it);
		if (obj)
			TheGameLogic->destroyObject(obj);
	}
	m_64.clear();
	m_68 = zero;
	const Overridable *ov = holder->friend_getFinalOverride();
	if (ov->m_val1C != 0x15)
		return;
	Object *o = m_object;
	if (o->m_pass330.Peek_Texture(zero) == 0)
		return;
	o->setWeaponLock((WeaponSlotType)zero, (WeaponLockType)1);
}
