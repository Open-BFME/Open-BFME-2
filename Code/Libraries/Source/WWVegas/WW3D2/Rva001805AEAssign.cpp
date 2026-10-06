// cl: /DNDEBUG /MD
// ?rva001805AE@BfmeResetTextureRef@@QAEAAU1@ABUBfmeResetAnyRef@@@Z @0x001805AE 50B
// Twin of BfmeResetTextureRef::operator= (0x00131D99 50B): if rhs.pointer
// and rhs GetClassId (slot 13 offset 0x34) != 0x50415254 TRAP then clear
// via rowed 0x0004D75B else assign via rowed RefCountPtr<TextureClass>
// operator= 0x000424D0. Called from 0x00180649.
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

class TextureClass;

template <class T>
class RefCountPtr
{
	void *pointer;
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
};

struct BfmeResetAnyRef
{
	BfmeResetTagged *pointer;
};

struct BfmeResetTextureRef
{
	void *pointer;
	void clear();
	BfmeResetTextureRef &rva001805AE(const BfmeResetAnyRef &rhs);
	BfmeResetTextureRef &rva00180815(const BfmeResetAnyRef &rhs);
};

BfmeResetTextureRef &BfmeResetTextureRef::rva001805AE(const BfmeResetAnyRef &rhs)
{
	if (rhs.pointer && rhs.pointer->GetClassId() != 0x50415254)
		clear();
	else
		*(RefCountPtr<TextureClass> *)this = *(const RefCountPtr<TextureClass> *)&rhs;
	return *this;
}

BfmeResetTextureRef &BfmeResetTextureRef::rva00180815(const BfmeResetAnyRef &rhs)
{
	// class ID 'BOX' (0x00424F58), spelled as characters
	if (rhs.pointer && rhs.pointer->GetClassId() != (('B' << 16) | ('O' << 8) | 'X'))
		clear();
	else
		*(RefCountPtr<TextureClass> *)this = *(const RefCountPtr<TextureClass> *)&rhs;
	return *this;
}
