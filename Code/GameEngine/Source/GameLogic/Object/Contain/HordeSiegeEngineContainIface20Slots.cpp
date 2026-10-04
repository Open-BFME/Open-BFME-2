// cl: /O1 /DNDEBUG /MD
//
// Two HordeSiegeEngineContain overrides in its +0x20 interface vftable
// 0x00C47328 (installed by the matched ctor 0x0047D247 over
// HordeTransportContain), compiled with that subobject this.
//
// ?rva004624EB@HordeSiegeEngineContain@@UAEXAAURva0046247DPair@@@Z, retail
// 0x0047D087, 27 bytes. Slot 71, named after the OpenContain implementation it
// replaces (0x004624EB hands out the interface and a static empty list): the
// interface (null-checked as cl converts) and the list at +0x128.
//
// ?rva0047CADB@HordeSiegeEngineContain@@UAEMXZ, retail 0x0047CADB, 16 bytes.
// Slot 53 (OpenContain's is a folded global float getter): the +0x12C count
// times the module data's +0x19C float. Address name.

class Object;
class ModuleData;

template <int N> class Rva0047CADBSlots : public Rva0047CADBSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0047CADBSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class ContainModuleInterface;

struct Rva0046247DPair
{
	ContainModuleInterface *m00;
	void *m04;
};

class ContainModuleInterface : public Rva0047CADBSlots<53>
{
public:
	virtual float rva0047CADB() = 0;
	virtual void gap54() = 0; virtual void gap55() = 0; virtual void gap56() = 0; virtual void gap57() = 0;
	virtual void gap58() = 0; virtual void gap59() = 0; virtual void gap60() = 0; virtual void gap61() = 0;
	virtual void gap62() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
	virtual void gap66() = 0; virtual void gap67() = 0; virtual void gap68() = 0; virtual void gap69() = 0;
	virtual void gap70() = 0;
	virtual void rva004624EB(Rva0046247DPair &p) = 0;
};

struct HordeSiegeEngineContainModuleData
{
	unsigned char m_pad000[0x19C];
	float m_19C; // +0x19C
};

struct Iface00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface24 { virtual void f24(); unsigned char m_pad[0x11C - 0x28]; };

class TransportContain : public Iface00, public Iface0C, public Iface10, public ContainModuleInterface, public Iface24
{
};

class HordeTransportContain : public TransportContain
{
protected:
	unsigned char m_11C[0x128 - 0x11C];
};

class HordeSiegeEngineContain : public HordeTransportContain
{
public:
	virtual float rva0047CADB();
	virtual void rva004624EB(Rva0046247DPair &p);
private:
	void *m_128; // +0x128 (list head)
	int m_12C; // +0x12C
};

// ?rva0047CADB@HordeSiegeEngineContain@@UAEMXZ @0x0047CADB
float HordeSiegeEngineContain::rva0047CADB()
{
	return m_12C * ((const HordeSiegeEngineContainModuleData *)m_moduleData)->m_19C;
}

// ?rva004624EB@HordeSiegeEngineContain@@UAEXAAURva0046247DPair@@@Z @0x0047D087
void HordeSiegeEngineContain::rva004624EB(Rva0046247DPair &p)
{
	p.m00 = this;
	p.m04 = &m_128;
}
