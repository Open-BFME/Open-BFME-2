// cl: /O1 /MD /arch:SSE
// ?Rva005EE317@@YGXPAVCoord3D@@@Z @ 0x005EE317 125B
// Random XY direction in AISPecialPowerTargetAoE.cpp (__FILE__ at 0x00878708
// line 150-151): GetGameLogicRandomValueReal(-1.0f at 0x007BB9AC, 1.0f) twice
// z=0 normalize then store to out. Callees rowed: GetGameLogicRandomValueReal
// 0x00234092 and Coord3D::normalize 0x000035B6. Gap between 0x005EE30C/0x005EE394.
class Coord3D
{
public:
	void normalize();
	float x;
	float y;
	float z;
};

float __cdecl GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

void __stdcall Rva005EE317(Coord3D *out)
{
	Coord3D tmp;
	tmp.x = GetGameLogicRandomValueReal(-1.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISPecialPowerTargetAoE.cpp", 150);
	tmp.y = GetGameLogicRandomValueReal(-1.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISPecialPowerTargetAoE.cpp", 151);
	tmp.z = 0.0f;
	tmp.normalize();
	out->x = tmp.x;
	out->y = tmp.y;
	out->z = tmp.z;
}
