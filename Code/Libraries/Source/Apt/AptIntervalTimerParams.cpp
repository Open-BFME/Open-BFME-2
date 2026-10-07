// cl: /O2 /Ob1 /MD /EHsc
// APT0.19.03 Xbox release donor GUID46a11dfd-96b7-4859-900b-d1c12429eda5 age126
// supplies AptIntervalTimer::cleanParams and AptValuePtrStack<AptValue>::pop.
// Target assertions independently name _AptValuePtrStack.h and size()>0.
// Target bodies6E0DA0+57 and6E3D50+82 agree with donor after address relocation.
// Target timer accesses establish embedded stack+0x14 and elements+0x1C;
// standalone pop corroborates count0/elements8 and Release virtual slot4.
// Unaccessed timer prefix stays opaque; donor fields there are not asserted.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
};
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *,unsigned int);
class Rva006DB270 { public: void freeBlock(void *,int); };
extern Rva006DB270* g_pChainBlockAllocator;
// Native6E3BA0..6E3BEA is this specialization's 74-byte destructor.
// Timer6E4F60 uses the same 12-byte member at+14. Its FuncInfo VA D62AF8
// has unwind state0 -> VA BA9140, which passes this+14 and jumps to6E3BA0.
// The _AptValuePtrStack.h assertion line52 agrees with the donor member type.
// The earlier address-derived AptBasePtrStack method owner was retired in a
// separate verified commit; no alternate-name or duplicate pin is needed.
template<class T> class AptValuePtrStack {
    int m_nElements;
    int m_nCapacity;
    T **m_aElements;
public:
    int size() const { return m_nElements; }
    inline void pop();
    ~AptValuePtrStack() {
        if(m_aElements) {
            if(!g_bfmeAptFreeSizeAtE17730) {
                g_bfmeAptAssertAtE17734("gAptFuncs.pfnMemFreeSize", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x52);
                if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
            }
            g_pChainBlockAllocator->freeBlock(m_aElements,m_nCapacity*4);
        }
    }
};
template<class T> void AptValuePtrStack<T>::pop()
{
    if (!(size()>0)) {
        g_bfmeAptAssertAtE17734("size() > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",125);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    m_aElements[m_nElements-1]->Release();
    --m_nElements;
}
template class AptValuePtrStack<AptValue>;
struct AptIntervalTimer {
    unsigned char unaccessed[20];
    AptValuePtrStack<AptValue> pParams;
    void cleanParams();
    ~AptIntervalTimer();
};
void AptIntervalTimer::cleanParams()
{
    for (int n=pParams.size();n>0;--n) pParams.pop();
}

// Complete native135-byte nonvirtual destructor6E4F60..6E4FE7, RET at6E4FE6.
// Destructor body cleans element references; member destruction then frees
// the backing store via the existing pool provider. Its one native unwind
// action also destroys this member. Names/type come from the existing release
// donor; target cleanParams call and EH action independently prove ownership.
AptIntervalTimer::~AptIntervalTimer() { cleanParams(); }
