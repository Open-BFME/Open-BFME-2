// cl: /DNDEBUG /MD
// ??0Rva000647B5@@QAE@XZ @0x000647B5 25B: empty derived ctor over GODupBase then own two vtables. Evidence: calls rowed GODupBase ctor 0x00306782 then two vptr stores; same two-base shape as GODupBase; caller 0x00042036.

class BfmeSnapshotBase
{
public:
	virtual void bfmeSlot0(void);
	~BfmeSnapshotBase();
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual void bfmeSlot0(void);
private:
	int m_bfmeState;
};

class GODupBase : public BfmeSnapshotBase, public SubsystemInterface
{
public:
	GODupBase();
	~GODupBase();
};

class Rva000647B5 : public GODupBase
{
public:
	Rva000647B5();
	~Rva000647B5();
private:
	char m_pad[4];
};

Rva000647B5::Rva000647B5()
{
}
