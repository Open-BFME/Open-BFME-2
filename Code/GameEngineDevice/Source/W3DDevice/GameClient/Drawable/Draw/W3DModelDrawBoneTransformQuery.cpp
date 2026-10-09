// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Target B7F04..B7FE8: render pointer+44; slots50/51; a 48B Matrix3D
// result. ZH at pinned donor874e38488; W3DModelDraw::clientOnly_getRenderObjBoneTransform supplies
// the same null guard / index-zero identity / transform assignment purpose.
// Target receiver identity remains address-derived: the adjacent W3DModelDraw
// body uses +50 for a render pointer. Native call and data facts are independent
// of the donor name. Donor Matrix3D assignment supplies the copy semantics and
// compiler shape; replacing the old manual field copies closes branch layout.
#include "ascii_string.h"

#include "matrix3d.h"

class Rva000B7F04Src
{
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot047();
	virtual void vslot048();
	virtual void vslot049();
	virtual int vslot050(const char *s);
	virtual Matrix3D vslot051(int v);
};

class Rva000B7F04
{
public:
	bool rva000B7F04(const AsciiString *in, Matrix3D *out);

private:
	char m_pad00[0x44];
	Rva000B7F04Src *m_44;
};

// ?rva000B7F04@Rva000B7F04@@QAE_NPBVAsciiString@@PAVMatrix3D@@@Z
bool Rva000B7F04::rva000B7F04(const AsciiString *in, Matrix3D *out)
{
    if (!m_44) return false;
    int t=m_44->vslot050(in->str());
    if (t == 0) { out->Make_Identity(); return false; }
    else { *out=m_44->vslot051(t); return true; }
}
