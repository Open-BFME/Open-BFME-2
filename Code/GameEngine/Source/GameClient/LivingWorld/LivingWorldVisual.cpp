// cl: /O1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// LivingWorldVisual.cpp -- LivingWorldVisual members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// functions and the member m_primaryRObj at +0x08; retail supplies the bytes.
//
// setHouseColor (retail 0x003FB602; WB vtable pairing) sends the colour to
// render-object slot 126 (+0x1F8) in the 16-byte option block below: its
// leading 3-bit field set to 1 and the next two fields cleared (top bit
// kept), then the colour and two zero words.
//
// createRenderObject (retail 0x003FCEA3, WB 0x0106E830) builds the primary
// render object: through the rowed option-taking factory 0x00137364 (scale
// 1.0, the same option block carrying the house colour) when a colour is
// given, else through Create_Render_Obj 0x00136175. With a non-empty list of
// sub-object names it hides every sub-object whose name matches none of them,
// either bare or as "<model>.<name>" (no case), then releases each one. The
// release build has no found-bit vector: WB's duplicate / not-found checks are
// debug-only. Last it records the shadow type and creates the shadow.
// The "<model>.<name>" concat and compare go through the rowed address-named
// helpers the ledger already spells: operator+ 0x000B49C5 (AsciiString plus
// text node), Rva005F17C6Build 0x005F17C6 (node plus the AsciiString element,
// passed as a dword) and Rva003FCE11Compare 0x003FCE11 (no-case compare of the
// name against the node); the call site 0x003FCFB5 is this body's.
//
// createShadow (retail 0x003FC6C3, WB 0x0106F5A0) adds the shadow for the
// primary render object once, when TheGlobalData's byte at +0x60 is set:
// a local shadow type info gets the visual's type (+0x10) and five zero
// Reals, goes to the rowed W3DShadowManager::addShadow 0x0009A8D3, and the
// returned shadow is enabled (byte +4). The info is constructed and destroyed
// by the rows 0x00079514 / 0x000793FA, which the ledger names AudioEventRTS;
// their two-string / int type at +8 / five-Real layout is the shadow type
// info's, so ShadowTypeInfo derives from that view exactly as
// W3DShadowManagerAddShadow.cpp does.

#include "ascii_string.h"
#include <vector>

typedef int Int;

class AudioEventRTS
{
public:
	AudioEventRTS();
	~AudioEventRTS();
	AsciiString m_name0;		// +0x00
	AsciiString m_name4;		// +0x04
	Int m_type;					// +0x08
	float m_reals[6];			// +0x0C
	unsigned char m_flags[4];	// +0x24
};

class Shadow
{
public:
	struct ShadowTypeInfo : public AudioEventRTS
	{
	};
	virtual void release() = 0;
	void enableShadowRender(bool isEnabled) { m_isEnabled = isEnabled; }

protected:
	bool m_isEnabled;			// +0x04
};

class RenderObjClass;
class Drawable;

class W3DShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};
extern W3DShadowManager *TheW3DShadowManager;

class GlobalData
{
public:
	unsigned char m_pad00[0x60];
	bool m_useShadowVolumes;	// +0x60
};
extern GlobalData *TheWritableGlobalData;

// Render-object option block (rowed copy worker 0x0013101E).
class Rva0013101E
{
public:
	unsigned int m_a : 3;
	unsigned int m_b : 27;
	unsigned int m_c : 1;
	unsigned int m_keep : 1;
	unsigned int m_d1;
	unsigned int m_d2;
	unsigned int m_d3;
};

class RenderObjClass
{
public:
	virtual void Delete_This();
	virtual void s001(); virtual void s002(); virtual void s003(); virtual void s004();
	virtual void s005();
	virtual const char *Get_Name() const;					// +0x18
	virtual void s007(); virtual void s008(); virtual void s009(); virtual void s010();
	virtual void s011(); virtual void s012(); virtual void s013(); virtual void s014();
	virtual void s015(); virtual void s016(); virtual void s017(); virtual void s018();
	virtual void s019(); virtual void s020(); virtual void s021(); virtual void s022();
	virtual void s023(); virtual void s024(); virtual void s025(); virtual void s026();
	virtual void s027();
	virtual int Get_Num_Sub_Objects() const;				// +0x70
	virtual void s029();
	virtual RenderObjClass *Get_Sub_Object(int index) const;	// +0x78
	virtual void s031(); virtual void s032(); virtual void s033(); virtual void s034();
	virtual void s035(); virtual void s036(); virtual void s037(); virtual void s038();
	virtual void s039(); virtual void s040(); virtual void s041(); virtual void s042();
	virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046();
	virtual void s047(); virtual void s048(); virtual void s049(); virtual void s050();
	virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054();
	virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058();
	virtual void s059(); virtual void s060(); virtual void s061(); virtual void s062();
	virtual void s063(); virtual void s064(); virtual void s065(); virtual void s066();
	virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070();
	virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074();
	virtual void s075(); virtual void s076(); virtual void s077(); virtual void s078();
	virtual void s079(); virtual void s080(); virtual void s081(); virtual void s082();
	virtual void s083(); virtual void s084(); virtual void s085(); virtual void s086();
	virtual void s087(); virtual void s088(); virtual void s089(); virtual void s090();
	virtual void s091(); virtual void s092(); virtual void s093(); virtual void s094();
	virtual void s095(); virtual void s096(); virtual void s097(); virtual void s098();
	virtual void s099(); virtual void s100();
	virtual void Set_Hidden(int onoff);						// +0x194
	virtual void s102(); virtual void s103(); virtual void s104(); virtual void s105();
	virtual void s106(); virtual void s107(); virtual void s108(); virtual void s109();
	virtual void s110(); virtual void s111(); virtual void s112(); virtual void s113();
	virtual void s114(); virtual void s115(); virtual void s116(); virtual void s117();
	virtual void s118(); virtual void s119(); virtual void s120(); virtual void s121();
	virtual void s122(); virtual void s123(); virtual void s124(); virtual void s125();
	virtual void Set_House_Color_Params(const Rva0013101E *params, Int flags);	// +0x1F8

