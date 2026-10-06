// cl: /O1 /MD /EHsc
// ?rva005E8E80@Rva005E8E80@@UAE?AURva005E1753Result@@XZ @0x005E8E80 33B:
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
	virtual Rva005E1753Result rva005E8E80();
};

// ?rva005E8E80@Rva005E8E80@@UAE?AURva005E1753Result@@XZ
Rva005E1753Result Rva005E8E80::rva005E8E80()
{
	return ((Rva005E8E80Base0 *)((char *)this - 8))->v08()->GetResult();
}
