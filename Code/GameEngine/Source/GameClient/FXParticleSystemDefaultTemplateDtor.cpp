// cl: /O1 /GX- /arch:SSE2
// BFME1 DefaultModuleTemplate<1> empty triple-vtbl dtor transferred to BFME2.
// Like its BFME1 model it stands apart from the wrapper TU: the template is
// redeclared here with no bases, so the destructor is three null-guarded
// vtable stores and nothing else - the 41 bytes retail folds every
// module-template destructor onto.

namespace FXParticleSystem
{

template <int CATEGORY>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<1>
{
public:
    virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<1>::~DefaultModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x00BBB554;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x00C1C780;
    *(volatile unsigned int *)this = 0x00BBB52C;
}

template <>
class __declspec(novtable) DefaultModuleTemplate<2>
{
public:
    virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<2>::~DefaultModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x00BBB554;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x00C1C780;
    *(volatile unsigned int *)this = 0x00BBB52C;
}

}
