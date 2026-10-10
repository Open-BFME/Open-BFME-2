// cl: /MD /Oy-
// Native Ghidra 0043B8C0..0043B920 RET8. DOTManager is established by
// the rowed neighbouring update/clear receivers, which use this same tree
// at +4. Search the int key, compare and replace an existing +14 value,
// or obtain a missing value through the 92-byte lower-bound/insert helper.
// The assignment provider proves the 88-byte value extent. Its original
// class name and the wrapper's method name remain unknown.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};


class Xfer::Version { public: Version(unsigned char n):m_version(n),m_max(n) {} unsigned char m_version,m_max; };
enum ObjectID { INVALID_OBJECT_ID=0 };
void XferObjectID(Xfer*,ObjectID*);

class Rva0043B163
{
public:
    Rva0043B163 &operator=(const Rva0043B163 &other);
    char unknown00[0x10];
    int value10;
    char unknown14[0x88 - 0x14];
};
class Rva0043B196 { char unknown00[0x88]; };
class Rva0043B2E2
{
public:
    Rva0043B196 &rva0043B864(const int &key);
    void *head;
    int flag;
};
class Rva00388F63Map { public: void *find(int *key); };
class Rva0043B8C0 { public: bool rva0043B0EA(void *current, void *incoming); };
class DOTManager
{
public:
    virtual void DoXfer(Xfer*);
    void rva0043B278(int key, int value);
    void rva0043B8C0(int key, const Rva0043B163 *incoming);
private:
    Rva0043B2E2 tree;
};

void DOTManager::rva0043B8C0(int key, const Rva0043B163 *incoming)
{
    void *node = reinterpret_cast<Rva00388F63Map *>(&tree)->find(&key);
    if (node != tree.head)
    {
        Rva0043B163 *current = reinterpret_cast<Rva0043B163 *>(
            static_cast<char *>(node) + 0x14);
        if (reinterpret_cast<Rva0043B8C0 *>(this)->rva0043B0EA(
                current, const_cast<Rva0043B163 *>(incoming)))
        {
            *current = *incoming;
            rva0043B278(key, incoming->value10);
        }
    }
    else
        reinterpret_cast<Rva0043B163 &>(tree.rva0043B864(key)) = *incoming;
}

namespace _STL {
struct _Rb_tree_node_base {
 bool m_color; _Rb_tree_node_base *parent,*left,*right;
};
template<class Dummy> class _Rb_global {
public: static _Rb_tree_node_base* __cdecl _M_increment(_Rb_tree_node_base*);
};
}
struct DOTRecordNode : _STL::_Rb_tree_node_base { ObjectID key; Rva0043B163 value; };
class Rva0043B208 { public: Rva0043B208 *rva0043B208(); };
class Rva0043B0B1 { public: void rva0043B0B1(Xfer*); };
// WB129DE80 names DOTManager::DoXfer; native43B920..43B9E8 is200B RET4.
// Native Version state is two bytes; load inserts 88B records, save walks
// the same +4 tree and xfers its ObjectID key and value at node+14.
void DOTManager::DoXfer(Xfer *xfer) {
 Xfer::Version version(1);
 *xfer==version;
 int count=tree.flag;
 *xfer==count;
 if(xfer->IsLoading()) {
  for(int i=0;i<count;++i) {
   ObjectID id;
   XferObjectID(xfer,&id);
   Rva0043B163 record;
   ((Rva0043B208*)&record)->rva0043B208();
   ((Rva0043B0B1*)&record)->rva0043B0B1(xfer);
   reinterpret_cast<Rva0043B163&>(tree.rva0043B864(reinterpret_cast<const int&>(id)))=record;
  }
 } else {
  DOTRecordNode *node=(DOTRecordNode*)((_STL::_Rb_tree_node_base*)tree.head)->left;
  while(node!=(DOTRecordNode*)tree.head) {
   ObjectID id=node->key;
   XferObjectID(xfer,&id);
   ((Rva0043B0B1*)&node->value)->rva0043B0B1(xfer);
   node=(DOTRecordNode*)_STL::_Rb_global<bool>::_M_increment(node);
  }
 }
}
