// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0022D941Destroy@@YAXPAURva0022CD2A@@0@Z @0x0022D941 25B
// Range destroy over 0x18-byte Rva0022CD2A via rowed dtor at 0x0022CD2A. Stride 0x18 via add esi 0x18. Evidence: chain packet calls just-landed 0x0022CD2A plus 25B push-esi jmp-cmp loop shape; callers at 0x0022DCF4 0x00414150 destroy then free.
struct Rva0022CD2A
{
	~Rva0022CD2A();
	char m_pad[24];
};

void __cdecl Rva0022D941Destroy(Rva0022CD2A *first, Rva0022CD2A *last)
{
	while (first != last) {
		first->~Rva0022CD2A();
		++first;
	}
}
