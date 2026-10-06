// cl: /MD
// ?Rva002DBE62Get@@YAHXZ @0x002DBE62 123B
// Evidence: unlock lane; callers 0x002DD3A7 0x002DD7F8 0x00434B57 0x00435768 0x00435A44; callees rowed isSelectionLocked 0x4253A and get 0x210C66; globals TheGameLogic g_009FEF10 g_Rva0023D607Holder; GameLogic +0x110 +0x114 layout from Disp8 getters and holder check.
class GameLogic
{
public:
	char m_pad[0x110];
	int m_110;
	int m_114;
};
extern GameLogic *TheGameLogic;
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};
struct Rva0023D607Holder
{
	char m_00[16];
	int m_10;
};
extern Rva0023D607Holder *g_Rva0023D607Holder;
class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};
int Rva002DBE62Get()
{
	GameLogic *logic = TheGameLogic;
	Rva002BA8F1Logic *sel;
	if (logic == 0 || (sel = g_009FEF10) == 0)
		return 2;
	if (((BfmeSelectionState *)sel)->isSelectionLocked())
		return logic->m_114 != 0 ? 6 : 4;
	if (g_Rva0023D607Holder->m_10 != 0)
		return logic->m_110 == 9;
	if (logic->m_114 == 0)
		return 3;
	if (((Rva00210C66CmpBoolField *)logic)->get())
		return 5;
	return logic->m_110 == 6 ? 0 : 2;
}
