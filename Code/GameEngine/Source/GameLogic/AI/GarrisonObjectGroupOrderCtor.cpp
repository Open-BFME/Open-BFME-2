// cl: /MD
// ??0GarrisonObjectGroupOrder@@QAE@XZ @0x00546C57 40B evidence: stores vtable 0x0086A3C4; base ctor rowed 0x005488C5; clears ObjectID at +0x18 then 3 floats at +0x1c +0x20 +0x24 via xorps-movss; caller 0x00354FFA; returns this.
// Ctor of GarrisonObjectGroupOrder via vtable store (naming rule).
enum ObjectID
{
	OBJECTID_0 = 0
};

class Rva0036E346;
class GroupOrder
{
public:
	GroupOrder(Rva0036E346 *holder);
	GroupOrder();
	GroupOrder(const GroupOrder &other);
protected:
	void *m_vtable; // +0x00 +0
	char m_pad04[0x14];
};

extern "C" const void *const __identifier("??_7GarrisonObjectGroupOrder@@6B@")[];
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
	*(const void **)this = __identifier("??_7GarrisonObjectGroupOrder@@6B@");
	m_1c[0] = 0.0f;
	m_1c[1] = 0.0f;
	m_1c[2] = 0.0f;
}

GarrisonObjectGroupOrder::GarrisonObjectGroupOrder(const GarrisonObjectGroupOrder &other)
	: GroupOrder(other)
{
	m_18 = OBJECTID_0;
	_ReadWriteBarrier();
	*(const void **)this = __identifier("??_7GarrisonObjectGroupOrder@@6B@");
	m_1c[0] = 0.0f;
	m_1c[1] = 0.0f;
	m_1c[2] = 0.0f;
}

