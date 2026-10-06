// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0030BB87@Rva0030BB87@@QAEXAAVDataChunkInput@@H@Z, retail 0x0030BB87, 30 bytes.
// Forwards DataChunkInput plus 1 to rowed 0x0030BAF8 then stores readInt at +0x28.
// Evidence: chain from 0x0030BAF8; prev 0x0030BAF8 same flags; callees 0x0030BAF8 rowed readInt 0x00306E78 rowed.
class DataChunkInput
{
public:
	int readInt();
};
struct Rva0030BAF8
{
	void rva0030BAF8(DataChunkInput &file, int val);
};
struct Rva0030BB87
{
	void rva0030BB87(DataChunkInput &file, int unused);
	char m_pad[0x28];
	int m_28;
};
void Rva0030BB87::rva0030BB87(DataChunkInput &file, int unused)
{
	((Rva0030BAF8 *)this)->rva0030BAF8(file, 1);
	m_28 = file.readInt();
}
