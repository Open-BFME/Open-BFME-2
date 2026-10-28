// Shared TU-scoped declaration from the seed and random-delay donor.
// Existing seed hierarchy and target member offsets are preserved.
#ifndef BFME_LARGE_GROUP_AUDIO_UPDATE_VIEW_H
#define BFME_LARGE_GROUP_AUDIO_UPDATE_VIEW_H

class Object;

class Player;

class ModuleData;

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
struct Rva004ABA81Pair
{
	Rva004ABA81Pair() {}
	Rva004ABA81Pair(const Rva004ABA81Pair &other) : x(other.x), y(other.y) {}
	float x;
	float y;
};

class Object
{
public:
	bool rva002943B2(const Player *player);
	const Rva004ABA81Pair *getPositionPair() const { return &m_position; }
private:
	unsigned char m_pad00[0x38];
	Rva004ABA81Pair m_position; // +0x38
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
	virtual void updateModuleInterfaceAnchor();
	int m_14; // +0x14, random-delay base
	int m_18; // +0x18, random-delay range
	unsigned char m_pad1C[0x20 - 0x1C];
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

class LargeGroupAudioUpdate : public BehaviorModule, public BehaviorModuleInterface,
	public UpdateModuleInterface, public Rva004ABA71Iface, public Rva004ABABCIface
{
public:
	virtual void onObjectCreated();
	virtual void rva004ABB46();
	virtual void rva004ABA71();
	virtual void rva004ABA79();
	virtual unsigned short getUnitWeight();
	virtual bool rva004ABACB();
	virtual Rva004ABA81Pair rva004ABA81() const;
	virtual Rva004ABA81Pair getPosition() const;
	int rva004AB7C8() const;
	void rva004AB90A();
	void rva004AB9A2();
private:
	Rva004ABA81Pair m_28; // +0x28
	unsigned char m_pad30[0x8D - 0x30];
	bool m_8D; // +0x8D
public:
	virtual NameKeyType getModuleNameKey() const;
};

#endif
