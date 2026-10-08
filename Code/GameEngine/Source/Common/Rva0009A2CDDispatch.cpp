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
extern class Rva00108660ResourceManager *Rva00DEC2D8Manager;

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

extern class W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern StringBase<unsigned short> *g_00DEC2CC;
extern class Rva0007DA23ResourceManager *Rva00DE1FF8Manager;

void Rva0009A2CDRun()
{
	if ((*(Rva000F278F **)&TheW3DVolumetricShadowManager) != 0)
		(*(Rva000F278F **)&TheW3DVolumetricShadowManager)->rva000F278F();
	if (g_00DEC2CC != 0)
		g_00DEC2CC->validate();
	if ((*(R2GlobalReceiver **)&Rva00DEC2D8Manager) != 0)
		((BfmeThing928F *)(*(R2GlobalReceiver **)&Rva00DEC2D8Manager))->bfmeGo928F();
	if ((*(Rva0007BA35 **)&Rva00DE1FF8Manager) != 0)
		(*(Rva0007BA35 **)&Rva00DE1FF8Manager)->rva0007BA35();
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DEC2CC@@3PAV?$StringBase@G@@A=?TheW3DProjectedShadowManager@@3PAVW3DProjectedShadowManager@@A")
