// cl: /DNDEBUG /MD /EHsc
// Retail RE: ?validate@ThingTemplate@@QAEXXZ @0x0033B4CD (108B).
//
// BFME2's validate() is a rewrite of the ZH/BFME1 shape (their validate() keeps
// the getTemplateGeometryInfo().getGeomType() switch; retail defaults the shadow
// texture through the usePluralShadowName() selector instead, the same idiom as
// BFME1's validateAudio(), and appends two wide-string fallback copies).
// Evidence for the identity:
// - sole caller (raw E8 scan) is the ThingTemplate reskin/parse worker at
//   0x002D1B2E ("DefaultThingTemplate" + "ObjectReskin must come after the
//   original Object" literals); our call is its last call before the epilogue,
//   exactly the thingTemplate->validate() slot of parseObjectDefinition.
// - "shadow" (0xBCFA20) / "shadows" (0xC10498) literals + isEmpty + selector.
// Callees (all pre-resolved, no new pins):
// - 0x001E2F narrow StringBase::isEmpty (matched row)
// - 0x6BE160 usePluralShadowName (matched BFME1-port row)
// - 0x0055F5 narrow StringBase::set(const char *) (matched row)
// - 0x35740 wide StringBase::isEmpty (matched row)
// - 0x37150 wide StringBase::set(const StringBase &) (existing pin)
// Layout is retail-measured: narrow shadow name +0x90, selector +0xA0 (0x2C pad
// + begin/end, per the usePluralShadowName TU), wide pairs +0x30->+0x58 and
// +0x38->+0x40. The wide members' true names are unknown; the mirror below
// keeps measured offsets with role-describing names and claims no real header.



#include "../../../Include/Common/BfmeThingTemplateShadowSelector.h"

#include "../../../Include/Common/ThingTemplate.h"

template <typename Char> static __forceinline StringBase<Char> &templateStringView(void *storage)
{
	return *reinterpret_cast<StringBase<Char> *>(storage);
}


void ThingTemplate::validate()
{
	if (templateStringView<char>(&m_shadowTextureName).isEmpty())
	{
		// no texture given, pick a default
		if (reinterpret_cast<const BfmeThingTemplateShadowSelector *>(m_geometryInfo)->usePluralShadowName())
			templateStringView<char>(&m_shadowTextureName).set("shadows");
		else
			templateStringView<char>(&m_shadowTextureName).set("shadow");
	}

	if (templateStringView<unsigned short>(m_displayNameStrategic + 4).isEmpty())
		templateStringView<unsigned short>(m_displayNameStrategic + 4).set(templateStringView<unsigned short>(m_displayName + 4));

	if (templateStringView<unsigned short>(m_descriptionStrategic + 4).isEmpty())
		templateStringView<unsigned short>(m_descriptionStrategic + 4).set(templateStringView<unsigned short>(m_description + 4));
}
