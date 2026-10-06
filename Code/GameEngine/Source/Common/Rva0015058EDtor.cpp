// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva0015058E@@UAE@XZ @0x0015058E 63B: dtor destroying Rva0014F699 at +0x10 then vector Rva00150209 at +4, restoring vtable 0x007C6F24 via inline Snapshot base. Evidence: rowed callees 0x0014D1E3 0x00150209, vtable data 0x007C6F24, callers 0x00150614 0x001510A9.
// Retail: mov eax handler / call __EH_prolog / lea ecx [esi+0x10] call ??1Rva0014F699 / lea ecx [esi+4] call ??1Rva00150209 / mov [esi] vtable / EH epilog.
// Not established: owning class identity; address-derived name.

extern const void *const g_00BC6F24[];

class Snapshot
{
public:
	virtual ~Snapshot();
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = g_00BC6F24;
}

class Rva0014F3E7;

struct Rva00150209
{
	Rva0014F3E7 *m_start;
	Rva0014F3E7 *m_finish;
	Rva0014F3E7 *m_endOfStorage;
	~Rva00150209();
};

class Rva0014F699
{
public:
	virtual ~Rva0014F699();
private:
	int m_pad[18];
};

class __declspec(novtable) Rva0015058E : public Snapshot
{
public:
	virtual ~Rva0015058E();
private:
	Rva00150209 m_04;
	Rva0014F699 m_10;
};

Rva0015058E::~Rva0015058E()
{
}
