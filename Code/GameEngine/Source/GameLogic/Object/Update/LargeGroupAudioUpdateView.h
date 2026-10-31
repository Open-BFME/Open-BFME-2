// Shared class views for the LargeGroupAudioUpdate translation unit.
// Module interfaces and member offsets follow the matched retail bodies.
#ifndef BFME_LARGE_GROUP_AUDIO_UPDATE_VIEW_H
#define BFME_LARGE_GROUP_AUDIO_UPDATE_VIEW_H

class Object;

class Player;

class ModuleData;
class Thing;
class Xfer;

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

template <int N> class BitFlags
{
public:
	void xfer(Xfer *xfer);
	unsigned int m_words[(N + 31) / 32];
};

template <int N> class Rva004ABB37Slots : public Rva004ABB37Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class Rva004ABB37Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

// An 8-byte x/y pair returned through a hidden pointer, so not a POD in
// retail's source; its member-wise copy is what loads x through the FPU.
struct Rva004ABA81Pair : public Coord2D
{
	Rva004ABA81Pair() {}
	Rva004ABA81Pair(const Rva004ABA81Pair &other) { x = other.x; y = other.y; }
};

class Object
{
public:
	bool rva002943B2(const Player *player);
	const Rva004ABA81Pair *getPositionPair() const { return &m_position; }
	unsigned char m_pad00[0x38];
	Rva004ABA81Pair m_position; // +0x38
	unsigned char m_pad40[0x94 - 0x40];
	BitFlags<101> m_94;
	unsigned char m_padA4[0x10C - 0xA4];
	BitFlags<591> m_10C;
};

struct LargeGroupAudioUpdateModuleData
{
	unsigned char m_pad00[0x1C];
	unsigned short m_unitWeight; // +0x1C
};

class BehaviorModule : public Rva004ABB37Slots<5>
{
public:
	virtual void onObjectCreated() = 0;
	virtual void gap6() = 0;
	virtual void gap7() = 0;
	virtual void rva004ABB46() = 0;
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	int m_14; // +0x14, random-delay base
	int m_18; // +0x18, random-delay range
	unsigned char m_pad1C[0x20 - 0x1C];
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
};

class Rva004ABA71Iface
{
public:
	virtual void rva004ABA71() = 0;
	virtual void rva004ABA79() = 0;
};

class Rva004ABABCIface
{
public:
	virtual Rva004ABA81Pair rva004ABA81() const = 0;
	virtual Rva004ABA81Pair getPosition() const = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual unsigned short getUnitWeight() = 0;
	virtual void gap7() = 0;
	virtual bool rva004ABACB() = 0;
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class LargeGroupAudioUpdate : public UpdateModule, public Rva004ABA71Iface,
	public Rva004ABABCIface
{
public:
	LargeGroupAudioUpdate(Thing *thing, const ModuleData *moduleData);
	virtual void onObjectCreated();
	virtual void rva004ABB46();
	virtual void rva004ABA71();
	virtual void rva004ABA79();
	virtual unsigned short getUnitWeight();
	virtual bool rva004ABACB();
	virtual Rva004ABA81Pair rva004ABA81() const;
	virtual Rva004ABA81Pair getPosition() const;
	virtual UpdateSleepTime update();
	int rva004AB7C8() const;
	void rva004AB90A();
	void rva004AB9A2();
protected:
	virtual void xfer(Xfer *xfer);
private:
	Rva004ABA81Pair m_28; // +0x28
	BitFlags<591> m_30;
	BitFlags<101> m_7C;
	bool m_8C;
	bool m_8D; // +0x8D
	int m_90;
public:
	virtual NameKeyType getModuleNameKey() const;
};

#endif
