// cl: /O1 /EHsc /arch:SSE2
// RVA 0x001F448D..0x001F44E4. The following matched copy constructor
// identifies CategoryModuleTemplate<7>; the default constructor calls the
// independently matched WindModuleInfo constructor at 0x003A53C4 on this+8.
// Retail installs the established template tables at +0/+4/+8 and unwinds
// the dual-interface base if WindModuleInfo construction throws.
//
// Keep this constructor in an EH-enabled unit: the main template unit uses
// /GX-. These opaque views retain the known 8-byte base and 0x48-byte wind
// subobject, while novtable leaves table ownership in the existing units.
// The three secondary tables fold to the same retail address but remain
// separate symbols, as they are during normal C++ construction.
namespace FXParticleSystem {
extern "C" const void *const vtbl_00C1C780[];
extern "C" const void *const windBaseInfoTable[];
extern "C" const void *const windCategoryInfoTable[];
#pragma comment(linker, "/alternatename:_windBaseInfoTable=??_7?$CategoryModuleTemplateBase@$06@FXParticleSystem@@6BSecondaryModuleBase@1@@")
#pragma comment(linker, "/alternatename:_windCategoryInfoTable=??_7?$CategoryModuleTemplate@$06@FXParticleSystem@@6BSecondaryModuleBase@1@@")
extern "C" const void *const vtbl_00BBB58C[];
extern "C" const void *const vtbl_00BE16C8[];
extern "C" const void *const vtbl_00BE16D8[];
#pragma comment(linker, "/alternatename:_vtbl_00C1C780=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")
#pragma comment(linker, "/alternatename:_vtbl_00BBB58C=??_7?$CategoryModuleTemplateBase@$06@FXParticleSystem@@6BModuleTemplate@1@@")
#pragma comment(linker, "/alternatename:_vtbl_00BE16C8=??_7?$CategoryModuleTemplate@$06@FXParticleSystem@@6BModuleTemplate@1@@")
#pragma comment(linker, "/alternatename:_vtbl_00BE16D8=??_7?$CategoryModuleTemplate@$06@FXParticleSystem@@6B@")
template<int N> class __declspec(novtable) CategoryModuleTemplateBase {
public:
    CategoryModuleTemplateBase() {
        *(void *volatile *)&v4=(void*)windBaseInfoTable;
        *(void **)this=(void*)vtbl_00BBB58C;
        v4=(void*)vtbl_00C1C780;
    }
    virtual ~CategoryModuleTemplateBase();
    void *v4;
};
class __declspec(novtable) WindModuleInfo {
public:
    WindModuleInfo();
    virtual ~WindModuleInfo();
    char fields[0x44];
};
template<int N> class __declspec(novtable) CategoryModuleTemplate : public CategoryModuleTemplateBase<N> {
    WindModuleInfo wind;
public:
    CategoryModuleTemplate();
};
template<int N> CategoryModuleTemplate<N>::CategoryModuleTemplate() {
    *(void **)&wind=(void*)vtbl_00BE16D8;
    *(void **)this=(void*)vtbl_00BE16C8;
    v4=(void*)windCategoryInfoTable;
}
template CategoryModuleTemplate<7>::CategoryModuleTemplate();
}
