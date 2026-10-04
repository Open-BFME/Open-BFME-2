// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/campaignmanagerascii -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/Terrain
// stlport
// class-gate: allow AsciiString retail calls the out-of-line copy ctor at 0x000365F0; this 4-byte single-pointer view with out-of-line copy ctor and dtor reproduces the /EHsc return-value frame the shared StringBase path does not

// TerrainRoadType::getBridgeModelNameBroken is an inline in
// GameClient/TerrainRoads.h:
//     inline AsciiString getBridgeModelNameBroken( void ) { return m_bridgeModelNameBroken; }
// The BFME1 donor TerrainRoads.cpp only emits it through that header. Retail
// 0x00062E72 copies the AsciiString at this+0x4C into the hidden return buffer
// through the AsciiString copy constructor at 0x000365F0; AsciiString's inline
// destructor gives the /EHsc return-value frame retail shows. Emitted
// out-of-line here, the donor's other bodies omitted.
class AsciiString
{
public:
	AsciiString( const AsciiString &other );
	~AsciiString();

private:
	void *m_data;
};

class TerrainRoadType
{
public:
	AsciiString getBridgeModelNameBroken();

private:
	char m_pad[0x4c];
	AsciiString m_bridgeModelNameBroken;
};

AsciiString TerrainRoadType::getBridgeModelNameBroken()
{
	return m_bridgeModelNameBroken;
}
