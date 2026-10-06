// cl: /MD
// ?rva004AB7C8@LargeGroupAudioUpdate@@QBEHXZ @0x004AB7C8 35B: returns GetGameLogicRandomValue(0 m_18 file 0xA7) plus m_14 plus 1. File literal at 0x008547B8 is LargeGroupAudioUpdate.cpp. Callers at 0x004AB94B 0x004ABB60 0x004ABB72 0x004ABC52. Prev Rva0024A797Grandchildren next V3PolyCopyCtors.

typedef int Int;
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, int line);

class LargeGroupAudioUpdate
{
public:
	Int rva004AB7C8() const;

private:
	unsigned char m_pad00[0x14];
	Int m_14;
	Int m_18;
};

Int LargeGroupAudioUpdate::rva004AB7C8() const
{
	return GetGameLogicRandomValue(0, m_18, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\LargeGroupAudioUpdate.cpp", 0xA7) + m_14 + 1;
}
