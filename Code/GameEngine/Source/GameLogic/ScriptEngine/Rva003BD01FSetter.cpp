// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BD01FSet@@YGXE@Z retail 0x003BD01F 19 bytes.
// Byte setter: TheGameClient+0xC1 = al([esp+4]). Evidence: caller 0x003CE64A; neighbours Rva003BD011Forward prev Rva003BD032Set next same /O1.
class ClientFrameSubsystem
{
public:
	unsigned char m_pad[0xC1];
	unsigned char m_c1;
};
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

void __stdcall Rva003BD01FSet(unsigned char val)
{
	((ClientFrameSubsystem *)TheGameClient)->m_c1 = val;
}
