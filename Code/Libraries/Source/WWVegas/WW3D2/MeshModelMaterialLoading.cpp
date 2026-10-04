// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/build/toolchains/dx81/include
//
// ?Peek_Legacy_Texture@MeshLoadContextClass@@AAE?AVBfmeHandleCX@@H@Z,
// retail 0x001893C0 (62 bytes).
// BFME1 MeshModelMaterialLoading.cpp donor-verbatim trimmed TU (placed body
// only; read_shaders / read_vertex_materials / read_textures live in their
// own TUs). LegacyMaterials object at context+0x94 (vector data at +0x98)
// with TextureIdx at entry+0x0C; miss returns an empty handle, hit forwards
// to Peek_Texture.
// One pin: Peek_Texture callee ?bfmeGet@Gen_0096D080.

class ChunkLoadClass
{
public:
	unsigned long Read(void *, unsigned long);
	bool Open_Chunk();
	bool Close_Chunk();
};

class TextureClass
{
public:
	void Add_Ref(void)
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
	}
	void Release_Ref(void);
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : p(0) {}
	BfmeHandleCX(const BfmeHandleCX &other) : p(other.p)
	{
		if (p) p->Add_Ref();
	}
	~BfmeHandleCX(void);
	BfmeHandleCX &operator=(const BfmeHandleCX &other)
	{
		if (other.p) other.p->Add_Ref();
		if (p) p->Release_Ref();
		p = other.p;
		return *this;
	}

	bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
	bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }

	TextureClass *p;
};

template <class T> class DynamicVectorClass
{
public:
	virtual ~DynamicVectorClass();
	virtual bool operator==(const DynamicVectorClass<T> &) const;
	virtual bool Resize(int newsize, T const *array = 0);
	virtual void Clear(void);
	virtual int ID(T const *ptr);
	virtual int ID(T const &ptr);

	int Length(void) const { return VectorMax; }
	int Count(void) const { return ActiveCount; }
	T &operator[](int index) { return Vector[index]; }

	bool Add(T const &object)
	{
		if (ActiveCount >= Length()) {
			if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
				if (!Resize(Length() + GrowthStep)) {
					return false;
				}
			} else {
				return false;
			}
		}
		(*this)[ActiveCount++] = object;
		return true;
	}

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
	int ActiveCount;
	int GrowthStep;
};

class MeshLoadContextClass
{
	BfmeHandleCX Peek_Texture(int index);
	BfmeHandleCX Peek_Legacy_Texture(int legacy_material_index);

private:
	struct LegacyMaterialClass {
		unsigned char nameAndMaterialIndices[0x0c];
		int TextureIdx;
	};
	unsigned char m_pad0[0x94];
public:
	DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
};

// ?Peek_Legacy_Texture@MeshLoadContextClass@@AAE?AVBfmeHandleCX@@H@Z
BfmeHandleCX MeshLoadContextClass::Peek_Legacy_Texture(int legacy_material_index)
{
	int ti = LegacyMaterials[legacy_material_index]->TextureIdx;
	if (ti != -1) {
		return Peek_Texture(ti);
	}
	return BfmeHandleCX();
}
