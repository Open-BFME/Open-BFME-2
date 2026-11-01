// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva003EED9D@Rva003EED9D@@QAEXXZ @0x003EED9D 57B (dump range 18).
// Guarded forward: bails when this+4 is set, otherwise copies the
// this+0x1C name through the rowed StringBase copy ctor into the pinned
// 0x003EEC63 (this+4, name, 0, 0) call (doSetTeamState argument idiom),
// then tail-jumps the pinned 0x004E3B78 member on this+8.
#include "ascii_string.h"

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
void rva0010E4F6(void *,bool);
class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
