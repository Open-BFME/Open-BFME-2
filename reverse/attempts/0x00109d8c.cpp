// ??0Rva00109D8C@@QAE@XZ
// partial score=1.0 date=2026-10-04
// cl: /O1 /G7 /arch:SSE2 /GX- /MD
// Clean BFME1 donor6d9434269164392c5ba62aaa7c15a86b5b020d76:
// game/GameEngine/Source/Common/Rva007B1380Ctor.cpp under sibling BFME2 flags.
// Target109D8C/26 calls132-byte EFA4E initializer, zeroes58/5C, storesBCEFA0.
// Donor virtual-handle name is not target identity; original class unknown.
// Use the rowed void initializer and preserve the observed ABI prefix.
// Dispatch-table identity/extent still require independent reconciliation;
// the current generic provider has4bytes, adjacent words do not prove extent.
struct RvaVec3
{
	float x;
	float y;
	float z;
};

class Rva000EFA4E
{
public:
	void initialize();
private:
	char m_pad00[4];
	unsigned char m_04;
	unsigned char m_05;
	char m_pad06[2];
	RvaVec3 m_08;
	RvaVec3 m_14;
	float m_20;
	int m_24;
	int m_28;
	int m_2C;
	unsigned char m_30;
	char m_pad31[3];
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
};



extern "C" const void *const vtbl_00BCEFA0[];
#pragma comment(linker, "/alternatename:_vtbl_00BCEFA0=??_7BfmeShadowBufferOwnerBase@@6B@")
class Rva00109D8C:public Rva000EFA4E { public:Rva00109D8C();unsigned word58,word5c; };
Rva00109D8C::Rva00109D8C() {
 initialize();word58=0;word5c=0;
 *(const void *const **)this=vtbl_00BCEFA0;
}
