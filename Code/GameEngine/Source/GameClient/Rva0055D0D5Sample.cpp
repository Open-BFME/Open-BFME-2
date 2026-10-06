// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0055D0D5@Rva0055D0D5@@QAE?AUCoord3D0055D0D5@@IIII@Z @0x0055D0D5 531B: box emission volume sample
// Evidence: vslot slot7 of BoxEmissionVolumeModule (0x0081C784 0x0081CB94 0x0081D04C); hollow flag +0x20 extents +0x24/+0x28/+0x2C; rowed GetGameClientRandomValue 0x0023404A and GetGameClientRandomValueReal 0x00234111 with BFME2 box path lines 108/111/112/121/122/131/132/140/141/142; preserves upstream Y-extent typo.
// Donor: reference/open-bfme-1/game/GameEngine/Source/GameClient/System/FXParticleSystem/fxpsemitterboxvolumemodule.cpp (same lines and typo, BFME1 path F:\bfme\...).

int GetGameClientRandomValue(int low, int high, char *file, int line);
float GetGameClientRandomValueReal(float low, float high, char *file, int line);

struct Coord3D0055D0D5
{
	float x;
	float y;
	float z;
	Coord3D0055D0D5() {}
	Coord3D0055D0D5(const Coord3D0055D0D5 &o) : x(o.x), y(o.y), z(o.z) {}
};

class Rva0055D0D5
{
public:
	Coord3D0055D0D5 rva0055D0D5(unsigned int, unsigned int, unsigned int, unsigned int);
private:
	char m_pad[0x20];
	bool m_hollow;
	char m_pad2[3];
	float m_extentX;
	float m_extentY;
	float m_extentZ;
};

Coord3D0055D0D5 Rva0055D0D5::rva0055D0D5(unsigned int, unsigned int, unsigned int, unsigned int)
{
	char *source = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterboxvolumemodule.cpp";
	Coord3D0055D0D5 result;

	if (m_hollow) {
		int side = GetGameClientRandomValue(0, 6, source, 108);

		if (side % 3 == 0) {
			result.x = GetGameClientRandomValueReal(-m_extentX, m_extentX, source, 111);
			result.y = GetGameClientRandomValueReal(-m_extentY, m_extentY, source, 112);
			if (side == 0)
				result.z = -m_extentZ;
			else
				result.z = m_extentZ;
		} else if (side % 3 == 1) {
			result.y = GetGameClientRandomValueReal(-m_extentY, m_extentY, source, 121);
			result.z = GetGameClientRandomValueReal(-m_extentZ, m_extentZ, source, 122);
			if (side == 1)
				result.x = -m_extentX;
			else
				result.x = m_extentY;
		} else if (side % 3 == 2) {
			result.x = GetGameClientRandomValueReal(-m_extentX, m_extentX, source, 131);
			result.z = GetGameClientRandomValueReal(-m_extentZ, m_extentZ, source, 132);
			if (side == 2)
				result.y = -m_extentY;
			else
				result.y = m_extentY;
		}
	} else {
		result.x = GetGameClientRandomValueReal(-m_extentX, m_extentX, source, 140);
		result.y = GetGameClientRandomValueReal(-m_extentY, m_extentY, source, 141);
		result.z = GetGameClientRandomValueReal(-m_extentZ, m_extentZ, source, 142);
	}

	return result;
}
