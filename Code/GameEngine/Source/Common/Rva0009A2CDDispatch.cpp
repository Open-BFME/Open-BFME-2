// cl: /MD
// class-gate: allow StringBase private validate via friend free function for rowed 0x000B3FD0
//
// ?Rva0009A2CDRun@@YAXXZ @ 0x0009A2CD (61B):
// Free dispatch of four guarded globals then tail jmp to 0x0007BA35.
// Chain from 0x0007BA35 which this session landed. Globals by packet names.

void Rva0009A2CDRun();

template <typename T> class StringBase
{
	friend void Rva0009A2CDRun();
	void validate() const;
};

class Rva000F278F
{
public:
	void rva000F278F();
};

class R2GlobalReceiver
{
public:
	virtual void slot000();
	virtual void slot004();
};
extern R2GlobalReceiver *R2Ptr01306DF0;

class BfmeThing928F
{
public:
	void bfmeGo928F();
};

class Rva0007BA35
{
public:
	void rva0007BA35();
};

extern Rva000F278F *g_00DEBCD8;
extern StringBase<unsigned short> *g_00DEC2CC;
extern Rva0007BA35 *g_00DE1FF8;

void Rva0009A2CDRun()
{
	if (g_00DEBCD8 != 0)
		g_00DEBCD8->rva000F278F();
	if (g_00DEC2CC != 0)
		g_00DEC2CC->validate();
	if (R2Ptr01306DF0 != 0)
		((BfmeThing928F *)R2Ptr01306DF0)->bfmeGo928F();
	if (g_00DE1FF8 != 0)
		g_00DE1FF8->rva0007BA35();
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DEBCD8@@3PAVRva000F278F@@A=?TheW3DVolumetricShadowManager@@3PAVW3DVolumetricShadowManager@@A")
#pragma comment(linker, "/alternatename:?g_00DEC2CC@@3PAV?$StringBase@G@@A=?TheW3DProjectedShadowManager@@3PAVW3DProjectedShadowManager@@A")
#pragma comment(linker, "/alternatename:?g_00DE1FF8@@3PAVRva0007BA35@@A=?Rva00DE1FF8Manager@@3PAVRva0007DA23ResourceManager@@A")
