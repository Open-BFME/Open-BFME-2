// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??1SynchronizeGroupOrder@@UAE@XZ, retail 0x005468E1, 59 bytes.
// SynchronizeGroupOrder destructor: reinstalls vtable 0x0086A314, destroys the +0x18
// member through the rowed ??1Rva002EE9B7 (state 0), then calls the rowed
// base ??1GroupOrder at 0x00548948 (state -1). Layout from the
// rowed ctor 0x00546982 in SynchronizeGroupOrderCtor.cpp (GroupOrder base
// 0x18, member at +0x18, bool at +0x24). Member is the opaque rowed tree/pool
// type so the call mangles to the row name and links; vtable immediate is
// DIR32.

class GroupOrder
{
public:
	virtual ~GroupOrder();

private:
	unsigned char m_pad04[0x18 - 4];
};

class Rva002EE9B7
{
public:
	~Rva002EE9B7();

private:
	void *m_header;
	int m_flag;
};

class SynchronizeGroupOrder : public GroupOrder
{
public:
	virtual ~SynchronizeGroupOrder();

private:
	Rva002EE9B7 m_18; // +0x18
	int m_pad20; // +0x20, set in the ctor TU is 12 bytes here
	bool m_24; // +0x24
};

// ??1SynchronizeGroupOrder@@UAE@XZ @0x005468E1
SynchronizeGroupOrder::~SynchronizeGroupOrder()
{
}
