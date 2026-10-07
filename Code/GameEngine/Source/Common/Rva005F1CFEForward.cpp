// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ?rva005F1CFE@Rva005F1CFEForwarder@@QAEXABVUnicodeString@@@Z @0x005F1CFE 8B
// Ptr-chase forwarder to Impl::SetTerritoryDescription. Evidence: mov ecx,[ecx+4] plus jmp to rowed 0x005F1C62.
#include "unicode_string.h"

namespace StrategicHUD {
class RegionDetailsTerritoryMovieClip {
public:
	class Impl;
};
}

class StrategicHUD::RegionDetailsTerritoryMovieClip::Impl {
public:
	void SetTerritoryDescription(const UnicodeString &text);
};

class Rva005F1CFEForwarder {
public:
	void rva005F1CFE(const UnicodeString &text);
private:
	char m_lead[4];
	StrategicHUD::RegionDetailsTerritoryMovieClip::Impl *m_impl;
};

void Rva005F1CFEForwarder::rva005F1CFE(const UnicodeString &text)
{
	m_impl->SetTerritoryDescription(text);
}
