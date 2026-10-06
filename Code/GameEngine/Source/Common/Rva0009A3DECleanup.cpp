// cl: /MD
// ?Rva0009A3DECleanup@@YAXXZ retail 0x0009A3DE 61 bytes.
// Four guarded releases via rowed callees with null-checked globals.
// Evidence: callers at 0x0006689A in 0x00066808 plus chain from 0x00109DCF.
class Rva000F0912
{
public:
	void rva000F0972();
};

class Rva0074011F
{
public:
	void rva0074011F();
};

class Rva00109DCF
{
public:
	void rva00109DCF();
};

class Rva0007BAD6
{
public:
	void rva0007BAD6();
};

class R2GlobalReceiver;

extern Rva000F0912 *g_00DEBCD8;
extern Rva0074011F *g_00DEC2CC;
extern R2GlobalReceiver *R2Ptr01306DF0;
extern Rva0007BAD6 *g_00DE1FF8;

void Rva0009A3DECleanup()
{
	if (g_00DEBCD8 != 0)
		g_00DEBCD8->rva000F0972();
	if (g_00DEC2CC != 0)
		g_00DEC2CC->rva0074011F();
	if (R2Ptr01306DF0 != 0)
		((Rva00109DCF *)R2Ptr01306DF0)->rva00109DCF();
	if (g_00DE1FF8 != 0)
		g_00DE1FF8->rva0007BAD6();
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DEBCD8@@3PAVRva000F0912@@A=?TheW3DVolumetricShadowManager@@3PAVW3DVolumetricShadowManager@@A")
#pragma comment(linker, "/alternatename:?g_00DEC2CC@@3PAVRva0074011F@@A=?TheW3DProjectedShadowManager@@3PAVW3DProjectedShadowManager@@A")
#pragma comment(linker, "/alternatename:?g_00DE1FF8@@3PAVRva0007BAD6@@A=?Rva00DE1FF8Manager@@3PAVRva0007DA23ResourceManager@@A")
