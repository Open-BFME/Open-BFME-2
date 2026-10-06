// cl: /DNDEBUG /MD
// ?rva00135E86@Rva00136001@@QAEAAV1@ABVHierarchyPrototype@@@Z @0x00135E86 134B.
// Rva00136001 texture adopt: if the prototype's class id (+0x34) is one of
// PART BOX MESH AGGR HLOD NULL rmod keep its texture ref via rowed
// RefCountPtr assign else rowed BfmeResetTextureRef clear. Evidence: unlock
// lane via 0x00136001 0x0013682B; caller 0x00136001 ctor passes own this;
// callees 0x0004D75B 0x000424D0 rowed; ret 4 returns this.
class TextureClass;
template<class T>
class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &that);
	T *p;
};
struct BfmeResetResource
{
	void Release_Ref();
};
struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};
class SubObject
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual int GetClassID();
};
class HierarchyPrototype
{
public:
	SubObject *m_obj;
};
class Rva00136001
{
public:
	Rva00136001 &rva00135E86(const HierarchyPrototype &proto);
};
Rva00136001 &Rva00136001::rva00135E86(const HierarchyPrototype &proto)
{
	if (proto.m_obj == 0
		|| proto.m_obj->GetClassID() == 0x50415254
		// class ID 'BOX' (0x00424F58), spelled as characters
		|| proto.m_obj->GetClassID() == (('B' << 16) | ('O' << 8) | 'X')
		|| proto.m_obj->GetClassID() == 0x4D455348
		|| proto.m_obj->GetClassID() == 0x41474752
		|| proto.m_obj->GetClassID() == 0x484C4F44
		|| proto.m_obj->GetClassID() == 0x4E554C4C
		|| proto.m_obj->GetClassID() == 0x6D6F6472)
		((RefCountPtr<TextureClass> *)this)->operator=((const RefCountPtr<TextureClass> &)proto);
	else
		((BfmeResetTextureRef *)this)->clear();
	return *this;
}
