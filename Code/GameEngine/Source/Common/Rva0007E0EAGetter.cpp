// cl: /DNDEBUG /MD
// ?rva0007E0EA@Rva0007E0EA@@QAEHXZ @0x0007E0EA 7B
// evidence: unlock 7B disp8 int-add getter via 3 matched callers in 0x00100A0B; no callees globals strings EH
class Rva0007E0EA
{
public:
	int rva0007E0EA();
private:
	char m_pad00[0x40];
	int m_40;
};
int Rva0007E0EA::rva0007E0EA()
{
	return m_40 + 0x50;
}
