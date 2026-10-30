// ?Register_For_Rendering@MeshModelClass@@QAEXXZ
// cl: /DNDEBUG /MD
// MeshModelClass::Register_For_Rendering, retail RVA 0x00173230, 150 bytes.
//
// Provenance: the three callee identities are UNPROVEN and address-derived. The
// bank recorded their pins with placeholder argument types (P6A0@Z, PAV0@), which
// no C++ declaration can mangle to, so the REL32 sites emitted call 0 and the body
// could not be compared past +0x5A at all. The three pins are respelled here to the
// MeshMatDescClass/MeshModelClass-typed names this TU actually mangles to; the
// addresses, and therefore the callees they name, are unchanged.
//
// The renderer block layout was reached with an explicit goto. Both the if/else and
// the inverted !=/|| spellings canonicalise under this compiler to `jne ELSE / jne
// BOTH`, emitting the both-zero block first. Retail emits `jne SPECIALIZED / je
// PLAIN` -- the specialized block at 0x1732AA is the fallthrough and the plain one
// at 0x1732B8 the branch target -- which is what two early `goto`s out of a plain
// fallthrough block produce. The prior bank concluded this layout was unreachable
// from source; the layout is reachable, just not from a conditional.
//
// MeshModelClass and MeshMatDescClass here are TU-local spellings carrying the
// retail offsets (0x19 flags, 0x94 cur_mat_desc, 0xB8/0x108 descriptor fields,
// 0xC0 has_been_in_use); they are not recovered class definitions.
struct UVBufferClass;
class MeshMatDescClass;
class W3DMPO
{
};

class RefCountClass
{
public:
	void Add_Ref() { NumRefs++; }
	void Release_Ref() { if (--NumRefs == 0) Delete_This(); }
	RefCountClass() : NumRefs(1) {}
	RefCountClass(const RefCountClass &) : NumRefs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int NumRefs; // +0x04
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
private:
	void *ListNode; // +0x04
};

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~MeshGeometryClass();
	MeshGeometryClass &operator=(const MeshGeometryClass &that);

protected:
	// Needs_Vertex_Normals (0x00171850) proves the packed flag byte at +0x19.
	char m_pad10[0x19 - sizeof(RefCountClass) - sizeof(MultiListObjectClass)];
	unsigned char m_flagByte;
	char m_pad1A[0x8C - 0x1A];
};

class MeshModelClass : public MeshGeometryClass
{
public:
	virtual ~MeshModelClass();
	MeshModelClass &operator=(const MeshModelClass &that);
	bool Needs_Vertex_Normals();
	void Make_Geometry_Unique();
	void Init_For_NPatch_Rendering();
	void Register_For_Rendering();
	int Get_Flag(int mask) const { return m_flagByte & mask; }

	enum { PRELIT_MASK = 0xE0 };

protected:
	void clone_materials(const MeshModelClass &srcmesh);

private:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
	void *MatInfo;
	unsigned char pad2[0xC0 - 0x9C];
	bool HasBeenInUse;
};
class MeshMatDescClass
{
public:
	MeshMatDescClass(const MeshMatDescClass &that);
	~MeshMatDescClass();
	MeshMatDescClass &operator=(const MeshMatDescClass &that);
	bool Do_Mappers_Need_Normals();

	int PassCount;
	int VertexCount;
	int PolyCount;
	UVBufferClass *UV[8];
	char m_pad[0xB8 - 0x2C];
	unsigned *field_b8;
	unsigned char pad1[0x108 - 0xBC];
	unsigned *field_108;
	char m_pad10C[0x118 - 0x10C];
};
class Rva001735F9 { public: void rva001735F9(MeshModelClass *mesh); };
// 0x00145C30 is the rowed DX8MeshRendererClass::Register_Mesh_Type.
class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mmc);
	void Register_Mesh_Type(MeshModelClass *mesh);
};
class Rva00199FFB { public: static bool rva00199FFB(MeshMatDescClass *, MeshModelClass *); };

// The globals this body reads. LODMeshCacheSetting, TheMeshGapFillerContext
// and TheDX8MeshRenderer bind to their existing providers. The two remaining
// mode gates retain provisional address-derived names. Keep the flag's
// volatile access at the use site so the declaration names the byte provider.
// The two mode gates are ww3d.cpp's private WW3D statics NPatchesLevel
// (0x009B5F94) and NPatchesGapFillingMode (0x009B5F90).
class WW3D
{
public:
	enum NPatchesGapFillingModeEnum { NPATCHES_GAP_FILLING_DISABLED, NPATCHES_GAP_FILLING_ENABLED, NPATCHES_GAP_FILLING_FORCE };
private:
	friend class MeshModelClass;
	static NPatchesGapFillingModeEnum NPatchesGapFillingMode;
	static unsigned NPatchesLevel;
};
#define g_0DB5F94 (*(volatile unsigned *)&WW3D::NPatchesLevel)
#define g_0DB5F90 (*(volatile unsigned *)&WW3D::NPatchesGapFillingMode)
extern unsigned char LODMeshCacheSetting; // force-register flag
extern class Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;            // specialized renderer
extern class DX8MeshRendererClass *TheDX8MeshRenderer;            // plain renderer

void MeshModelClass::Register_For_Rendering()
{
    HasBeenInUse = true;
    if (g_0DB5F94 > 1) {
        if (g_0DB5F90 != 0) {
            Init_For_NPatch_Rendering();
        }
    } else if (g_0DB5F90 == 2) {
        Init_For_NPatch_Rendering();
    }

    MeshMatDescClass *desc = CurMatDesc;
    if (desc->field_b8 == 0 && desc->field_108 == 0) {
        if (*(volatile unsigned char *)&LODMeshCacheSetting != 0 || (m_flagByte & 4) != 0) {
            Rva00199FFB::rva00199FFB(desc, this);
        }
    }

    desc = CurMatDesc;
    // The two renderer globals sit on opposite arms of the source's branch order from
    // a naive reading: the 0x00DF363C renderer takes the field_b8==0 && field_108==0
    // arm. Only which branch each sits on is asserted here; the identity of the two
    // globals is untouched.
    //
    // The layout is reached with an explicit goto. See the header: every conditional
    // spelling canonicalises to the both-zero block first, which is not retail's.
    if (desc->field_b8 != 0) goto specialized;
    if (desc->field_108 != 0) goto specialized;
    {
        TheDX8MeshRenderer->Register_Mesh_Type(this);
    }
    return;
specialized:
    {
        Rva001735F9 *renderer = (*(Rva001735F9 **)&TheMeshGapFillerContext);
        renderer->rva001735F9(this);
    }
}
