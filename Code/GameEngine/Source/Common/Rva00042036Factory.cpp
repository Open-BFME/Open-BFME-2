// cl: /DNDEBUG /MD /EHsc
// ?rva00042036@Rva00042036@@QAEPAVRva000647B5@@XZ @0x00042036 50B: factory news 16B Rva then calls rowed ctor 0x000647B5. Evidence: calls rowed new 0x0002FDA0 and rowed ctor; chain from 0x000647B5; between GameLogic and ModuleFactory name getters.
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

void *__cdecl operator new(unsigned int size);

class Rva00042036
{
public:
	Rva000647B5 *rva00042036();
};

Rva000647B5 *Rva00042036::rva00042036()
{
	return new Rva000647B5();
}
