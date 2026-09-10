// cl: /O1 /DNDEBUG /MD
//
// BfmeResetShaderRef::operator=(const BfmeResetAnyRef &), retail 0x0015142A,
// 50 bytes. Dedicated TU so dx8wrapper.cpp and the texture-assign unit cannot
// see this body. Non-FXSH holders are cleared; FXSH or null go through
// RefCountPtr assign. clear is the ICF twin already pinned on the texture ref.

struct BfmeResetTagged
{
	virtual int pad00();
	virtual int pad01();
	virtual int pad02();
	virtual int pad03();
	virtual int pad04();
	virtual int pad05();
	virtual int pad06();
	virtual int pad07();
	virtual int pad08();
	virtual int pad09();
	virtual int pad10();
	virtual int pad11();
	virtual int pad12();
	virtual unsigned GetClassId();
};

class BfmeMapPictureTexture
{
	void *pointer;

public:
	BfmeMapPictureTexture &operator=(const BfmeMapPictureTexture &);
};

struct BfmeResetAnyRef
{
	BfmeResetTagged *pointer;
};

struct BfmeResetTextureRef
{
	void *pointer;
	void clear();
};

struct BfmeResetShaderRef
{
	void *pointer;
	BfmeResetShaderRef &operator=(const BfmeResetAnyRef &rhs);
};

BfmeResetShaderRef &BfmeResetShaderRef::operator=(const BfmeResetAnyRef &rhs)
{
	if (rhs.pointer && rhs.pointer->GetClassId() != 0x46585348)
		((BfmeResetTextureRef *)this)->clear();
	else
		*(BfmeMapPictureTexture *)this = *(const BfmeMapPictureTexture *)&rhs;
	return *this;
}
