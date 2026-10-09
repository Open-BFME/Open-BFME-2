// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0009DA3B@Rva0009D9BD@@QAEXXZ retail 0x0009DA3B..0x0009DB47 (268
// bytes). Rebuilds the shadow list of the Rva0009D9BD owner: the vector of
// shadows at +0x1C0 is first released through the rowed rva0009D9BD
// 0x0009D9BD when not empty; then with the asset manager at +0xD4 present
// each model name in the AsciiString vector at TheLivingWorldManager+0x19C
// is created through that manager (vtable +0x80 with a zero second
// argument) and given a shadow by W3DShadowManager::addShadow 0x0009A8D3
// from one local Shadow::ShadowTypeInfo (type 2 with the five floats from
// +0x0C zeroed; ctor 0x00079514 and dtor 0x000793FA). The render object
// reference is released inline (count at +4 and slot 0 on zero) and each
// shadow returned is appended with the bfmealloc pointer-vector push_back
// fold 0x004DFCB0. No donor or WorldBuilder twin; the owner class is the
// one the 0x0009D9BD/0x0009DA28 rows name and the method name is
// address-derived.
#include "ascii_string.h"
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>

class RenderObjClass
{
public:
	virtual void Delete_This();

	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

private:
	int m_numRefs; // +0x04
};

class Drawable;

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();

		AsciiString m_first; // +0x00
		AsciiString m_second; // +0x04
		int m_type; // +0x08
		float m_floatC;
		float m_float10;
		float m_float14;
		float m_float18;
		float m_float1C;
		float m_float20;
		unsigned char m_byte24;
		unsigned char m_byte25;
		unsigned char m_byte26;
	};
};

class W3DShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

extern W3DShadowManager *TheW3DShadowManager;

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
struct Rva0009DA3BManagerView
{
	char m_pad[0x19C];
	_STL::vector<AsciiString> m_shadowModelNames; // +0x19C
};

class Rva0009DA3BAssetManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual RenderObjClass *createRenderObj(const char *name, int arg); // +0x80
};

class Rva0009D9BD
{
public:
	void rva0009D9BD();
	void rva0009DA3B();

private:
	char m_pad00[0xD4];
	Rva0009DA3BAssetManager *m_assetManager; // +0xD4
	char m_padD8[0x1C0 - 0xD8];
	_STL::vector<Shadow *> m_shadows; // +0x1C0
};

void Rva0009D9BD::rva0009DA3B()
{
	if (!m_shadows.empty())
		rva0009D9BD();

	if (m_assetManager == 0)
		return;

	Shadow::ShadowTypeInfo shadowInfo;
	shadowInfo.m_type = 2;
	shadowInfo.m_floatC = 0.0f;
	shadowInfo.m_float10 = 0.0f;
	shadowInfo.m_float14 = 0.0f;
	shadowInfo.m_float18 = 0.0f;
	shadowInfo.m_float1C = 0.0f;

	// Retail recounts the names on every pass as end minus start and carries
	// no start register into the body: spell the count over the vector's own
	// start/finish pair (declared first) as the 0x0009D9BD sibling does.
	int *span = (int *)&reinterpret_cast<Rva0009DA3BManagerView *>(TheLivingWorldManager)->m_shadowModelNames;
	const _STL::vector<AsciiString> &names =
		reinterpret_cast<Rva0009DA3BManagerView *>(TheLivingWorldManager)->m_shadowModelNames;
	for (unsigned int i = 0; i < (unsigned)((span[1] - span[0]) >> 2); ++i)
	{
		RenderObjClass *robj = m_assetManager->createRenderObj(names[i].str(), 0);

		if (robj)
		{
			Shadow *shadow = TheW3DShadowManager->addShadow(robj, &shadowInfo, 0);
			robj->Release_Ref();
			if (shadow)
				m_shadows.push_back(shadow);
		}
	}
}
