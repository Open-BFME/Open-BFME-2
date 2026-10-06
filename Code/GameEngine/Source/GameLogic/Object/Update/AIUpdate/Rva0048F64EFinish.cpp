// ?rva0048F64E@AssaultTransportAIUpdate@@QAE_NPAX@Z
// cl: /DNDEBUG /MD
//
// ?rva0048F64E@AssaultTransportAIUpdate@@QAE_NPAX@Z @0x0048F64E 66B
// __thiscall predicate on AssaultTransportAIUpdate: arg+0x254 slave provides
// two float virtuals at +0x10 and +0x18 (ratio a/b); this+4 master provides
// float at +0x64 threshold; returns threshold > ratio, false on null slave.
// Neighbours AssaultTransportAIUpdateCheck/ PassengerHelper share // cl and
// class; callers at 0x0048F9A7 0x0048FAA6 in 0x0048F828. /arch:SSE is what
// selects retail's fcomip float guard: plain /O1 emits the fnstsw/parity form
// three bytes shorter (63B). The Helper sibling TU carries the same flag.
class Rva0048F64ESlave
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual float GetA();
	virtual void v05();
	virtual float GetB();
};
struct Rva0048F64EMaster
{
	unsigned char m_pad[0x64];
	float m64;
};
class AssaultTransportAIUpdate
{
public:
	bool rva0048F64E(void *arg);
private:
	int m00;
	Rva0048F64EMaster *m04;
};
bool AssaultTransportAIUpdate::rva0048F64E(void *arg)
{
	Rva0048F64ESlave *slave = *(Rva0048F64ESlave **)((char *)arg + 0x254);
	Rva0048F64EMaster *master = m04;
	if (slave != 0) {
		float a = slave->GetA();
		float b = slave->GetB();
		float ratio = a / b;
		if (ratio < master->m64)
			return true;
	}
	return false;
}
