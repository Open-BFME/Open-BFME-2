// cl: /MD /EHsc /DNDEBUG
//
// ??1LargeGroupAudioUpdate@@UAE@XZ, retail 0x004AB8DC, 46 bytes.
// Target evidence: the audited scalar deleting dtor 0x004ABB1B calls this
// body; slot 4 -> 0x004AB897 uses class-name string "LargeGroupAudioUpdate".
// Body: five compiler vptr restores (+0 +0x0C +0x10 +0x20 +0x24), then the
// +0x24 base's own inline dtor re-stores its vptr 0x00BFB698, then a tail
// jmp to the UpdateModule-family dtor 0x0024A797 (UpdateModule). The +0x20
// and +0x24 bases are structural stand-ins (types unrecovered).

// Base view matching Common/Rva0024A797DeletingDtor.cpp.
class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class PrimaryP4AB8DC : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP4AB8DC() {}
};

class Rva0024A797_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class UpdateModule : public PrimaryP4AB8DC, public Rva0024A797_B2
{
public:
	virtual ~UpdateModule();
};

class LargeGroupAudioUpdate_B20
{
public:
	virtual void f20();
};

class LargeGroupAudioUpdate_B24
{
public:
	virtual void f24();
	~LargeGroupAudioUpdate_B24() {}
};

class LargeGroupAudioUpdate : public UpdateModule, public LargeGroupAudioUpdate_B20,
	public LargeGroupAudioUpdate_B24
{
public:
	virtual ~LargeGroupAudioUpdate();
};

LargeGroupAudioUpdate::~LargeGroupAudioUpdate()
{
}
