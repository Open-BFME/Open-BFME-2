// cl: /DNDEBUG /MD
// ?Rva002A74C3Get@@YGHPAX@Z 61B @0x002A74C3: int helper adding Object float-out to +0x61C int then returning.
// Evidence: linkbody lane LINK BONUS via 0x002A7500/0x002A7513 plus 14B file; callees rowed Object 0x0028C149; caller 0x002A7507 pushes one arg then add [esi+0xC] eax ret4; prev Rva002A7400Ctor next Rva002A73B8Dtor share /O1 /DNDEBUG /MD.
class Object
{
public:
	bool rva0028C149(int a, float *b, int c);
};
struct Rva002A74C3Inner
{
	char m_pad[0x61C];
	int m_val61C;
};
struct Rva002A74C3Outer
{
	char m_pad[4];
	Rva002A74C3Inner *m_template;
};
int __stdcall Rva002A74C3Get(void *a)
{
	Rva002A74C3Outer *objectView = (Rva002A74C3Outer *)a;
	int commandPointBonus = objectView->m_template->m_val61C;
	float out = 0.0f;
	if (((Object *)a)->rva0028C149(0x18, &out, 0))
		commandPointBonus = (int)((float)commandPointBonus + out);
	return commandPointBonus;
}
