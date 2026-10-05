// cl: /O1 /MD /arch:SSE
// ??0GarrisonObjectGroupOrder@@QAE@PAVRva0036E346@@H@Z @0x00546C26 49B evidence: stores vtable 0x00C6A3C4; base holder ctor rowed 0x00548A25; ObjectID at +0x18 from int arg then 3 floats at +0x1c +0x20 +0x24 via xorps-movss; caller 0x00355A32 news 0x28; abuts 0x00546C57.
// Honest-address ctor: vtable 0x00C6A3C4 is not tied to a known class, so Rva name (neighbor GarrisonObjectGroupOrder stores 0x0086A3C4).
enum ObjectID
{
	OBJECTID_0 = 0
};

class Rva0036E346;

class GroupOrder
{
public:
	GroupOrder(Rva0036E346 *holder);

protected:
	void *m_vtable; // +0
private:
	unsigned char m_pad04[0x18 - 4];
};

extern const void *const g_00C6A3C4[];

class GarrisonObjectGroupOrder : public GroupOrder
{
public:
	GarrisonObjectGroupOrder(Rva0036E346 *holder, int val);
private:
	enum ObjectID m_18;
	float m_1c[3];
};

GarrisonObjectGroupOrder::GarrisonObjectGroupOrder(Rva0036E346 *holder, int val)
	: GroupOrder(holder)
{
	m_18 = (enum ObjectID)val;
	*(const void **)this = g_00C6A3C4;
	m_1c[0] = 0.0f;
	m_1c[1] = 0.0f;
	m_1c[2] = 0.0f;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00C6A3C4@@3QBQBXB=??_7GarrisonObjectGroupOrder@@6B@")
