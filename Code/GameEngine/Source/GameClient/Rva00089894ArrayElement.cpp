// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Constructor89894/28B is the owner8990C callback for 255/4 elements,
// stride20. Target writes three zero floats, a null string-compatible slot
// at+C and word+10. Cleanup4F82B/8B tail-calls actual releaseBuffer36410.
// The shared owning view uses canonical AsciiString. Original identity and
// the meaning of the final word remain unknown; this is not GeometryRecord16.
#include "../../Include/GameClient/Rva0008990CArrayOwner.h"

Rva00089894ArrayElement::Rva00089894ArrayElement() : m_10(0)
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;
}

Rva00089894ArrayElement::~Rva00089894ArrayElement() {}
