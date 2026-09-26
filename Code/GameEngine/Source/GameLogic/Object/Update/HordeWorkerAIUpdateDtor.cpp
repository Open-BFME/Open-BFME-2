// cl: /O1 /DNDEBUG /MD /GX
//
// ??1HordeWorkerAIUpdate@@UAE@XZ, retail 0x0049AC94 (49 bytes).
// Behavior-side destructor (class of rowed ctor 0x49AD15, vtable 0x008508C8):
// restores the five vptrs at +0x00/+0x0C/+0x10/+0x20/+0x24 (DBaseRoot/M1/B2/
// M3/M4 shape, DeployStyleAIUpdateDtor precedent) plus the +0x3E4 word via
// the inherited extra, then tail-jumps to the rowed base dtor
// ??1Rva0049A64B@@UAE@XZ at 0x0049A64B. Sole caller is the scalar-deleting
// dtor at 0x0049AD9B.

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

class Rva0026E836 : public DBaseRoot, public DBaseM1, public DBaseB2, public DBaseM3, public DBaseM4
{
public:
	virtual ~Rva0026E836();
};

class Rva0049A64B : public Rva0026E836
{
public:
	virtual ~Rva0049A64B();

protected:
	char m_pad0028[0x3E4 - 0x28];
	int m_extra03E4;
};

class HordeWorkerAIUpdate : public Rva0049A64B
{
public:
	virtual ~HordeWorkerAIUpdate();
};

HordeWorkerAIUpdate::~HordeWorkerAIUpdate()
{
	m_extra03E4 = 0x00C50868;
}
