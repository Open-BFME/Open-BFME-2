// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00210C33@Rva00210C33@@QAEXXZ, retail 0x00210C33, 25 bytes.
// Show-cursor-once wrapper: if byte at +0x5008 is 0, calls user32 ShowCursor(1)
// via IAT 0x00BBA830 and sets the flag to 1. Evidence: single caller
// 0x00213C10, IAT call shape needs dllimport stdcall, neighbouring bool
// getters use /O1. No fallback paths.
extern "C" __declspec(dllimport) int __stdcall ShowCursor(int bShow);

class Rva00210C33
{
public:
	void rva00210C33();
	char m_pad[0x5008];
	bool m_flag5008; // +0x5008
};

void Rva00210C33::rva00210C33()
{
	if (!m_flag5008)
		ShowCursor(1);
	m_flag5008 = true;
}
