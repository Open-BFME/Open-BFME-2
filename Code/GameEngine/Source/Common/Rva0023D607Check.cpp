// cl: /MD
// ?Rva0023D607Get@@YAEXZ, retail 0x0023D607, 13 bytes.
// mov eax,[global] cmp [eax+0x10],0 setne al ret; unsigned char return.
// Evidence: unlock lane; caller 0x00200084 tests al; global at 0x009FDC8C.
struct Rva0023D607Holder
{
	char m_00[16];
	int m_10;
};
class LinearCampaignManager;
// TheLinearCampaignManager: matched references place it at VA 0xdfdc8c (zero-filled .bss).
LinearCampaignManager *TheLinearCampaignManager;
unsigned char Rva0023D607Get()
{
	return ((Rva0023D607Holder *)TheLinearCampaignManager)->m_10 != 0;
}
