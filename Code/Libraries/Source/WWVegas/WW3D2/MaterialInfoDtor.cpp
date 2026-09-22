// cl: /DNDEBUG /MD /EHsc
// BFME MaterialInfoClass destructor at 0x00930F60 / 175 bytes.
// Layout/vtable identities follow MaterialInfoClassCtor.cpp. Free releases
// materials first, then owned texture cells and vertex-pointer storage unwind.
// Nonthrowing array deallocation removes the spurious EH state before the
// final POD vector cleanup; TextureClass::Release_Ref can still unwind.

class VertexMaterialClass;
void __cdecl operator delete[](void *) throw();

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}

private:
	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

class TextureVectorBaseCtorShim
{
public:
	__declspec(noinline) TextureVectorBaseCtorShim(int, TextureVectorCell const *);
	virtual ~TextureVectorBaseCtorShim() {
  if(Vector && IsAllocated) { delete[] Vector; Vector=0; }
  IsAllocated=false;
  VectorMax=0;
 }
 TextureVectorBaseCtorShim &operator=(const TextureVectorBaseCtorShim &);

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

// VectorClass<VertexMaterialClass *>'s vtable (retail 0x00BD4628, installed by the
// matched MaterialCollectorClass dtor too). The BFME1 donor stored BFME1's address
// as an integer; referencing the vtable lets the build take the slot from retail.
extern "C" const unsigned char VectorClassVertexMaterialPtrVtable[];

class MaterialVector {
public:
 ~MaterialVector() {
  Vtable=(unsigned)VectorClassVertexMaterialPtrVtable;
  if(Vector && IsAllocated) { delete[] Vector; Vector=0; }
  IsAllocated=false;
  VectorMax=0;
 }
private:
 unsigned Vtable; VertexMaterialClass **Vector; int VectorMax;
 bool IsValid, IsAllocated; char pad[2]; int ActiveCount, GrowthStep;
};

class TextureVector : public TextureVectorBaseCtorShim
{
public:
private:
	int ActiveCount, GrowthStep;
};

class RefCountClass
{
public:
	RefCountClass() : Count(1) {}
	virtual void Delete_This() { delete this; }

protected:
	virtual ~RefCountClass() {}

private:
	int Count;
};

class MaterialInfoClass : public RefCountClass
{
public:
	MaterialInfoClass(const MaterialInfoClass &);
private:
 void Free();
public:
	virtual ~MaterialInfoClass();

private:
	MaterialVector VertexMaterials;
	TextureVector Textures;
};

MaterialInfoClass::~MaterialInfoClass()
{
 Free();
}

void Force_MaterialInfoClass_Deleting_Destructor(MaterialInfoClass *material_info)
{
	delete material_info;
}
