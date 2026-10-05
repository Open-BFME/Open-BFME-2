// cl: /O1 /MD /arch:SSE
// ??0GarrisonObjectGroupOrder@@QAE@XZ @0x00546C57 40B evidence: stores vtable 0x0086A3C4; base ctor rowed 0x005488C5; clears ObjectID at +0x18 then 3 floats at +0x1c +0x20 +0x24 via xorps-movss; caller 0x00354FFA; returns this.
// Ctor of GarrisonObjectGroupOrder via vtable store (naming rule).
enum ObjectID
{
	OBJECTID_0 = 0
};

class GroupOrder
{
public:
	GroupOrder();
	GroupOrder(const GroupOrder &other);

protected:
	void *m_vtable; // +0
private:
	unsigned char m_pad04[0x18 - 4];
};

extern const void *const g_0086A3C4[];
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	GarrisonObjectGroupOrder();
	GarrisonObjectGroupOrder(const GarrisonObjectGroupOrder &other);
private:
	enum ObjectID m_18;
	float m_1c[3];
};

GarrisonObjectGroupOrder::GarrisonObjectGroupOrder()
{
	m_18 = OBJECTID_0;
	_ReadWriteBarrier();
	*(const void **)this = g_0086A3C4;
	m_1c[0] = 0.0f;
	m_1c[1] = 0.0f;
	m_1c[2] = 0.0f;
}

GarrisonObjectGroupOrder::GarrisonObjectGroupOrder(const GarrisonObjectGroupOrder &other)
	: GroupOrder(other)
{
	m_18 = OBJECTID_0;
	_ReadWriteBarrier();
	*(const void **)this = g_0086A3C4;
	m_1c[0] = 0.0f;
	m_1c[1] = 0.0f;
	m_1c[2] = 0.0f;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_0086A3C4@@3QBQBXB=??_7GarrisonObjectGroupOrder@@6B@")
