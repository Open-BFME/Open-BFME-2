// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Open@XferSave@@QAEEPAVXfer@@H_N@Z @0x0060D10A 169B
// XferSave open-style writer. Evidence: neighbours 0x0060D0B3/0x0060D24D same TU,
// ALAE 0x45414c41 and 2STR 0x52545332 tags, 4 Xfer slot-4 writes checked for 4,
// vector erase at 0x31BD55 plus hashtable clears at 0x60CFB6/0x1DBCDC.
#include <vector>
#include <hash_map>

#include <cstddef>

namespace _STL {
template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline size_t vector<void *>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline void * &vector<void *>::operator[](size_t n) { return *(this->_M_start + n); }
}
// The bucket initializer (0x00148DDF) reads the vector end field and calls
// the canonical reserve/fill-insert providers, as in SelectionIDMap.cpp.
namespace _STL {
template <> __declspec(dllimport) __forceinline void **vector<void *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void *, allocator<void *> >::insert(void **pos, unsigned int n, void *const &x) { _M_fill_insert(pos, n, x); }
}
class Xfer {
public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual int write(const void *buf, int size);
};
enum NameKeyType {
    NAMEKEY_INVALID = 0,
    NAMEKEY_MAX = 1 << 23,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
namespace rts {
template <typename T> struct hash {
    unsigned int operator()(const T &v) const;
};
template <typename T> struct equal_to {
    bool operator()(const T &a, const T &b) const;
};
}
class FXList {
    int _x;
};
class ArmorTemplate {
public:
    float m_damageCoefficient[38];
};
typedef std::hash_map<NameKeyType, FXList, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > FXListMap;
typedef std::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, std::equal_to<NameKeyType> > ArmorMap;
class XferSave {
public:
    virtual ~XferSave();
    unsigned char Open(Xfer *stream, int arg2, bool arg3);
private:
    Xfer *volatile m_stream;
    bool m_flag;
    unsigned char m_pad[3];
    _STL::vector<void *> m_positions;
    FXListMap m_fx;
    ArmorMap m_armor;
};
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<_STL::pair<NameKeyType const,FXList> >(_STL::pair<NameKeyType const,FXList> *); }
namespace _STL { template <> void hashtable<_STL::pair<NameKeyType const,FXList>,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<_STL::pair<NameKeyType const,FXList> >,rts::equal_to<NameKeyType>,_STL::allocator<_STL::pair<NameKeyType const,FXList> > >::_M_delete_node(_STL::_Hashtable_node<_STL::pair<NameKeyType const,FXList> > *); }
namespace _STL { template <> void hashtable<_STL::pair<NameKeyType const,FXList>,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<_STL::pair<NameKeyType const,FXList> >,rts::equal_to<NameKeyType>,_STL::allocator<_STL::pair<NameKeyType const,FXList> > >::clear(); }
// bfme link decl-only end
unsigned char XferSave::Open(Xfer *stream, int arg2, bool arg3)
{
    if (m_stream != 0)
        return 0;
    int tag1 = 0x45414c41;
    int tag2 = 0x52545332;
    if (stream->write(&tag1, 4) != 4)
        return 0;
    if (stream->write(&tag2, 4) != 4)
        return 0;
    if (stream->write(&arg2, 4) != 4)
        return 0;
    int flag01 = (arg3 != 0) ? 1 : 0;
    if (stream->write(&flag01, 4) != 4)
        return 0;
    m_stream = stream;
    m_flag = arg3;
    _STL::vector<void *> *v = &m_positions;
    v->erase(v->begin(), v->end());
    m_fx.clear();
    m_armor.clear();
    return 1;
}
