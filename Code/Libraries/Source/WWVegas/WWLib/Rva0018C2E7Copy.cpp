// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0018C2E7Copy@@YAPAFPAURva0018C2E7Node@@0PAF0H@Z @ 0x0018C2E7 39B unlock: tree-to-short copy via rowed _M_increment. Caller 0x0018C3C9 passes 5 args.
// The node base is only named here, never laid out; the _Rb_global and node
// spellings are FXShaderGeometry.cpp's, the unit this body belongs to.
namespace _STL { struct _Rb_tree_node_base; }
namespace _STL {
template<class T> struct _Rb_global {static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);};

}
struct Rva0018C2E7Node { int unknown; void *parent; void *left; void *right; short value; };
short *__cdecl Rva0018C2E7Copy(Rva0018C2E7Node *first, Rva0018C2E7Node *last, short *result, void *tag1, int tag2);
short *__cdecl Rva0018C2E7Copy(Rva0018C2E7Node *first, Rva0018C2E7Node *last, short *result, void *tag1, int tag2)
{
	(void)tag1;
	(void)tag2;
	for (; first != last;) {
		short v = first->value;
		*result = v;
		++result;
		first = (Rva0018C2E7Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)first);
	}
	return result;
}
