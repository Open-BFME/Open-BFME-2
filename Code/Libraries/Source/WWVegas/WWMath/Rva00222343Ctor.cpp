// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ??0Rva00222343@@QAE@XZ @0x00222343 89B
// Unnamed 0x3A-byte WWMath curve parameter block: fourteen int slots with
// 0x200/0x40-style defaults and two trailing zero bytes. Own TU with /O1:
// the neighbour TU folds same-value stores and zeroes bytes via xor, retail
// keeps them sequential with immediates.
// Evidence: gap between 0x002221A6 and 0x0022239C unlock, callers
// 0x00224296 0x006CF230, no donor, honest-address ctor.
struct Rva00222343
{
	Rva00222343(void);
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	bool m_38;
	bool m_39;
};

Rva00222343::Rva00222343(void)
{
	m_00 = 0x200;
	m_04 = 0x200;
	m_08 = 0x40;
	m_0C = 0x100;
	m_10 = 0x40;
	m_14 = 0x100;
	m_18 = 0x180;
	m_1C = 0x40;
	m_20 = 0x180;
	m_24 = 0x20;
	m_28 = 0x100;
	m_2C = 0x400;
	m_30 = 0x80;
	m_34 = 8;
	m_38 = false;
	m_39 = false;
}
