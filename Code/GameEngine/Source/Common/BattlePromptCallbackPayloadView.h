#ifndef BFME2_BATTLE_PROMPT_CALLBACK_PAYLOAD_VIEW_H
#define BFME2_BATTLE_PROMPT_CALLBACK_PAYLOAD_VIEW_H

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C
{
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C() : m_ptr(0) {}
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
    ~TreeHintRef00217D4C()
    {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};

// Existing 50-byte factories return this one-pointer intrusive handle through
// a hidden result buffer. Native 005FADEF assigns the resulting handle using
// TreeHintRef's established operator and releases it through 0007DEEF.
template <class T> class RvaCloneResult
{
public:
    RvaCloneResult(T *p) : pointer(p) { if (p) ++p->m_ref; }
    ~RvaCloneResult()
    {
        if (pointer) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)pointer);
    }
    operator const TreeHintRef00217D4C &() const
    {
        return *(const TreeHintRef00217D4C *)this;
    }
private:
    T *pointer;
};

// 005FADEF writes three words and a byte at +0C; the constructors and clones
// copy all sixteen bytes, including the untouched padding after that byte.
// Context and callback-list meanings are inferred from these call sites.
struct Payload005FAB16
{
    int context;
    void *input;
    void *observers;
    bool flag;
};
struct Payload005FAB9E
{
    int context;
    void *input;
    void *observers;
    bool flag;
};

#endif
