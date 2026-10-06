// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// WaypointMap at MapMetaData+38 uses this AsciiString-to-Coord3D tree.
// Its copy chain reaches the proven32B node constructor3012CE; destruction
// at22D7FC calls clear22D160 then erase22CFB1. The value destroys only its
// string key: the pair dtor folds with the independently verified5B string
// release tail48BA39. Coord3D is three trivially destroyed scalar floats.
#include <map>
class AsciiString { void *m_data; public: ~AsciiString(); };
struct Coord3D { float x,y,z; };
typedef _STL::pair<const AsciiString,Coord3D> WaypointValue;
typedef _STL::_Rb_tree<AsciiString,WaypointValue,_STL::_Select1st<WaypointValue>,_STL::less<AsciiString>,_STL::allocator<WaypointValue> > WaypointTree;
template WaypointTree::~_Rb_tree();
