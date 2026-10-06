// cl: /MD
// ?rva006003AD@Rva006003FC@@QAEXXZ @0x006003AD 8B vslot tail-forward.
// Retail add ecx,8 then jmp 0x005FFB81 ?rva005FFB81@Rva005FFB81@@QAEXXZ.
// Evidence: vslot lane slot 1 (offset 0x4) of 0x0087A638 class of
// ??1Rva006003FC@@UAE@XZ; prev 0x006003A5 same add-jmp shape; caller 0x005FAA93.
class Rva005FFB81
{
public:
	void rva005FFB81();
};

class Rva006003FC
{
public:
	void rva006003AD();
private:
	char m_pad[8];
	Rva005FFB81 m_member08;
};

void Rva006003FC::rva006003AD()
{
	m_member08.rva005FFB81();
}
