// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// Target Ghidra43-byte body: clear the list header at+0x910, then write
// signed bit pattern-2 to four words at+0x914/+0x918/+0x91C/+0x920.
// The list call uses the already rowed39-byte node-clear implementation.
// list<int> here is an ABI call view: the clear helper frees nodes without
// reading their payload. The original payload type spelling, class/method and
// complete object size remain unknown. The adjacent 219-byte query establishes
// two signed coordinate words per node and inclusive bounding limits at the
// four offsets. Its integer product is converted to float only after IMUL;
// horizontal edges and edges wholly above/below/left of the point are skipped.
// WB 0x00DB6570 has the same checks and wrapped list iteration, but no name.
// Original class and method names remain unasserted.
#include <list>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"
namespace _STL {
template<> void _List_base<int,allocator<int> >::clear();
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T,L>& a,
                              const _List_iterator<T,R>& b) {
    return a._M_node != b._M_node;
}
}
// Views for the selection iterator 0x0029FFFF (WB 0x00DB6770, unnamed).
static __forceinline bool Rva0029FFFFIsPoint(const IRegion2D &region2D) { return region2D.hi.y-region2D.lo.y==0 && region2D.hi.x-region2D.lo.x==0; }
struct Rva0087DC00Vec { int x,y,z; };
#include "../../Include/GameClient/Rva0087DC00.h"
class Rva00270FEE { public: char* rva00270FEE(); };
class Rva00276470Drawable { public: const Coord3D* rva00276470() const; };
template<int N> class BitFlags { public: bool test(const void*) const; };
class Drawable {
public:
    char pad00[4]; char* thingTemplate;
    char pad08[0x104-8]; Drawable* next;
};
class SelectionData { public: char pad[0x24]; BitFlags<69> excluded; };
class GameClientView {
public:
#define V(n) virtual void slot##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
#undef V
    virtual Drawable* firstDrawable();
};
class GameClient; extern GameClient* TheGameClient;
class TacticalView {
public:
#define V(n) virtual void slot##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
    virtual Drawable* pick(const ICoord2D*,bool,unsigned);
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
    V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
    V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
    V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
    V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
#undef V
    virtual void project(const Coord3D*,ICoord2D*);
};
class View; extern View* TheTacticalView;
unsigned Rva0030F099(bool);
class Rva0029C138 {
public:
    void rva0029C138();
    bool rva0029C163(const ICoord2D& point);
    int rva0029FFFF(int (*callback)(Drawable*,void*),void* data);
private:
    unsigned char m_prefix[0x8b8];
    bool m_forceAttack;
    unsigned char m_pad8b9[0x910-0x8b9];
    _STL::list<ICoord2D> m_points;
    union {
        struct { int m_word914,m_word918,m_word91C,m_word920; };
        IRegion2D bounds;
    };
};
void Rva0029C138::rva0029C138() {
    reinterpret_cast<_STL::_List_base<int,_STL::allocator<int> >*>(&m_points)->clear();
    m_word914=-2;
    m_word918=-2;
    m_word91C=-2;
    m_word920=-2;
}

bool Rva0029C138::rva0029C163(const ICoord2D& point) {
    if (point.x < m_word914) return false;
    if (point.y < m_word918) return false;
    if (point.x > m_word91C) return false;
    if (point.y > m_word920) return false;

    bool inside = false;
    for (_STL::list<ICoord2D>::iterator it = m_points.begin();
         it != m_points.end();) {
        ICoord2D a = *it;
        it++;
        ICoord2D b;
        if (it != m_points.end()) b = *it;
        else b = *m_points.begin();

        if (a.y == b.y) continue;
        if (a.y < point.y && b.y < point.y) continue;
        if (a.y >= point.y && b.y >= point.y) continue;
        if (a.x < point.x && b.x < point.x) continue;

        float intersection = (float)((point.y-a.y)*(b.x-a.x)) /
                             (float)(b.y-a.y) + (float)a.x;
        if (intersection >= (float)point.x) inside = !inside;
    }
    return inside;
}

// Native 0x0029FFFF..0x002A0161 RET8 selection iterator (WB 0x00DB6770): a
// degenerate region (under three polygon nodes, or a zero-area box) picks one
// drawable under the box corner; otherwise every drawable passes the data's
// exclusion mask and the polygon test before the callback runs. WorldBuilder
// keeps the visibility verdict in a bool local that the callback branch tests
// after the exclusion/projection block; that local (not an early continue on
// the polygon test) gives retail's block layout.
int Rva0029C138::rva0029FFFF(int (*callback)(Drawable*,void*),void* data) {
    int count=0;
    _ReadWriteBarrier();
    bool point=false;
    if(m_points.size()<3 || Rva0029FFFFIsPoint(bounds)) point=true;
    Drawable* only=0;
    if(point) {
        bool attack=m_forceAttack;
        only=((TacticalView*)TheTacticalView)->pick(&bounds.lo,true,Rva0030F099(attack));
        if(!only) return 0;
    }
    Drawable* draw=((GameClientView*)TheGameClient)->firstDrawable();
    for(;draw;draw=draw->next) {
        bool visible;
        if(only) { draw=only; visible=true; }
        else {
            visible=false;
            if(((SelectionData*)data)->excluded.test(draw->thingTemplate+0x108)) continue;
            Coord3D pos;
            ((Rva0087DC00*)((Rva00270FEE*)draw)->rva00270FEE())->get((Rva0087DC00Vec*)&pos);
            const Coord3D* base=((Rva00276470Drawable*)draw)->rva00276470();
            pos.x+=base->x; pos.y+=base->y; pos.z+=base->z;
            ICoord2D screen;
            ((TacticalView*)TheTacticalView)->project(&pos,&screen);
            visible=rva0029C163(screen);
        }
        if(visible) {
            int result=callback(draw,data);
            if(result==0) ++count;
            else if(result==1) count=1;
        }
        if(only) break;
    }
    return count;
}
