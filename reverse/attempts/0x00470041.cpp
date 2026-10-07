// ?index@Rva00470041@@QAEAAMABG@Z
// partial score=0.92 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
#include <map>
struct Rva00470041Less : public _STL::less<unsigned short> {};
typedef _STL::map<unsigned short, float, Rva00470041Less> Rva00470041Map;
class Rva0046A9ABFloatLowerBound {
public:
    _STL::_Rb_tree_node<Rva00470041Map::value_type>* lower_bound(const unsigned short& key) const;
};
class Rva004DD25AFloatInsert {
public:
    Rva00470041Map::iterator insert(Rva00470041Map::iterator, const Rva00470041Map::value_type&);
};
class Rva00470041 {
public:
    float& index(const unsigned short& key);
};
float& Rva00470041::index(const unsigned short& key) {
    Rva00470041Map* map = (Rva00470041Map*)this;
    Rva00470041Map::iterator i(((Rva0046A9ABFloatLowerBound*)this)->lower_bound(key));
    if (i == map->end() || map->key_comp()(key, i->first))
        i = ((Rva004DD25AFloatInsert*)this)->insert(i, Rva00470041Map::value_type(key, float()));
    return i->second;
}
