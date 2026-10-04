// ??0Rva000F0F2B@@QAE@XZ
// partial score=1.0 date=2026-10-04
// cl: /O1 /G7 /arch:SSE2 /GX- /MD
// F0F2B/48 native constructor; original class name remains unknown.
// EFA4E is now a rowed void initializer, called before dispatch assignment.
// Prefix matches Rva000EFA4EBase.cpp; future landing must share that layout.
// Target tableBCEFA0 has three entries (EFAD2,B3FD0,__purecall).
// Existing BfmeShadowBufferOwnerBase table provider emits only four bytes,
// so its folded-address alias does not establish a complete usable table.
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
class Rva000F0F2B:public Rva000EFA4E { public:Rva000F0F2B();float value58,value5c,value60;bool flag64; };
Rva000F0F2B::Rva000F0F2B() {
 initialize();
 value58=0.0f;value5c=0.0f;
 *(const void *const **)this=vtbl_00BCEFA0;
 value60=20.0f;flag64=false;
}
