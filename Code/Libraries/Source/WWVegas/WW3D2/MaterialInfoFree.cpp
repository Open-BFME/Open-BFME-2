// cl: /G7 /DNDEBUG /MD /EHsc /O2 /Ob2
// ?Free@MaterialInfoClass@@AAEXXZ
// BFME1 MaterialInfoFree.cpp, adapted with /G7 for BFME2 RVA 0x16EE70.
// The matched MaterialInfo destructor calls this body at 0x17015C.
// Target code releases vertex materials and clears both vectors at +8/+0x20;
// helper names come from the donor. Full 105-byte body ends at ret 0x16EED8.

class BfmeRefObj
{
public:
	virtual void bfmeDelete(void);
	int m_refs;
};

class BfmeVecCX
{
public:
	virtual void bfmeV0(void);
	virtual void bfmeV1(void);
	virtual void Resize(int newsize, void *array);
	virtual void Clear(void);

	BfmeRefObj **m_vector;
	int m_max;
	int m_pad;
	int m_count;
	int m_growth;
};

class MaterialInfoClass
{
private:
	void Free(void);

	void *m_vptr;
	int m_refs;
	BfmeVecCX m_vmats;
	BfmeVecCX m_textures;
};

void MaterialInfoClass::Free(void)
{
	register MaterialInfoClass *self = this;
	register int i = 0;

	for (; i < self->m_vmats.m_count; i++)
	{
		BfmeRefObj *obj = self->m_vmats.m_vector[i];

		if (obj)
		{
			if (--obj->m_refs == 0)
				obj->bfmeDelete();

			self->m_vmats.m_vector[i] = 0;
		}
	}

	BfmeVecCX *vmats = &self->m_vmats;
	int vmax = vmats->m_max;
	vmats->Clear();
	vmats->Resize(vmax, 0);

	BfmeVecCX *textures = &self->m_textures;
	int tmax = textures->m_max;
	textures->Clear();
	textures->Resize(tmax, 0);
}
