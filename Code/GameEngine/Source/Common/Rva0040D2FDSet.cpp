// cl: /DNDEBUG /MD /Oy-
// ?rva0040D2FD@ArmySummarySystem@@QAEXHHPAURva0040D2FDVec@@@Z @0x0040D2FD 79B: army lookup 0x0040D008 on its own this clears +0x2c scales int arg by g_00DBA4F4 to +0x30 copies vec pair to +0x58/+0x5c. Evidence: calls rowed 0x0040D008; single caller GameLogic forwarder 0x0023D054 (add ecx, 0x184; jmp); prev/next in Common.
class BfmeY1038
{
public:
	char m_pad0[0x2c];
	int m_2c;
	int m_30;
	char m_pad34[0x24];
	int m_58;
	int m_5c;
};
struct Rva0040D2FDVec
{
	float x;
	float y;
};
extern float LOGICFRAMES_PER_SECONDS_REAL;
class ArmySummarySystem
{
public:
	void *rva0040D008(int id);
	void rva0040D2FD(int armyId, int delaySeconds, Rva0040D2FDVec *coordinates);
};
void ArmySummarySystem::rva0040D2FD(int armyId, int delaySeconds, Rva0040D2FDVec *coordinates)
{
	float coordinateCopy[2];
	BfmeY1038 *y = (BfmeY1038 *)rva0040D008(armyId);
	if (y == 0)
		return;
	y->m_2c &= 0;
	y->m_30 = (int)((float)delaySeconds * LOGICFRAMES_PER_SECONDS_REAL);
	coordinateCopy[0] = coordinates->x;
	coordinateCopy[1] = coordinates->y;
	y->m_58 = *(int *)&coordinateCopy[0];
	y->m_5c = *(int *)&coordinateCopy[1];
}
