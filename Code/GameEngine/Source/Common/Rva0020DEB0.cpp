// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva0020DEB0@Rva0020DEB0@@QAEPAVOverridable@@XZ @0x0020DEB0 91B: cleanup of two
// pointer vectors then tail to Overridable::deleteOverrides. Evidence: rowed
// callees deleteOverrides 0x001E35ED erase 0x0031BD55 dup-assign 0x0026F4F4 and
// validate 0x000B3FD0; caller 0x0020DFD3; neighbours SubsystemNameGetters/next Rva0020DFFBRegister.
#include <vector>

class Overridable {
public:
    Overridable *deleteOverrides();
};

template <typename T> class StringBase {
    friend class Rva0020DEB0;
    void validate() const;
};

class Rva0020DEB0 {
public:
    Overridable *rva0020DEB0();
private:
    char m_pad00[0x10];
    _STL::vector<unsigned int> m_vec10;
    _STL::vector<unsigned int> m_vec1C;
    _STL::vector<void *> m_vec28;
    Overridable *m_34;
};

Overridable *Rva0020DEB0::rva0020DEB0()
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
