// cl: /O1 /DNDEBUG /MD
//
// BfmeResetTextureRef::operator=(const BfmeResetAnyRef &), retail 0x00131D99,
// 50 bytes. Dedicated TU so dx8wrapper.cpp cannot see this body.
// Non-TEX holders are cleared; TEX or null go through RefCountPtr assign.

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
	BfmeResetTextureRef &operator=(const BfmeResetAnyRef &rhs);
};

BfmeResetTextureRef &BfmeResetTextureRef::operator=(const BfmeResetAnyRef &rhs)
{
	if (rhs.pointer && rhs.pointer->GetClassId() != 0x544558)
		clear();
	else
		*(BfmeMapPictureTexture *)this = *(const BfmeMapPictureTexture *)&rhs;
	return *this;
}
