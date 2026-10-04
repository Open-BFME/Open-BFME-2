// cl: /O1 /DNDEBUG /MD
//
// Thin LargeGroupAudioUpdate overrides in the vtables its matched ctor
// 0x004AB811 installs: primary 0x00C549BC, +0x20 0x00C548E8 and +0x24
// 0x00C548B8 (the +0x20/+0x24 slots compiled with their subobject this).
// Names are by address. The two members they reach are pinned: 0x004AB90A
// (when +0x8D is clear: raises it, registers the +0x24 interface with the
// "LargeGroupAudio" subsystem and copies the owner's position and condition
// state) and 0x004AB9A2 (when +0x8D is set: unregisters, sleeps forever and
// clears it).

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
	Rva004ABA81Pair(const Rva004ABA81Pair &o) : x(o.x), y(o.y) {}
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
	unsigned short m_1C; // +0x1C
};

class BehaviorModule : public Rva004ABB37Slots<5>
{
public:
	virtual void rva004ABB37() = 0;
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
	unsigned char m_pad14[0x20 - 0x14];
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
	virtual Rva004ABA81Pair rva004ABA93() const = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual unsigned short rva004ABABC() = 0;
	virtual void gap7() = 0;
	virtual bool rva004ABACB() = 0;
};

class LargeGroupAudioUpdate : public BehaviorModule, public BehaviorModuleInterface,
	public UpdateModuleInterface, public Rva004ABA71Iface, public Rva004ABABCIface
{
public:
	virtual void rva004ABB37();
	virtual void rva004ABB46();
	virtual void rva004ABA71();
	virtual void rva004ABA79();
	virtual unsigned short rva004ABABC();
	virtual bool rva004ABACB();
	virtual Rva004ABA81Pair rva004ABA81() const;
	virtual Rva004ABA81Pair rva004ABA93() const;
	void rva004AB90A();
	void rva004AB9A2();
private:
	Rva004ABA81Pair m_28; // +0x28
	unsigned char m_pad30[0x8D - 0x30];
	bool m_8D; // +0x8D
};

// ?rva004ABB37@LargeGroupAudioUpdate@@UAEXXZ, retail 0x004ABB37, 15 bytes:
// primary slot 5.
void LargeGroupAudioUpdate::rva004ABB37()
{
	if (!m_8D)
		rva004AB90A();
}

// ?rva004ABB46@LargeGroupAudioUpdate@@UAEXXZ, retail 0x004ABB46, 5 bytes:
// primary slot 8.
void LargeGroupAudioUpdate::rva004ABB46()
{
	rva004AB9A2();
}

// ?rva004ABA71@LargeGroupAudioUpdate@@UAEXXZ, retail 0x004ABA71, 8 bytes: +0x20
// slot 0.
void LargeGroupAudioUpdate::rva004ABA71()
{
	rva004AB9A2();
}

// ?rva004ABA79@LargeGroupAudioUpdate@@UAEXXZ, retail 0x004ABA79, 8 bytes: +0x20
// slot 1.
void LargeGroupAudioUpdate::rva004ABA79()
{
	rva004AB90A();
}

// ?rva004ABABC@LargeGroupAudioUpdate@@UAEGXZ, retail 0x004ABABC, 8 bytes: +0x24
// slot 6, the module data's +0x1C word.
unsigned short LargeGroupAudioUpdate::rva004ABABC()
{
	return ((const LargeGroupAudioUpdateModuleData *)m_moduleData)->m_1C;
}

// ?rva004ABACB@LargeGroupAudioUpdate@@UAE_NXZ, retail 0x004ABACB, 11 bytes: +0x24
// slot 8, the rowed Object::rva002943B2 for no player.
bool LargeGroupAudioUpdate::rva004ABACB()
{
	return m_object->rva002943B2(0);
}

// ?rva004ABA81@LargeGroupAudioUpdate@@UBE?AURva004ABA81Pair@@XZ, retail
// 0x004ABA81, 18 bytes: +0x24 slot 0, the pair at +0x28.
Rva004ABA81Pair LargeGroupAudioUpdate::rva004ABA81() const
{
	return m_28;
}

// ?rva004ABA93@LargeGroupAudioUpdate@@UBE?AURva004ABA81Pair@@XZ, retail
// 0x004ABA93, 23 bytes: +0x24 slot 1, the x/y of the Object's position (+0x38).
Rva004ABA81Pair LargeGroupAudioUpdate::rva004ABA93() const
{
	return *m_object->getPositionPair();
}
