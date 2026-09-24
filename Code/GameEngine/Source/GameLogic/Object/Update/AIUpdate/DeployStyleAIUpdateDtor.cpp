// cl: /O1 /GX /DNDEBUG /MD
//
// ??1DeployStyleAIUpdate@@UAE@XZ, retail 0x0048E852 (90 bytes). Destructor
// over the MI Transport base (five vptrs at +0x00/+0x0C/+0x10/+0x20/+0x24,
// implicitly reinstalled here; base teardown is the pinned opaque SEH dtor
// at 0x26E836): destroys the +0x3E4 member through the rowed
// Rva0026AFDAMember dtor, then the base. The empty body is load-bearing:
// explicit statements would reschedule the EH arming ahead of the implicit
// vptr installs. Sole caller is the scalar-deleting dtor at 0x48E9F3.
class Thing;
class ModuleData;

class DBaseRoot
{
public:
	virtual ~DBaseRoot();

private:
	char m_pad04[8];
};

class DBaseM1
{
public:
	virtual void f1();
};

class DBaseB2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class DBaseM3
{
public:
	virtual void f3();
};

class DBaseM4
{
public:
	virtual void f4();
};

class Rva0026E9BDBase : public DBaseRoot, public DBaseM1, public DBaseB2, public DBaseM3, public DBaseM4
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0026E9BDBase();
};

class Rva0026AFDAMember
{
public:
	~Rva0026AFDAMember();

private:
	unsigned char m_pad[0xC4];
};

class DeployStyleAIUpdate : public Rva0026E9BDBase
{
public:
	DeployStyleAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~DeployStyleAIUpdate();

protected:
	unsigned char m_pad28[0x3E4 - 0x28];
	Rva0026AFDAMember m_member3E4;		// +0x3E4
};

// ??1DeployStyleAIUpdate@@UAE@XZ @0x48E852
DeployStyleAIUpdate::~DeployStyleAIUpdate()
{
}
