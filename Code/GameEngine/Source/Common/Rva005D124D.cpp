// cl: /MD
// ?rva005D124D@Rva005D124D@@QAEHXZ @0x005D124D 8B: forwarding thunk that tail-jumps to slot1 of object at +8. Evidence: unlock lane; caller 0x0023BEE8; callees none rowed virtual dispatch.
class Inner005D124D
{
public:
	virtual void v00();
	virtual int target();
};
class Rva005D124D
{
public:
	int rva005D124D();
private:
	void *m_00;
	void *m_04;
	Inner005D124D *m_08;
};
int Rva005D124D::rva005D124D()
{
	return m_08->target();
}
