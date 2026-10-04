// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient

// BFME's LightEnvironmentClass occupies 0x228 bytes and reads OutputAmbient at
// +0x164; the BFME1 donor RTS3DSceneRva00713780.cpp declares only the members
// this body reads, with the header body inline as:
//     void Set_Output_Ambient(Vector3 &oa) { OutputAmbient = oa; }
// Retail 0x0006E136 copies X, Y then Z to this+0x164. Vector3 carries the
// WWMath user-defined operator=, whose inline scalar stores are what /Os emits
// here instead of the movsd idiom a plain 12-byte POD would produce. Vector3 is
// a class (retail mangling AAVVector3@@). Donor's other bodies omitted.
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3 & operator = ( const Vector3 &v ) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

class LightEnvironmentClass
{
public:
	void Set_Output_Ambient( Vector3 &oa );

private:
	char m_inputs[0x164];
	Vector3 OutputAmbient;
};

void LightEnvironmentClass::Set_Output_Ambient( Vector3 &oa )
{
	OutputAmbient = oa;
}
