// cl: /MD
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
template<class T> class AptValuePtrStack {
    int m_nElements;
    int m_nCapacity;
    T **m_aElements;
public:
    int size() const { return m_nElements; }
    void pop();
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
};
void AptIntervalTimer::cleanParams()
{
    for (int n=pParams.size();n>0;--n) pParams.pop();
}
