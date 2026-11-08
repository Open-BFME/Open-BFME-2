// cl: /GX-

// Alpha default-module copy through its middle base, followed by four vptr stores.

class Rva003AEA42
{
public:
	Rva003AEA42(const Rva003AEA42 &other);
};

// Existing verified primary/factory arrays and compiler-emitted secondary tables.
// Native constructor operands independently establish these address bindings.
extern const void *const g_00C1CDCC[5];
extern const void *const g_00C1C504[6];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$00@1@@")[];
extern "C" const void *const __identifier("??_7Rva003ABC6E@@6BSnapshot@@@")[];

namespace FXParticleSystem
{
template <int CATEGORY>
class __declspec(novtable) DefaultModule
{
public:
    __declspec(noinline) DefaultModule(const DefaultModule &that);
    virtual DefaultModule *clone() const;

private:
    char m_storage[0x9C];
};

// ??0?$DefaultModule@$00@FXParticleSystem@@QAE@ABV01@@Z
template <>
DefaultModule<1>::DefaultModule(const DefaultModule<1> &that)
{
	const void *src = &that;
	((Rva003AEA42 *)this)->Rva003AEA42::Rva003AEA42(*(const Rva003AEA42 *)src);
	*(void **)this = (void *)g_00C1CDCC;
	*(void **)((char *)this + 0x14) = (void *)g_00C1C504;
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$00@1@@");
	*(void **)((char *)this + 0x1C) = (void *)__identifier("??_7Rva003ABC6E@@6BSnapshot@@@");
}
}
