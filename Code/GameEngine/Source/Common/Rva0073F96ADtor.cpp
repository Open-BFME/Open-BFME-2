// cl: /MD /EHsc
// ??1Rva0073F96A@@UAE@XZ @0x0073F96A 103B.
// Derived dtor releasing refcounted statics then base MaterialPassClass.
// Evidence: unlock lane packet; vtable store; globals E1F290/294/298.
class MaterialPassClass {
public:
    virtual ~MaterialPassClass();
};
typedef void (__stdcall *Rva0073F96ARel)(void *obj);
extern int g_bfmeCountAtE1F290;
// g_bfmeCountAtE1F290: matched references place it at VA 0xe1f290 (zero-filled .bss).
int g_bfmeCountAtE1F290;
extern void *g_bfmeObj1AtE1F294;
// g_bfmeObj1AtE1F294: matched references place it at VA 0xe1f294 (zero-filled .bss).
void * g_bfmeObj1AtE1F294;
extern void *g_bfmeObj2AtE1F298;
// g_bfmeObj2AtE1F298: matched references place it at VA 0xe1f298 (zero-filled .bss).
void * g_bfmeObj2AtE1F298;
class Rva0073F96A : public MaterialPassClass {
public:
    virtual ~Rva0073F96A();
};
Rva0073F96A::~Rva0073F96A()
{
    if (--g_bfmeCountAtE1F290 == 0) {
        void *o1 = g_bfmeObj1AtE1F294;
        if (o1)
            (*(Rva0073F96ARel **)o1)[2](o1);
        g_bfmeObj1AtE1F294 = 0;
        void *o2 = g_bfmeObj2AtE1F298;
        if (o2)
            (*(Rva0073F96ARel **)o2)[2](o2);
        g_bfmeObj2AtE1F298 = 0;
    }
}
