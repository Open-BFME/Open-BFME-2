// cl: /DNDEBUG /MD
// ?Rva00446A77Enable@@YAXXZ @0x00446A77 30B
// Conditionally enables +0x2B9/+0x2BA bytes of the object at global.
// Evidence: gated by byte 0x00A0335C and null-checked pointer 0x00A03354;
// tail-jmps to rowed ?enable@Rva0043DB47DoubleSetter@@QAEXXZ @0x0043DB47
// via outer+0x288; callers @0x004493C7 @0x00582265 and jmp @0x00248D98.
class Rva0043DB47DoubleSetter
{
public:
	void enable();

	char m_lead[0x2B9];
	unsigned char m_a;
	unsigned char m_b;
};

struct Outer00446A77
{
	char m_pad[0x288];
	Rva0043DB47DoubleSetter m_sub;
};

extern unsigned char g_Va00A0335C;
extern Outer00446A77 *g_Va00A03354;

void Rva00446A77Enable(void)
{
	if (g_Va00A0335C == 0)
		return;
	Outer00446A77 *p = g_Va00A03354;
	if (p == 0)
		return;
	return p->m_sub.enable();
}

// ?Rva00248D84Enable@@YAXXZ @0x00248D84 25B unlock lane.
// Null-checked pointer 0x00A03354: null tail-jmps to rowed
// ?Rva00446A77Enable@@YAXXZ @0x00446A77, else tail-jmps to rowed
// ?enable@Rva0043DB47DoubleSetter@@QAEXXZ @0x0043DB47 via outer+0x288.
// Evidence: 6 callers in unclaimed bodies; landing unblocks 5 waiters.
void Rva00248D84Enable(void)
{
	Outer00446A77 *p = g_Va00A03354;
	if (p != 0)
		return p->m_sub.enable();
	return Rva00446A77Enable();
}

// ?Rva00248E98Enable@@YAXXZ @0x00248E98 43B chain lane on 0x00444462.
// Calls virtual slot 0xE0 on global 0x009FE958, rowed Get 0x00446A71,
// null-checked pointer 0x00A03354, tail-jmps to rowed 0x00444462.
// Evidence: mov ecx global plus call [eax+0xE0] plus Get plus
// mov ecx global plus jmp, 2 callers.
struct Global009FE958
{
	virtual int v00(); virtual int v01(); virtual int v02(); virtual int v03();
	virtual int v04(); virtual int v05(); virtual int v06(); virtual int v07();
	virtual int v08(); virtual int v09(); virtual int v10(); virtual int v11();
	virtual int v12(); virtual int v13(); virtual int v14(); virtual int v15();
	virtual int v16(); virtual int v17(); virtual int v18(); virtual int v19();
	virtual int v20(); virtual int v21(); virtual int v22(); virtual int v23();
	virtual int v24(); virtual int v25(); virtual int v26(); virtual int v27();
	virtual int v28(); virtual int v29(); virtual int v30(); virtual int v31();
	virtual int v32(); virtual int v33(); virtual int v34(); virtual int v35();
	virtual int v36(); virtual int v37(); virtual int v38(); virtual int v39();
	virtual int v40(); virtual int v41(); virtual int v42(); virtual int v43();
	virtual int v44(); virtual int v45(); virtual int v46(); virtual int v47();
	virtual int v48(); virtual int v49(); virtual int v50(); virtual int v51();
	virtual int v52(); virtual int v53(); virtual int v54(); virtual int v55();
	virtual int v56();
};
class LANAPI; extern LANAPI *TheLAN;
extern unsigned char Rva00446A71Get(void);
class Rva00444462
{
public:
	void rva00444462();
};
void Rva00248E98Enable(void)
{
	if (!((Global009FE958 *)TheLAN)->v56())
		return;
	if (!Rva00446A71Get())
		return;
	Outer00446A77 *p = g_Va00A03354;
	if (p == 0)
		return;
	return ((Rva00444462 *)p)->rva00444462();
}

// TheLAN (the data ledger's name): matched references place it at VA 0xdfe958.
LANAPI *TheLAN = 0;
// ?g_Va00A03354@@3PAUOuter00446A77@@A: the global at VA 0xe03354 is ?g_Va00A03354@@3HA.
#pragma comment(linker, "/alternatename:?g_Va00A03354@@3PAUOuter00446A77@@A=?g_Va00A03354@@3HA")
