// cl: /MD
//
// ?rva000E6594@Rva000E6594@@QAEXXZ, retail 0x000E6594 8B.
// Evidence: unlock lane; add ecx 0x38 plus jmp to rowed FillLevelSurfaces 0x00132989; callers at 0x0006B819 and 0x0006B829 in FUN_0046b804; tail forwarder per PartitionManagerShroudThunks precedent.
struct CursorTextureSlot
{
	void *Ptr;
	void FillLevelSurfaces();
};

class Rva000E6594
{
	char m_pad[0x38];
	CursorTextureSlot m_slot38;
public:
	void rva000E6594();
};

void Rva000E6594::rva000E6594()
{
	m_slot38.FillLevelSurfaces();
}
