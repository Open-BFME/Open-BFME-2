// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHa /Oy-

#include <new>

extern void *DebugAllocMemory(unsigned size);

class Rva00891540DebugIOCon
{
private:
    char m_body[0x110];
};

class DebugIOCon
{
public:
    DebugIOCon(void);

private:
    char m_body[0x110];
};

class Rva00891540DebugIOConFactory
{
public:
    static Rva00891540DebugIOCon *Create(void);
};

// ?Create@Rva00891540DebugIOConFactory@@SAPAVRva00891540DebugIOCon@@XZ
Rva00891540DebugIOCon *Rva00891540DebugIOConFactory::Create(void)
{
    return (Rva00891540DebugIOCon *)new (DebugAllocMemory(sizeof(Rva00891540DebugIOCon)))
        DebugIOCon();
}
