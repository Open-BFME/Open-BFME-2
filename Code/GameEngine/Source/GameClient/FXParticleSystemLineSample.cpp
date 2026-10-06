// cl: /MD
// ?rva0055CDEC@Rva0055CDEC@@QAE?AUCoord3D0055CDEC@@IIII@Z at 0x0055CDEC size 166
// Evidence: vslot slot7 of 0x0081D02C and 0x0081C750 Line info; lerp between +0x24 and +0x30 with random 0-1 file fxpsemitterlinevolumemodule.cpp line 0x72; pattern from Box slot6 Rva005F8890.

struct Coord3D0055CDEC
{
	float x;
	float y;
	float z;
	Coord3D0055CDEC() {}
	Coord3D0055CDEC(const Coord3D0055CDEC &o) : x(o.x), y(o.y), z(o.z) {}
};

float GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

class Rva0055CDEC
{
public:
	Coord3D0055CDEC rva0055CDEC(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
private:
	char m_pad[0x24];
	Coord3D0055CDEC m_a;
	Coord3D0055CDEC m_b;
};

Coord3D0055CDEC Rva0055CDEC::rva0055CDEC(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
	Coord3D0055CDEC delta, start, end;
	start = m_a;
	end = m_b;
	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	delta.z = end.z - start.z;
	float t = GetGameClientRandomValueReal(0.0f, 1.0f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterlinevolumemodule.cpp", 0x72);
	Coord3D0055CDEC newPos;
	newPos.x = start.x + t * delta.x;
	newPos.y = start.y + t * delta.y;
	newPos.z = start.z + t * delta.z;
	return newPos;
}
