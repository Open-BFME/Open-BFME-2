// cl: /DNDEBUG /MD /EHsc
// ?Rva004A9975Check@@YA_NPAX@Z @0x004A9975 70B: free predicate over an AIUpdate machine.
// Evidence: leaf lane; caller 0x004A99D7; rowed callee getCurrentStateID 0x00262FC3 on the +0x258 machine;
// slot-12 virtual on its +0x3E8 subobject; true when that predicate holds or the state id is 0xE or 0x2F.
class AIUpdateInterface
{
public:
	int getCurrentStateID() const;
};

class Machine3e8
{
public:
	virtual void wt00();
	virtual void wt01();
	virtual void wt02();
	virtual void wt03();
	virtual void wt04();
	virtual void wt05();
	virtual void wt06();
	virtual void wt07();
	virtual void wt08();
	virtual void wt09();
	virtual void wt10();
	virtual void wt11();
	virtual bool pred();
};

struct Holder
{
	char m_pad[0x3E8];
	Machine3e8 m_3e8;
};

struct ChainC
{
	char m_pad[0x258];
	Holder *m_ptr;
};

struct ChainB
{
	char m_pad[0x14];
	ChainC *m_ptr;
};

struct ChainA
{
	char m_pad[0x18];
	ChainB *m_ptr;
};

bool Rva004A9975Check(void *arg)
{
	Holder *holder = ((ChainA *)arg)->m_ptr->m_ptr->m_ptr;
	if (!holder)
		return false;
	int state = ((AIUpdateInterface *)holder)->getCurrentStateID();
	return holder->m_3e8.pred() || state == 0x0E || state == 0x2F;
}
