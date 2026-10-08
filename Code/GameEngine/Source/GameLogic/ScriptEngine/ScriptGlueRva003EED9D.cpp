// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva003EED9D@Rva003EED9D@@QAEXXZ @0x003EED9D 57B (dump range 18).
// Guarded forward: bails when this+4 is set, otherwise copies the
// this+0x1C name through the rowed StringBase copy ctor into the pinned
// 0x003EEC63 (this+4, name, 0, 0) call (doSetTeamState argument idiom),
// then tail-jumps the pinned 0x004E3B78 member on this+8.
#include "ascii_string.h"

class Rva003EEC63
{
public:
	void rva003EEC63(void *p, AsciiString s, bool a, bool b);
};
class Rva004E3CD0 { public: void rva004E3A6E(); };
struct Rva004E3B78Node {
    unsigned unknown00;
    Rva004E3B78Node *parent04, *left08, *right0C;
    unsigned unknown10;
    Rva004E3CD0 *value14;
};
namespace _STL {
    struct _Rb_tree_node_base;
    template<class T> class _Rb_global {
    public: static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
    };
}
class Rva004E3B78 {
public: void rva004E3B78();
private: Rva004E3B78Node *header00;
};

class Rva003EED9D
{
public:
	void rva003EED9D();
private:
	char m_pad00[0x04];
	void *m_p04; // +0x04
	char m_pad08[0x14];
	AsciiString m_name1C; // +0x1C
};

void Rva003EED9D::rva003EED9D()
{
	if (m_p04 != 0)
		return;
	((Rva003EEC63 *)this)->rva003EEC63((char *)this + 4, m_name1C, 0, 0);
	((Rva004E3B78 *)((char *)this + 8))->rva004E3B78();
}

// Complete native 41B traversal at 4E3B78..4E3BA1. The existing caller
// supplies its container at receiver+8. Payload and owner identities remain
// address-derived; nodes survive this value-reset pass.
void Rva004E3B78::rva004E3B78()
{
    for (Rva004E3B78Node *node=header00->left08; node!=header00;
         node=(Rva004E3B78Node *)_STL::_Rb_global<bool>::_M_increment(
             (_STL::_Rb_tree_node_base *)node)) {
        if (node->value14)
            node->value14->rva004E3A6E();
    }
}

// Native 3EEC63..3EED9D: 314B including RET16 and AsciiString cleanup.
// The adjacent rowed caller and reset caller establish pointer/name/flag ABI;
// BYTE test at +14 and direct bool forwarding at +10 correct the old int pin.
// WB friend_InitRegionStateObject is a semantic lead, not a claimed target name.
// Measured views: render transform translation +24/+34/+44 and slots50/54;
// scene height/add slots40/44 and writable-global flag87.
class RenderObjClass;
RenderObjClass *Create_Render_Obj(const char *);
void rva0010E4F6(void *,int);
class Rva002BF4F3 { public: void rva002BEA10(RenderObjClass *,bool); };
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct RegionObjectTransform
{
    float m[3][4];
    __forceinline RegionObjectTransform() {
        m[0][0]=1.0f;m[0][1]=0.0f;m[0][2]=0.0f;m[0][3]=0.0f;
        m[1][0]=0.0f;m[1][1]=1.0f;m[1][2]=0.0f;m[1][3]=0.0f;
        m[2][0]=0.0f;m[2][1]=0.0f;m[2][2]=1.0f;m[2][3]=0.0f;
    }
};
struct RegionPosition {
 float x,y,z;
 __forceinline RegionPosition(float a,float b,float c):x(a),y(b),z(c){}
};
class RegionRenderObjectView
{
public:
    virtual void s00();virtual void s04();virtual void s08();virtual void s0C();
    virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
    virtual void s20();virtual void s24();virtual void s28();virtual void s2C();
    virtual void s30();virtual void s34();virtual void s38();virtual void s3C();
    virtual void s40();virtual void s44();virtual void s48();virtual void s4C();
    virtual void slot50();
    virtual void slot54(const RegionObjectTransform &);
    char pad04[0x24-4];
    float x;
    char pad28[0x34-0x28];
    float y;
    char pad38[0x44-0x38];
    float z;
    __forceinline RegionPosition position() { slot50(); return RegionPosition(x,y,z); }
};
class RegionSceneView
{
public:
    virtual void s00();virtual void s04();virtual void s08();virtual void s0C();
    virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
    virtual void s20();virtual void s24();virtual void s28();virtual void s2C();
    virtual void s30();virtual void s34();virtual void s38();virtual void s3C();
    virtual float slot40();
    virtual void slot44(RenderObjClass *);
};
void Rva003EEC63::rva003EEC63(void *slot,AsciiString name,bool flag,bool prepare)
{
    RenderObjClass **out=(RenderObjClass **)slot;
    if (!*out) {
        RenderObjClass *renderObj=Create_Render_Obj(name.str());
        if (renderObj) {
            if (prepare) rva0010E4F6(renderObj,0);
            RegionObjectTransform transform;
            RegionRenderObjectView *view=(RegionRenderObjectView *)renderObj;
            RegionPosition pos=view->position();
            pos.z=((unsigned char *)TheWritableGlobalData)[0x87]
                ? -100.0f : ((RegionSceneView *)g_00DFEF18)->slot40();
            transform.m[0][3]=pos.x;transform.m[1][3]=pos.y;transform.m[2][3]=pos.z;
            view->slot54(transform);
            ((Rva002BF4F3 *)g_00DFEF18)->rva002BEA10(renderObj,flag);
            ((RegionSceneView *)g_00DFEF18)->slot44(renderObj);
        }
        *out=renderObj;
    }
}