	void Release_Ref() { if (--m_numRefs == 0) Delete_This(); }

private:
	Int m_numRefs;				// +0x04
};

RenderObjClass *Create_Render_Obj(const char *name);
RenderObjClass *Rva00137364CreateRenderObj(const char *name, float scale, const Rva0013101E &options);

struct Rva005F17C6S12
{
	int m0, m1, m2;
};

struct Rva005F17C6S16
{
	Rva005F17C6S16(const Rva005F17C6S16 &that);
	int m0, m1, m2, m3;
};

struct AsciiStringPlusText : public Rva005F17C6S12
{
};

AsciiStringPlusText operator+(const AsciiString &lhs, const char *rhs);
Rva005F17C6S16 __cdecl Rva005F17C6Build(const Rva005F17C6S12 &src, int v);
int __cdecl Rva003FCE11Compare(void *a, void *b);

typedef std::vector<AsciiString> AsciiStringVector;

class LivingWorldVisual
{
public:
	virtual void setHouseColor(const Int &color);
	RenderObjClass *createRenderObject(const AsciiString &modelName, const AsciiStringVector &subObjectNames,
		Int shadowType, const Int *houseColor);
	void createShadow();

private:
	unsigned char m_pad04[4];
	RenderObjClass *m_primaryRObj;		// +0x08
	Shadow *m_shadow;					// +0x0C
	Int m_shadowType;					// +0x10
};

// LivingWorldVisual::setHouseColor, retail 0x003FB602.
void LivingWorldVisual::setHouseColor(const Int &color)
{
	if (m_primaryRObj)
	{
		Rva0013101E params;
		params.m_a = 1;
		params.m_b = 0;
		params.m_c = 0;
		params.m_d1 = color;
		params.m_d2 = 0;
		params.m_d3 = 0;
		m_primaryRObj->Set_House_Color_Params(&params, 0);
	}
}

// LivingWorldVisual::createRenderObject, retail 0x003FCEA3.
RenderObjClass *LivingWorldVisual::createRenderObject(const AsciiString &modelName,
	const AsciiStringVector &subObjectNames, Int shadowType, const Int *houseColor)
{
	if (houseColor)
	{
		Rva0013101E options;
		options.m_a = 1;
		options.m_b = 0;
		options.m_c = 0;
		options.m_d1 = *houseColor;
		options.m_d2 = 0;
		options.m_d3 = 0;
		m_primaryRObj = Rva00137364CreateRenderObj(modelName.str(), 1.0f, options);
	}
	else
	{
		m_primaryRObj = Create_Render_Obj(modelName.str());
	}

	if (!subObjectNames.empty() && m_primaryRObj)
	{
		Int numSubObjects = m_primaryRObj->Get_Num_Sub_Objects();
		for (Int i = 0; i < numSubObjects; ++i)
		{
			RenderObjClass *subObj = m_primaryRObj->Get_Sub_Object(i);
			if (subObj)
			{
				bool hide = true;
				const char *name = subObj->Get_Name();
				if (name)
				{
					AsciiString subObjName(name);
					AsciiStringVector::const_iterator it = subObjectNames.begin();
					AsciiStringVector::const_iterator end = subObjectNames.end();
					for (; it != end; ++it)
					{
						if (subObjName.compareNoCase(*it) == 0
							|| Rva003FCE11Compare(&subObjName, &Rva005F17C6Build(modelName + ".", (int)it)) == 0)
						{
							hide = false;
							break;
						}
					}
				}
				subObj->Set_Hidden(hide);
				subObj->Release_Ref();
			}
		}
	}

	m_shadowType = shadowType;
	if (shadowType)
		createShadow();
	return m_primaryRObj;
}

// LivingWorldVisual::createShadow, retail 0x003FC6C3.
void LivingWorldVisual::createShadow()
{
	if (m_shadow == 0 && TheWritableGlobalData->m_useShadowVolumes)
	{
		Shadow::ShadowTypeInfo shadowInfo;
		shadowInfo.m_type = m_shadowType;
		shadowInfo.m_reals[0] = 0.0f;
		shadowInfo.m_reals[1] = 0.0f;
		shadowInfo.m_reals[2] = 0.0f;
		shadowInfo.m_reals[3] = 0.0f;
		shadowInfo.m_reals[4] = 0.0f;
		m_shadow = TheW3DShadowManager->addShadow(m_primaryRObj, &shadowInfo, 0);
		if (m_shadow)
			m_shadow->enableShadowRender(true);
	}
}
