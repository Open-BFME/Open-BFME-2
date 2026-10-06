// cl: /O1 /MD /EHsc
// ??0Rva000F1A32@@QAE@XZ 0x000F1A32 166B ctor creating Rva000F0AF7 at +8 and W3DBufferManager singleton with TCB vector resizes; caller 0x0009A710
class Rva000F0AF7 {
public:
    Rva000F0AF7();
private:
    void *m_a;
    void *m_b;
};
class W3DBufferManager {
public:
    W3DBufferManager();
private:
    char _s[0x4265c];
};
extern class W3DBufferManager *TheW3DBufferManager;
// g_00DEC3C0: matched references place it at VA 0xdec3c0 (zero-filled .bss).
class TCBSpline3DClass {
public:
    class TCBClass;
};
class TCBSpline3DClass::TCBClass {
public:
    float Tension;
    float Continuity;
    float Bias;
};
template<class T> class VectorClass {
public:
    VectorClass(int size = 0, T const *array = 0);
    virtual ~VectorClass();
    virtual bool operator==(VectorClass const &) const;
    virtual bool Resize(int size, T const *array = 0);
    virtual void Clear();
    virtual int ID(T const *);
    virtual int ID(T const &);
protected:
    T *Vector;
    int VectorMax;
    bool IsValid;
    bool IsAllocated;
    bool VectorClassPad[2];
};
template<class T> class DynamicVectorClass : public VectorClass<T> {
public:
    DynamicVectorClass(int size = 0, T const *array = 0);
    virtual ~DynamicVectorClass();
    virtual bool Resize(int size, T const *array = 0);
    virtual void Clear();
    virtual int ID(T const *);
    virtual int ID(T const &);
protected:
    int ActiveCount;
    int GrowthStep;
};
template<class T>
DynamicVectorClass<T>::DynamicVectorClass(int size, T const *array) :
    VectorClass<T>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
extern int g_00DEBE14;
// g_00DEBE14: matched references place it at VA 0xdebe14 (zero-filled .bss).
int g_00DEBE14;
extern int g_00DEBE2C;
// g_00DEBE2C: matched references place it at VA 0xdebe2c (zero-filled .bss).
int g_00DEBE2C;
extern DynamicVectorClass<TCBSpline3DClass::TCBClass> g_00DEBE0C;
extern DynamicVectorClass<TCBSpline3DClass::TCBClass> g_00DEBE24;
// g_00DEBE0C/g_00DEBE24: defined here (neighboring g_00DEBE14/2C pattern); Resize resolves to rowed 0x000F0CF9.
DynamicVectorClass<TCBSpline3DClass::TCBClass> g_00DEBE0C;
DynamicVectorClass<TCBSpline3DClass::TCBClass> g_00DEBE24;
class Rva000F1A32 {
public:
    Rva000F1A32();
private:
    int m_0;
    int m_4;
    Rva000F0AF7 *m_8;
};
Rva000F1A32::Rva000F1A32()
{
    m_0 = 0;
    m_4 = 0;
    m_8 = new Rva000F0AF7;
    W3DBufferManager *mgr = new W3DBufferManager;
    TheW3DBufferManager = mgr;
    if (g_00DEBE14 < 0x3e8)
        g_00DEBE0C.Resize(0x3e8, 0);
    if (g_00DEBE2C < 0x3e8)
        g_00DEBE24.Resize(0x3e8, 0);
}
