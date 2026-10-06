// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// LargeGroupAudio::removeOverrides @0x0020DEB0 91B (WorldBuilder name,
// LargeGroupAudio.cpp lines 537..557: deleteOverrides over both lists, clear,
// copy, then the +0x34 overrides): cleanup of two
// pointer vectors then tail to Overridable::deleteOverrides. Evidence: rowed
// callees deleteOverrides 0x001E35ED erase 0x0031BD55 dup-assign 0x0026F4F4 and
// validate 0x000B3FD0; caller 0x0020DFD3; neighbours SubsystemNameGetters/next Rva0020DFFBRegister.
#include <vector>

class Overridable {
public:
    Overridable *deleteOverrides();
};

template <typename T> class StringBase {
    friend class LargeGroupAudio;
    void validate() const;
};

class LargeGroupAudio {
public:
    Overridable *removeOverrides();
private:
    char m_pad00[0x10];
    _STL::vector<unsigned int> m_vec10;
    _STL::vector<unsigned int> m_vec1C;
    _STL::vector<void *> m_vec28;
    Overridable *m_34;
};

Overridable *LargeGroupAudio::removeOverrides()
{
    for (unsigned int *it = m_vec1C.begin(); it != m_vec1C.end(); ++it) {
        ((Overridable *)*(void * const *)it)->deleteOverrides();
        ((StringBase<unsigned short> *)*(void * const *)it)->validate();
    }
    for (void **it = m_vec28.begin(); it != m_vec28.end(); ++it)
        ((Overridable *)*it)->deleteOverrides();
    _STL::vector<void *> &v28 = m_vec28;
    v28.erase(v28.begin(), v28.end());
    m_vec10 = m_vec1C;
    return m_34->deleteOverrides();
}
