// cl: /O1 /DNDEBUG /MD
//
// FakePathfindPortalBehaviour slot 0 of its +0x20 interface table 0x00C42B50,
// retail 0x0046190A (19 bytes), so `this` is that subobject: the pinned
// rva0046183B (which the class dtor 0x004619F2 also runs) on the primary
// this, then the byte at +0x31 is raised. The argument is unused. Named by
// address.
class ModuleData;
class Object;
class FakePathfindPortalBehaviourBase
{
public:
	virtual ~FakePathfindPortalBehaviourBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
};
class Rva00C42B50Iface
{
public:
	virtual void rva0046190A(void *arg) = 0;
};
class FakePathfindPortalBehaviour : public FakePathfindPortalBehaviourBase, public Rva00C42B50Iface
{
public:
	virtual void rva0046190A(void *arg);
	void rva0046183B();
private:
	unsigned char m_pad24[0x31 - 0x24];
	bool m_31;			// +0x31
};
void FakePathfindPortalBehaviour::rva0046190A(void *arg)
{
	rva0046183B();
	m_31 = true;
}
