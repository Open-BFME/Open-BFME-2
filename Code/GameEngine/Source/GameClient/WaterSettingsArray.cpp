// cl: /O1 /DNDEBUG /MD /EHsc
// ZH donor: GeneralsMD GameClient/Water.cpp `WaterSetting
// WaterSettings[ TIME_OF_DAY_COUNT ];`. Target evidence: game.dat's __xc_a
// table points at 0x007AE6C2, which passes six elements of 0x7C bytes at
// 0x00DFF1A0, the rowed ??0WaterSetting@@QAE@XZ (0x00309CF8) and the
// destructor behind it (0x00309D9E) to the eh vector constructor iterator
// (0x00629512), then registers the array cleanup at 0x007B7ACD with atexit.
// INI::parseWaterSettingDefinition (0x00200BEB) indexes the same array. Six
// elements is BFME2's count; the donor's enum is not carried, so the count is
// written out. WaterSettingCtor.cpp carries the member layout; only the size
// and the virtual destructor matter to this initializer.

class WaterSetting
{
public:
	WaterSetting( void );
	virtual ~WaterSetting( void );

private:
	char m_body[0x78];
};

WaterSetting WaterSettings[ 6 ];
