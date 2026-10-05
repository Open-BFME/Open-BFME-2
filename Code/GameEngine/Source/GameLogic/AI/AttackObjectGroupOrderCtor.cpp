// cl: /O1 /MD /arch:SSE
// ??0AttackObjectGroupOrder@@QAE@XZ @0x00546F03 44B evidence: stores vtable 0x0086A420; base ctor rowed 0x005488C5; clears dword at +0x18 then byte at +0x1c then 3 floats at +0x20 +0x24 +0x28 via xorps-movss; caller 0x00354FCC; returns this.
// Ctor of AttackObjectGroupOrder via vtable store (naming rule).
enum ObjectID
{
	OBJECTID_0 = 0
};

class Rva0036E346;

class GroupOrder
{
public:
	GroupOrder();
	GroupOrder(const GroupOrder &other);
	GroupOrder(Rva0036E346 *holder);

protected:
	void *m_vtable; // +0
private:
	unsigned char m_pad04[0x18 - 4];
};

extern const void *const g_0086A420[];
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class AttackObjectGroupOrder : public GroupOrder
{
public:
	AttackObjectGroupOrder();
	AttackObjectGroupOrder(Rva0036E346 *holder, int val);
	AttackObjectGroupOrder(const AttackObjectGroupOrder &other);
private:
	enum ObjectID m_18;
	bool m_1c;
	float m_20[3];
};

AttackObjectGroupOrder::AttackObjectGroupOrder()
{
	m_18 = OBJECTID_0;
	_ReadWriteBarrier();
	*(const void **)this = g_0086A420;
	m_1c = false;
	m_20[0] = 0.0f;
	m_20[1] = 0.0f;
	m_20[2] = 0.0f;
}

AttackObjectGroupOrder::AttackObjectGroupOrder(Rva0036E346 *holder, int val)
	: GroupOrder(holder)
{
	m_18 = (enum ObjectID)val;
	*(const void **)this = g_0086A420;
	m_1c = false;
	m_20[0] = 0.0f;
	m_20[1] = 0.0f;
	m_20[2] = 0.0f;
}

AttackObjectGroupOrder::AttackObjectGroupOrder(const AttackObjectGroupOrder &other)
	: GroupOrder(other)
{
	m_18 = OBJECTID_0;
	_ReadWriteBarrier();
	*(const void **)this = g_0086A420;
	m_1c = false;
	m_20[0] = 0.0f;
	m_20[1] = 0.0f;
	m_20[2] = 0.0f;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_0086A420@@3QBQBXB=??_7AttackObjectGroupOrder@@6B@")
