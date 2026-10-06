// cl: /MD
//
// ?rva004B2A9D@Rva004B2A9D@@QAEPAHXZ 39B @0x004B2A9D: picks a random int
// from the int array at +4/+8 via rowed GetGameLogicRandomValue(0,
// count-1, file, 0x47) and returns its address. Caller at 0x004B2C0E;
// file literal is the ReplaceObjectUpdate TU per the neighbourhood.

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Rva004B2A9D
{
public:
	int *rva004B2A9D();
private:
	unsigned char m_pad00[4];
	char *m_start; // +4
	char *m_finish; // +8
};

int *Rva004B2A9D::rva004B2A9D()
{
	int count = (m_finish - m_start) >> 2;
	int picked = GetGameLogicRandomValue(0, count - 1, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\ReplaceObjectUpdate.cpp", 0x47);
	return (int *)(m_start + picked * 4);
}
