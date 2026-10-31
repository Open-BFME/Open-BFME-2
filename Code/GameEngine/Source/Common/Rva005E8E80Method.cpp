// cl: /O1 /MD /EHsc
// ?getResult@Rva005E8E80@@UAE?AURva005E1753Result@@XZ @0x005E8E80 33B:
// secondary-base forwarder returning Rva005E1753Result. Identity: ref table slot
// 0x00877F84 reaches it; neighbours are ?rva005E0D9C, ??_GRva005E8D71 and
// FUN_009e8cf8. Shape follows the Rva005CC468Family getters (same result type,
// GetResult pin at 0x005E1753); the -8 adjust reaches the primary base whose
// slot 2 yields the Rva005E1753Class to report on.

struct Rva005E1753Result
{
	void *m_ptr;
	Rva005E1753Result();
	Rva005E1753Result(const Rva005E1753Result &);
	~Rva005E1753Result();
};

class Rva005E1753Class
{
public:
	Rva005E1753Result GetResult();
};

class Rva005E8E80Base0
{
public:
	virtual void v00();
	virtual void v04();
	virtual Rva005E1753Class *v08();
private:
	char m_pad[0x8 - 4];
};

class Rva005E8E80 : public Rva005E8E80Base0
{
public:
	virtual Rva005E1753Result getResult();
};

// ?getResult@Rva005E8E80@@UAE?AURva005E1753Result@@XZ
Rva005E1753Result Rva005E8E80::getResult()
{
	return ((Rva005E8E80Base0 *)((char *)this - 8))->v08()->GetResult();
}

// The retail call in this body reads 0x005E1753, an address the ledger already
// carries as ?CreateHelp@StandardCommandButtonSettings@StrategicHUD@@QBE?AUTreeHintRef00217D4C@@XZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?GetResult@Rva005E1753Class@@QAE?AURva005E1753Result@@XZ=?CreateHelp@StandardCommandButtonSettings@StrategicHUD@@QBE?AUTreeHintRef00217D4C@@XZ")
