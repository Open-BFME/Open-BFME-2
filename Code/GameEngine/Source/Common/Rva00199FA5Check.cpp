// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: null-gated twin init at 0x199FA5 (39B). Free cdecl
// function: returns false when the record's +0xC is null, otherwise runs
// two inits on it and returns true. Callee 0x15A800 reuses its rowed
// MeshMatDescClass name (second pin refused by gate); 0x15D5B0 pinned.

class MeshMatDescClass
{
public:
	void Set_Single_Rva0015A800(void *a, int b);
	void rva0015D5B0(int a);
};
class Rva00199FA5Rec
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

// ?rva00199FA5@@YA_NPAVRva00199FA5Rec@@@Z
bool rva00199FA5(Rva00199FA5Rec *p)
{
	if (p->m_0C == 0)
		return false;
	((MeshMatDescClass *)p)->Set_Single_Rva0015A800(0, 0);
	((MeshMatDescClass *)p)->rva0015D5B0(0);
	return true;
}
