// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: ButterflyDrawModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class ButterflyDrawModuleInfo
{
public:
	ButterflyDrawModuleInfo(const ButterflyDrawModuleInfo &that);
	virtual void dummy();
};

// The tables are retail's exported names, at retail's addresses (reverse/exports.csv).
extern "C" const void *const __identifier("??_7ButterflyDrawModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@")[];
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
extern "C" const void *const __identifier("??_7ButterflyDrawModuleTemplate@FXParticleSystem@@6B@")[];

class ButterflyDrawModuleTemplate
{
public:
	ButterflyDrawModuleTemplate(const ButterflyDrawModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0ButterflyDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
ButterflyDrawModuleTemplate::ButterflyDrawModuleTemplate(
	const ButterflyDrawModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	ButterflyDrawModuleInfo *sub = (ButterflyDrawModuleInfo *)((char *)this + 8);
	sub->ButterflyDrawModuleInfo::ButterflyDrawModuleInfo(*(const ButterflyDrawModuleInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = (void *)__identifier("??_7ButterflyDrawModuleTemplate@FXParticleSystem@@6B@");
	m_v0 = (void *)__identifier("??_7ButterflyDrawModuleTemplate@FXParticleSystem@@6BModuleTemplate@1@@");
	m_v4 = &__identifier("??_7Rva003F498ACallback@@6B@");
}
}
// _ButterflyDrawModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ??_7Rva003F498ACallback@@6B@.
