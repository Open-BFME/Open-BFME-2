// cl: /MD /EHsc /DNDEBUG
// Native boundary 0x002866B5..0x00286772, 189 bytes, RET 12: hidden
// three-float result, source-coordinate pointer, and float radius.
// Receiver +0x84 supplies a red-black sentinel, whose leftmost node is +8.
// Each node supplies signed integer coordinates at +0x18/+0x1C; its other
// payload words remain unknown. The walk uses the already-rowed STLport
// successor 0x00024250. Strictly nearer XY coordinates replace the local
// result inside radius squared; Z remains the source value. The original
// owner, node/key type and method name are unknown.
// The explicit output pointer models the observed return-buffer ABI, using
// the canonical Coord3D layout and copying its components as retail does.
#include "../../../Libraries/Include/Lib/Coord3D.h"
namespace _STL {
struct _Rb_tree_node_base {
 bool _M_color;
 _Rb_tree_node_base *_M_parent,*_M_left,*_M_right;
};
template<class Dummy>class _Rb_global {public:static _Rb_tree_node_base *__cdecl _M_increment(_Rb_tree_node_base *);};
}
struct Rva002866B5Node:public _STL::_Rb_tree_node_base {
 char unknown10[8];
 int x,y;
};
class Rva002866B5 {
public:
 Coord3D *rva002866B5(Coord3D *out,const Coord3D *location,float radius);
 char unknown00[0x84];
 _STL::_Rb_tree_node_base *head;
};
Coord3D *Rva002866B5::rva002866B5(Coord3D *out,const Coord3D *location,float radius) {
 Coord3D result;
 result.x=location->x;
 result.y=location->y;
 result.z=location->z;
 float limit=radius*radius;
 _STL::_Rb_tree_node_base *node=head->_M_left;
 while(node!=head) {
  Rva002866B5Node *point=static_cast<Rva002866B5Node *>(node);
  float x=(float)point->x;
  float y=(float)point->y;
  float dx=x-location->x;
  float dy=y-location->y;
  float distance=dx*dx+dy*dy;
  if(limit>distance) {
   result.x=x;
   result.y=y;
   limit=distance;
  }
  node=_STL::_Rb_global<bool>::_M_increment(node);
 }
 out->x=result.x;
 out->y=result.y;
 out->z=result.z;
 return out;
}
