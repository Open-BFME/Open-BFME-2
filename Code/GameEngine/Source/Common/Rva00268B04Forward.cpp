// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00268B04@Rva00268B04@@QAEXXZ @ 0x00268B04 8B
// Tail-jmp void forwarder: m_pool.Rva00268902 where m_pool is PoolMember-like at +8.
// Evidence: honest address name; add ecx 8 jmp to pinned ?Rva00268902@PoolMember@@QAEXXZ; callers in FUN_006698e6 and others; neighbours Object_getPlanarDirectionTo.cpp and SubsystemNameGetters2.cpp.
class PoolMember
{
public:
	void Rva00268902();
};
class Rva00268B04
{
public:
	void rva00268B04();
	char m_pad[8];
	PoolMember m_pool;
};
void Rva00268B04::rva00268B04()
{
	m_pool.Rva00268902();
}
