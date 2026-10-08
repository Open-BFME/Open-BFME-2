// cl: /G7 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// BFME stores the texture stages as one-word owning wrappers.  Keeping that
// layout local avoids changing the later vendored MaterialPassClass header,
// while allowing MSVC to emit the retail array-destructor cleanup sequence.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
// Retail's out-of-line RefCountClass deleting-dtor copy is the /O1 form
// (pop ecx after the delete call); this TU builds /G7 which emits add esp,4
// instead. Compile just the base class for size so our COMDAT matches the
// first copy in link order. Code this TU's rows inline keeps this TU's flags.
#pragma optimize("s", on)
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	void Add_Ref() { ++NumRefs; }

	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	virtual void Delete_This() { delete this; }

protected:
 	virtual ~RefCountClass() {}

private:
 	int NumRefs;
};
#pragma optimize("", on)

class MaterialPassStage
{
public:
	MaterialPassStage();
	~MaterialPassStage();

private:
	void *Pointer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h
class MaterialPassClass : public RefCountClass
{
public:
 	virtual ~MaterialPassClass();
	RefCountClass *rva0013EF70() const;

private:
	MaterialPassStage Stages[8];
	int Shader;
	RefCountClass *Material;
	bool EnableOnTranslucentMeshes;
	int CullVolume;
};

inline MaterialPassClass::~MaterialPassClass()
{
	if (Material)
	{
		Material->Release_Ref();
		Material = 0;
	}
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeMaterialPassClassInlineAnchor@@YAXPAVMaterialPassClass@@@Z absent-from-retail
void _bfmeMaterialPassClassInlineAnchor(MaterialPassClass *p)
{
    p->MaterialPassClass::~MaterialPassClass();
}
#pragma inline_depth()
// BFME1 matpass.cpp rev9cbfb551fe20 Get_Material is the semantic lead.
// Native [0013EF70,0013EF7F) witnesses field2C, null guard and +4 refcount.
// Retain the existing base pointer view; the original return type and
// accessor spelling are not established from the target.
RefCountClass *MaterialPassClass::rva0013EF70() const
{
    if (Material)
        Material->Add_Ref();
    return Material;
}
