// ??0W3DVolumetricShadowV2@@QAE@PAPAV0@PAVRenderObjClass@@@Z
// partial score=0.98 date=2026-10-09
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Recovery guided by prior bank and pinned BFME1 575ba2b04 shadow sources.
// Target WB8DFDA0 names W3DVolumetricShadowV2 constructor; complete
// native10811E..10837F has RET8. Target fields68/6C/74/78/7C/80/84
// and array sizes/mesh flags are independently read from native bytes.
// Donor supplies the shadow initialization purpose and reference ownership.
// Candidate: ??0W3DVolumetricShadowV2@@QAE@PAPAV0@PAVRenderObjClass@@@Z at
// Mesh-pointer same-valued PHI in the filtering loop preserves native EBX
// zero and EDI index without adding instructions. Canonical Coord3D remains
// the data layout; the scoped lifetime adapter proves the folded callback.
// strstr reaches retail through the msvcrt import while the vector's
// allocator frees through the game wrapper; declare the string header with
// the import attribute before the STLport headers see an empty _CRTIMP.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
extern "C" double __cdecl fabs(double value);
#include <vector>

#include "Code/Libraries/Include/Lib/Coord3D.h"
// Native array callback uses the owned empty three-byte constructor. This
// scoped lifetime view preserves canonical Coord3D's data layout.
struct Rva0010811EVertex : Coord3D { Rva0010811EVertex(); };
Rva0010811EVertex::Rva0010811EVertex() {}

struct Rva0010811EVector3
{
	float X;
	float Y;
	float Z;
};

struct AABoxClass
{
	Rva0010811EVector3 Center;
	Rva0010811EVector3 Extent;
};

class MeshModelClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

	int m_numRefs; // +0x04
	char m_pad08[0x24 - 8];
	int m_polyCount; // +0x24
	int m_vertexCount; // +0x28
};

struct Rva0010811EMaterialView
{
	char m_pad00[0x18];
	unsigned int m_flags; // +0x18
};

class MeshClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual const char *Get_Name() const; // +0x18
	MeshModelClass *Get_Model();
	void Add_Ref() { ++m_numRefs; }

	int m_numRefs; // +0x04
	char m_pad08[0xC4 - 8];
	Rva0010811EMaterialView *m_c4; // +0xC4
};

class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const; // +0x110
	void Add_Ref() { ++m_numRefs; }

	int m_numRefs; // +0x04
};

class Rva000F0F2B
{
public:
	Rva000F0F2B();
	virtual ~Rva000F0F2B();

private:
	char m_body[0x68 - 4];
};

struct W3DVolumetricShadowSubMesh
{
	MeshClass *m_mesh;
	Rva0010811EVertex *m_vertices;
	char *m_polygonFlags;
	int *m_indices;
	int m_10;
	bool m_isShadowMesh;
};

class W3DVolumetricShadowV2 : public Rva000F0F2B
{
public:
	W3DVolumetricShadowV2(W3DVolumetricShadowV2 **prevLink, RenderObjClass *renderObj);
	virtual ~W3DVolumetricShadowV2();
	void rva001080B4(_STL::vector<MeshClass *> *meshes, RenderObjClass *renderObj);
	void SetBoundingCircle(float radius) { m_boundingRadius = radius; }

private:
	W3DVolumetricShadowV2 **m_prevLink; // +0x68
	W3DVolumetricShadowV2 *m_next; // +0x6C
	int m_70;
	RenderObjClass *m_renderObj; // +0x74
	int m_numSubMeshes; // +0x78
	W3DVolumetricShadowSubMesh *m_submesh; // +0x7C
	float m_boundingRadius; // +0x80
	float m_height; // +0x84
	float m_88;
	float m_8C;
	Rva0010811EVector3 m_90;
};

// WWMath::Sqrt as the library writes it for x86 MSVC (wwmath.h): the x87
// fsqrt block with its single-precision argument and result spills.
static __forceinline float Rva0010811ESqrt(float val)
{
	float retval;
	__asm {
		fld [val]
		fsqrt
		fstp [retval]
	}
	return retval;
}

W3DVolumetricShadowV2::W3DVolumetricShadowV2(W3DVolumetricShadowV2 **prevLink, RenderObjClass *renderObj)
	: m_prevLink(prevLink), m_next(*prevLink), m_renderObj(renderObj), m_88(0.0f), m_8C(0.0f)
{
	if (m_next != 0)
		m_next->m_prevLink = &m_next;
	*prevLink = this;
	m_renderObj->Add_Ref();

	_STL::vector<MeshClass *> meshes;
	rva001080B4(&meshes, m_renderObj);
	for (unsigned int i = 0; i < meshes.size();)
	{
		if ((prevLink ? meshes[i] : meshes[i])->m_c4->m_flags & 0x1000)
			++i;
		else
		{
			(prevLink ? meshes[i] : meshes[i]) = meshes.back();
			meshes.pop_back();
		}
	}

	m_numSubMeshes = meshes.size();
	m_submesh = new W3DVolumetricShadowSubMesh[m_numSubMeshes];
	for (int k = 0; k < m_numSubMeshes; k++)
	{
		m_submesh[k].m_mesh = meshes[k];
		m_submesh[k].m_mesh->Add_Ref();
		MeshModelClass *mmc = m_submesh[k].m_mesh->Get_Model();
		m_submesh[k].m_vertices = new Rva0010811EVertex[mmc->m_vertexCount];
		m_submesh[k].m_polygonFlags = new char[mmc->m_polyCount];
		m_submesh[k].m_indices = new int[mmc->m_polyCount * 3];
		m_submesh[k].m_10 = 0;
		m_submesh[k].m_isShadowMesh = meshes[k]->Get_Name() != 0 && strstr(meshes[k]->Get_Name(), "SHADOW") != 0;
		mmc->Release_Ref();
	}

	AABoxClass box;
	m_renderObj->Get_Obj_Space_Bounding_Box(box);
	float x = fabs(box.Center.X) + box.Extent.X;
	float y = fabs(box.Center.Y) + box.Extent.Y;
	SetBoundingCircle(Rva0010811ESqrt(x * x + y * y));
	m_height = box.Center.Z + box.Extent.Z + 20.0f;
}
