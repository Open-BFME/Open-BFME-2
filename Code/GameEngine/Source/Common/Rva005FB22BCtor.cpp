// cl: /MD
// ??0Rva005FB22B@@QAE@PBX@Z @ 0x005FB22B 24B
// Honest address-name ctor beside Rva005FA393Dtor. Target evidence: 24B
// retail stores vtable VA 0x879F04 at [this], zeroes +4, copies *arg to +8,
// 1 caller 0x5FB2B3, ret 4. Prev dtor shares /O1 /MD shape.
extern const void *const g_00879F04[];
template <class T> class RvaCloneResult {
public: RvaCloneResult(T *p):pointer(p){if(p)++p->m_ref;} ~RvaCloneResult();
private: T *pointer;
};
class __declspec(novtable) Rva005FB22B
{
public:
    Rva005FB22B(const void *arg);
    virtual ~Rva005FB22B();
    RvaCloneResult<Rva005FB22B> clone() const;
    __forceinline Rva005FB22B(const Rva005FB22B &src):m_ref(0) {
      *(const void **)this=g_00879F04;m_08=src.m_08;
    }
private:
    template<class T> friend class RvaCloneResult;
    int m_ref;
    void *m_08;
};
Rva005FB22B::Rva005FB22B(const void *arg)
{
    m_ref = 0;
    *(const void **)this = g_00879F04;
    m_08 = *(void *const *)arg;
}

// Native 005FB2CC: copy payload+8 into fresh12-byte counted object.
RvaCloneResult<Rva005FB22B> Rva005FB22B::clone() const {
 return RvaCloneResult<Rva005FB22B>(new Rva005FB22B(*this));
}
