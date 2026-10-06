// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva00538F61@@QAE@XZ, retail 0x00538F61, 10 bytes.
// Dtor freeing pointer at +4 via rowed free 0x00030830.
// Evidence: callers 0x00319DE5 plus Unwind 0x0077A998 0x0077AA5E 0x0077AAF6; prev QuickMatchScreenBase /O1 /DNDEBUG next Disp32Float no-flags.
extern "C" void __cdecl free(void *block);

struct Rva00538F61
{
	~Rva00538F61();
	char m_pad[4];
	void *m_ptr;
};

Rva00538F61::~Rva00538F61()
{
	free(m_ptr);
}
