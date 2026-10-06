// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D9C2F@Rva002D9C2F@@QAEAAUOpaqueRefElement4@@ABU2@@Z @ 0x002D9C2F 8B
// Tail-jmp assign forwarder: return m_ref = other where m_ref is OpaqueRefElement4 at +8.
// Evidence: honest address name; add ecx 8 jmp to rowed ??4OpaqueRefElement4@@QAEAAU0@ABU0@@Z; callers in FUN_0045a451 and others; neighbours CDManager getPath and BfmeStringTailRecord144 deleting dtor.
struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};
class Rva002D9C2F
{
public:
	OpaqueRefElement4 &rva002D9C2F(const OpaqueRefElement4 &other);
	char m_pad[8];
	OpaqueRefElement4 m_ref;
};
OpaqueRefElement4 &Rva002D9C2F::rva002D9C2F(const OpaqueRefElement4 &other)
{
	return m_ref = other;
}
