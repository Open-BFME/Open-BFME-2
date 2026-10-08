// cl: /DNDEBUG /MD
//
// OneRingPenaltyUpdate slot 0 of its +0x20 interface table 0x00C50250, retail
// 0x00499D18 (11 bytes), so `this` is that subobject: runs the class's
// 0x00499C46 (pinned by address) on the primary this; the argument is
// unused. Named by address.
// The callee is the rowed BfmeC987::bfmeGo987C.
class BfmeC987
{
public:
	void bfmeGo987C();
};

class ModuleData;
class Object;
class OneRingPenaltyUpdateBase
{
public:
	virtual ~OneRingPenaltyUpdateBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};
class Rva00C50250Iface
{
public:
	virtual void rva00499D18(void *arg) = 0;
};
class OneRingPenaltyUpdate : public OneRingPenaltyUpdateBase, public Rva00C50250Iface
{
public:
	virtual void rva00499D18(void *arg);
	void rva00499C46();
};
void OneRingPenaltyUpdate::rva00499D18(void *arg)
{
	((BfmeC987 *)this)->bfmeGo987C();
}
