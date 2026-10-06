// cl: /MD
// ?rva004693AD@Rva004693AD@@QAE_NPAURva004693ADArg@@@Z 0x004693AD 44B evidence: int at arg+0x74 vs this +0x264 +0x26c or flag 0x109 bit 8 callers 0x470517 0x470731 0x474C9F
struct Flag109
{
	unsigned char m_pad[0x109];
	unsigned char m_flags;
};
struct Rva004693ADArg
{
	char m_pad00[4];
	Flag109 *m_04;
	char m_pad08[0x6C];
	int m_74;
};
class Rva004693AD
{
public:
	bool rva004693AD(Rva004693ADArg *arg);
private:
	char m_pad[0x264];
	int m_264;
	int m_pad268;
	int m_26C;
};
bool Rva004693AD::rva004693AD(Rva004693ADArg *arg)
{
	int value = arg->m_74;
	if (m_264 == value || m_26C == value || (arg->m_04->m_flags & 8) != 0)
		return true;
	return false;
}
