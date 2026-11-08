// cl: /MD
// ??0Rva003ACD71@@QAE@PAX0@Z @0x003ACD71 42B
// Chain ctor calling rowed base ??0Rva003ABA83 0x003ABA83 then vtable plus two
// immediates. Evidence: call target rowed; stores match retail order vtable
// g_00C1CC24 g_00C1C324; caller createModule at 0x003AD707.
extern "C" const void *const __identifier("??_7Rva003AE43F@@6BDefaultModuleHeadBase@@@")[];
extern "C" const void *const __identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@")[];
extern "C" const void *const __identifier("??_7Rva003AE43F@@6B@")[];
class Rva003ABA83
{
public:
	Rva003ABA83(void *a, void *b);
};
class __declspec(novtable) Rva003ACD71 : public Rva003ABA83
{
public:
	Rva003ACD71(void *a, void *b);
};
Rva003ACD71::Rva003ACD71(void *a, void *b)
	: Rva003ABA83(a, b)
{
	*(void **)this = (void *)__identifier("??_7Rva003AE43F@@6BDefaultModuleHeadBase@@@");
	*(void **)((char *)this + 0x14) = (void *)__identifier("??_7?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@6B?$CategoryModuleInfo@$05@1@@");
	*(void **)((char *)this + 0x18) = (void *)__identifier("??_7Rva003AE43F@@6B@");
}
