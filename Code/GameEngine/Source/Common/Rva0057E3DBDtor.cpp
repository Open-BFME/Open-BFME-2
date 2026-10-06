// cl: /MD /EHs
// ??1Rva0057E3DB@@UAE@XZ @0x0057E3DB 129B
// MI dtor: derived vptr 0x86F390 at +0 on entry, base vptrs 0x86E350 at +0
// and 0x8363B8 at +4 at exit. Members +0x0C freed via rowed _free 0x30830,
// +0x18/+0x6C released via rowed ReleaseTreeHintRef 0x7DEEF, +0x64 deleted
// via rowed MapMetaData dtor 0x22DBC6 plus rowed operator delete 0x2FD60.
// Evidence: packet disasm with all callees rowed, two callers 0x4421E1
// 0x43A396, vtable stores at +0/+4.
struct TargetRef00217D4C
{
	int m_00;
	int m_04;
	int m_08;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
class MapMetaData
{
public:
	~MapMetaData();
};
void operator delete(void *p);
extern "C" void __cdecl free(void *p);

struct Buf0C
{
	~Buf0C() { if (m_ptr) free(m_ptr); }
	void *m_ptr;
};

struct Rva57E3DBRefHolder
{
	~Rva57E3DBRefHolder() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
	struct TargetRef00217D4C *m_ptr;
};

class Rva0057E3DBBase
{
public:
	__forceinline ~Rva0057E3DBBase() {}
	virtual void keep() {}
};

struct Mem04
{
	__forceinline ~Mem04() {}
	virtual void keep4() {}
};

class Rva0057E3DB : public Rva0057E3DBBase
{
public:
	virtual ~Rva0057E3DB();
	void rva0057E058();
	void rva0057E24B(int arg);
private:
	struct Mem04 m_04; // +0x04 second vptr slot
	int m_08; // +0x08
	struct Buf0C m_0C; // +0x0C, dtor frees via free
	char m_pad10[8]; // +0x10..+0x17
	struct Rva57E3DBRefHolder m_18; // +0x18, dtor releases
	char m_pad1C[72]; // +0x1C..+0x63
	class MapMetaData *m_64; // +0x64, body deletes
	char m_pad68[4]; // +0x68..+0x6B
	struct Rva57E3DBRefHolder m_6C; // +0x6C, dtor releases
};

Rva0057E3DB::~Rva0057E3DB()
{
	delete m_64;
}

// ?rva0057E24B@Rva0057E3DB@@QAEXH@Z @0x0057E24B 18B
// Setter on the AptMpGameSetup +0x60 panel member: stores the int arg into the
// +0x18 target's +8 slot, then refreshes via the pinned 0x0057E058 body.
// Evidence: thiscall (ecx read), ret 4, caller 0x0043A0D9 passes [esi+0x88]
// with ecx=esi+0x18, callee pin ?rva0057E058@Rva0057E3DB@@QAEXXZ.
void Rva0057E3DB::rva0057E24B(int arg)
{
	m_18.m_ptr->m_08 = arg;
	rva0057E058();
}
