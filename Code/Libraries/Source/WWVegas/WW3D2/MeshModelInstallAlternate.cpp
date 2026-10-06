// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME2 MeshModelClass::install_alternate_material_desc, retail RVA 0x00188290.
// Dedicated TU: the shared meshmdlio.cpp TU cannot host the out-of-line body
// (its include chain already declares the member). TU-local views anchored to
// retail immediates: DefMatDesc at +0x8C, AlternateMatDesc at +0x90, the load
// context AlternateMatDesc object at +0x124, MeshMatDescClass 0x118 bytes
// (operator-new immediate). Callees resolve by name to the ledger row (new),
// the MeshMatDesc default-ctor pin and the Is_Empty / Init_Alternate pins.

extern void *__cdecl operator new(unsigned int size);

class MeshMatDescClass
{
public:
	MeshMatDescClass();
	bool Is_Empty();
	void Init_Alternate(MeshMatDescClass &defDesc, MeshMatDescClass &contextDesc);

private:
	unsigned char m_data[0x118];
};

class MeshLoadContextClass
{
	friend class MeshModelClass;

private:
	unsigned char m_beforeAlternate[0x124];

public:
	MeshMatDescClass AlternateMatDesc;
};

class MeshModelClass
{
private:
	unsigned char m_beforeDef[0x8C];
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;

protected:
	void install_alternate_material_desc(MeshLoadContextClass *context);
};

void MeshModelClass::install_alternate_material_desc(MeshLoadContextClass *context)
{
	if (context->AlternateMatDesc.Is_Empty() == false) {
		AlternateMatDesc = new MeshMatDescClass;
		AlternateMatDesc->Init_Alternate(*DefMatDesc, context->AlternateMatDesc);
	}
}
