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

template <typename T>
class StringBase
{
public:
	bool isEmpty() const;
	void set(const char *text);
	void set(const StringBase &other);

private:
	void *m_data;
};

class BfmeThingTemplateShadowSelector
{
public:
	bool usePluralShadowName() const;

private:
	char m_pad[0x2c];
	const char *m_begin;
	const char *m_end;
};

class ThingTemplate
{
public:
	void validate();

private:
	char m_pad0[0x30]; // +0x00
	StringBase<unsigned short> m_wideSrcA; // +0x30
	char m_pad34[0x4]; // +0x34
	StringBase<unsigned short> m_wideSrcB; // +0x38
	char m_pad3C[0x4]; // +0x3C
	StringBase<unsigned short> m_wideDstB; // +0x40
	char m_pad44[0x14]; // +0x44
	StringBase<unsigned short> m_wideDstA; // +0x58
	char m_pad5C[0x34]; // +0x5C
	StringBase<char> m_shadowTextureName; // +0x90
	char m_pad94[0xc]; // +0x94
	BfmeThingTemplateShadowSelector m_shadowSelector; // +0xA0
};

void ThingTemplate::validate()
{
	if (m_shadowTextureName.isEmpty())
	{
		// no texture given, pick a default
		if (m_shadowSelector.usePluralShadowName())
			m_shadowTextureName.set("shadows");
		else
			m_shadowTextureName.set("shadow");
	}

	if (m_wideDstA.isEmpty())
		m_wideDstA.set(m_wideSrcA);

	if (m_wideDstB.isEmpty())
		m_wideDstB.set(m_wideSrcB);
}
