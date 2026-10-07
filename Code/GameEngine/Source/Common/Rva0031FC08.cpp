// cl: /O1 /arch:SSE /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include "ascii_string.h"
#include <list>
#include "../GameClient/GUI/ControlBar/ControlBarSchemeManagerView.h"

// BFME1 donor guide 968ca36c32; BFME2 native0x31FC08/98B.
// Native setters and creation use the returned ControlBarScheme and prove
// its inline name subobject at +0. Complete scheme extent is not inferred.

ControlBarScheme *ControlBarSchemeManager::findControlBarScheme(AsciiString name)
{
	// This is the same one-word worker view used by the canonical string header.
	reinterpret_cast<StringBase<char> *>(&name)->toLower();
	ControlBarSchemeList::iterator it = m_schemeList.begin();
	ControlBarScheme *res;
	for (;;)
	{
		if (it._M_node == m_schemeList.end()._M_node)
		{
			res = 0;
			break;
		}
		ControlBarScheme *scheme = *it;
		if (!scheme)
		{
			res = 0;
			break;
		}
		// Native callers prove that the scheme's inline name starts at +0.
		if (reinterpret_cast<const StringBase<char> *>(scheme)->compareNoCase(
			*reinterpret_cast<const StringBase<char> *>(&name)) == 0)
		{
			res = scheme;
			break;
		}
		++it;
	}
	return res;
}
