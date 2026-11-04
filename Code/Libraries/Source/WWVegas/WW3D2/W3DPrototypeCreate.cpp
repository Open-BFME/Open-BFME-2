// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
//
// The Create slots (slot 15) of two BFME 2 W3D asset prototypes, Zero Hour's
// HLodPrototypeClass::Create and BoxPrototypeClass::Create behind BFME 2's
// asset-factory load check: unless slot 10 (+0x28) reports the asset loaded,
// slot 11 (+0x2C) loads it, then the render object is built from the
// definition the prototype owns at +0x14. Owner names are those of the rowed
// deleting destructors (Rva0017FFCA in table 0x00BD4F50, Gen_dtor_00972460 in
// table 0x00BD5010); these views define no constructor or destructor and emit
// no vtables.
//
// ?Create@Rva0017FFCA@@UAEPAVRenderObjClass@@XZ, retail 0x0017FEF0 (85 bytes):
// new HLodClass (0x16C bytes, rowed HLodClass(const HLodDefClass &)).
// ?Create@Gen_dtor_00972460@@UAEPAVRenderObjClass@@XZ, retail 0x00180794
// (129 bytes): the box definition's attribute bit 0 (W3D_BOX_ATTRIBUTE_ORIENTED)
// picks OBBoxRenderObjClass (0x148 bytes) over AABoxRenderObjClass (0x124).
#include "rendobj.h"

class HLodDefClass;
class HLodClass : public RenderObjClass
{
public:
	HLodClass(const HLodDefClass &def);
	virtual RenderObjClass *Clone(void) const;
	virtual void Render(RenderInfoClass &rinfo);
private:
	unsigned char m_padC4[0x16C - 0xC4];
};

struct W3dBoxStruct
{
	unsigned int Version;
	unsigned int Attributes;	// +0x04
};
class OBBoxRenderObjClass : public RenderObjClass
{
public:
	OBBoxRenderObjClass(const W3dBoxStruct &def);
	virtual RenderObjClass *Clone(void) const;
	virtual void Render(RenderInfoClass &rinfo);
private:
	unsigned char m_padC4[0x148 - 0xC4];
};
class AABoxRenderObjClass : public RenderObjClass
{
public:
	AABoxRenderObjClass(const W3dBoxStruct &def);
	virtual RenderObjClass *Clone(void) const;
	virtual void Render(RenderInfoClass &rinfo);
private:
	unsigned char m_padC4[0x124 - 0xC4];
};

enum
{
	W3D_BOX_ATTRIBUTE_ORIENTED = 0x00000001
};

class W3DAssetPrototypeView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09();
	virtual bool isLoaded();		// +0x28
	virtual void load();			// +0x2C
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual RenderObjClass *Create() = 0;	// +0x3C
protected:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva0017FFCA : public W3DAssetPrototypeView
{
public:
	virtual RenderObjClass *Create();
private:
	HLodDefClass *m_definition;	// +0x14
};

class Gen_dtor_00972460 : public W3DAssetPrototypeView
{
public:
	virtual RenderObjClass *Create();
private:
	W3dBoxStruct *m_definition;	// +0x14
};

RenderObjClass *Rva0017FFCA::Create()
{
	if (!isLoaded())
		load();
	if (m_definition)
		return new HLodClass(*m_definition);
	return 0;
}

RenderObjClass *Gen_dtor_00972460::Create()
{
	if (!isLoaded())
		load();
	if (m_definition)
	{
		if (m_definition->Attributes & W3D_BOX_ATTRIBUTE_ORIENTED)
			return new OBBoxRenderObjClass(*m_definition);
		else
			return new AABoxRenderObjClass(*m_definition);
	}
	return 0;
}
