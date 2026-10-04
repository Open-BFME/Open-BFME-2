// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// stlport

// Display::testMinSpecRequirements is an inline in GameClient/Display.h:
//     virtual Bool testMinSpecRequirements(Bool *videoPassed, Bool *cpuPassed,
//         Bool *memPassed, StaticGameLODLevel *idealVideoLevel=NULL, Real *cpuTime=NULL)
//     {*videoPassed=*cpuPassed=*memPassed=true; return true;}
// The BFME1 donor W3DDisplay.cpp only emits it through that header. Retail
// 0x00049F35 writes memPassed, cpuPassed then videoPassed and returns true with
// ret 0x14; emitted out-of-line here, the donor's other bodies omitted.
typedef bool Bool;
typedef float Real;

enum StaticGameLODLevel
{
	STATIC_GAME_LOD_LEVEL_FIRST
};

class Display
{
public:
	virtual Bool testMinSpecRequirements( Bool *videoPassed, Bool *cpuPassed,
		Bool *memPassed, StaticGameLODLevel *idealVideoLevel, Real *cpuTime );
};

Bool Display::testMinSpecRequirements( Bool *videoPassed, Bool *cpuPassed,
	Bool *memPassed, StaticGameLODLevel *idealVideoLevel, Real *cpuTime )
{
	*videoPassed = *cpuPassed = *memPassed = true;
	return true;
}
