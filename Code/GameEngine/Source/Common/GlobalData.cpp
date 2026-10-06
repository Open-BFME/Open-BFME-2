// cl: /O1 /EHsc /MD /arch:SSE
// GlobalData.cpp -- GlobalData members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. Zero Hour's newOverride also copies the current data
// into the new override; BFME2's retail body only constructs a fresh
// GlobalData (0x1254 bytes, ctor 0x0023631C) and links it in front of the
// chain through m_next at +0x1250 (target evidence).

class GlobalData
{
public:
	GlobalData();					// 0x0023631C

	static GlobalData *newOverride();

private:
	unsigned char m_data[0x1250];
	GlobalData *m_next;				// +0x1250
};

// TheWritableGlobalData, VA 0x00DFE758.
extern GlobalData *TheWritableGlobalData;

// GlobalData::newOverride, retail 0x00237A6B.
GlobalData *GlobalData::newOverride()
{
	GlobalData *override = new GlobalData;
	override->m_next = TheWritableGlobalData;
	TheWritableGlobalData = override;
	return override;
}
