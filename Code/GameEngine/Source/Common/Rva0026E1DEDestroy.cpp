// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0026E1DEDestroy@@YAXPAVRva00268B04@@0@Z, retail 0x0026E1DE, 25 bytes.
// Array destroy loop over 12-byte Rva00268B04 via rowed forwarder 0x00268B04.
// Evidence: stride 0xC plus caller 0x0026E5B9 vector-dtor shape plus callee row.

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

void __cdecl Rva0026E1DEDestroy(Rva00268B04 *first, Rva00268B04 *last)
{
	for (; first != last; ++first)
		first->rva00268B04();
}
