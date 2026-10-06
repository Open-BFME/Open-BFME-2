// cl: /MD
//
// ?rva0040FB2E@Rva0040FB2E@@QAEAAUOpaqueRefElement4@@ABU2@@Z @ 0x0040FB2E 8B
// Tail-jmp wrapper returning m_elem = other via rowed OpaqueRefElement4::operator=.
// Evidence: retail add ecx,4 then jmp to rowed ??4OpaqueRefElement4 at 0x00239099; caller 0x0022199F.
struct OpaqueRefElement4
{
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva0040FB2E
{
public:
	OpaqueRefElement4 &rva0040FB2E(const OpaqueRefElement4 &other);
private:
	char m_pad00[4];
	OpaqueRefElement4 m_elem;
};

OpaqueRefElement4 &Rva0040FB2E::rva0040FB2E(const OpaqueRefElement4 &other)
{
	return m_elem = other;
}
