// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva0026E5B9@@QAE@XZ, retail 0x0026E5B9, 30 bytes.
// Vector-dtor shape over Rva00268B04 via rowed destroy 0x0026E1DE plus game free.
// Evidence: pushes [esi+4] plus [esi] to destroy then frees [esi]; callers at 0x0026E802 plus 0x003325E3 plus 0x003327A7.

class PoolMember
{
public:
	void Rva00268902();
private:
	void *m_head;
};

class Rva00268B04
{
public:
	void rva00268B04();
private:
	char m_pad[8];
	PoolMember m_pool;
};

void __cdecl Rva0026E1DEDestroy(Rva00268B04 *first, Rva00268B04 *last);
extern "C" void __cdecl free(void *);

class Rva0026E5B9
{
public:
	~Rva0026E5B9();
private:
	Rva00268B04 *m_start;
	Rva00268B04 *m_finish;
	Rva00268B04 *m_end;
};

Rva0026E5B9::~Rva0026E5B9()
{
	Rva0026E1DEDestroy(m_start, m_finish);
	void *p = (void *)m_start;
	if (p)
		free(p);
}
