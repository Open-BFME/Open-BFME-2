// cl: /MD
// ??0Rva005FB400@@QAE@PBX@Z @0x005FB400 24B: honest ctor storing vtable VA 0x00C79F24 at [this] plus zeroes +4 plus copies *arg to +8. Evidence: caller new 0xc at 0x005FB46F plus ret 4 plus precedent Rva005FB22BCtor same 24B shape.
extern const void *const g_00C79F24[];
template <class T> class RvaCloneResult {
public: RvaCloneResult(T *p):pointer(p){if(p)++p->m_ref;} ~RvaCloneResult();
private: T *pointer;
};
class __declspec(novtable) Rva005FB400
{
public:
    Rva005FB400(const void *arg);
    virtual ~Rva005FB400();
    RvaCloneResult<Rva005FB400> clone() const;
    __forceinline Rva005FB400(const Rva005FB400 &src):m_ref(0) {
      *(const void **)this=g_00C79F24;m_08=src.m_08;
    }
private:
    template<class T> friend class RvaCloneResult;
    int m_ref;
    void *m_08;
};
Rva005FB400::Rva005FB400(const void *arg)
{
    m_ref = 0;
    *(const void **)this = g_00C79F24;
    m_08 = *(void *const *)arg;
}

// Native 005FB4A1: copy payload+8 into fresh12-byte counted object.
RvaCloneResult<Rva005FB400> Rva005FB400::clone() const {
 return RvaCloneResult<Rva005FB400>(new Rva005FB400(*this));
}
