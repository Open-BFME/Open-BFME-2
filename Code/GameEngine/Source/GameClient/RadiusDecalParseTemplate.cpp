// cl: /O1
// RadiusDecalTemplate::parseRadiusDecalTemplate (retail 0x00330D91, 19
// bytes). Zero Hour donor served from RadiusDecal.cpp: delegates the store
// to the retail decal sub-table at 0x00C0DC20 (Texture, Texture2, Style,
// OpacityMin/Max/ThrobTime, ...) through the rowed INI::initFromINI at
// 0x002DE78. Shared by the DecalTemplate and DeliveryDecal table entries.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class RadiusDecalTemplate
{
public:
	static void parseRadiusDecalTemplate(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseRadiusDecalTemplate@RadiusDecalTemplate@@SAXPAVINI@@PAX1PBX@Z
void RadiusDecalTemplate::parseRadiusDecalTemplate(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	ini->initFromINI(store, reinterpret_cast<const FieldParse *>(0x00C0DC20));
}
