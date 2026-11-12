// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// stlport
// ?GetImage@Rva005E16B9@@QAEPBVImage@@XZ @0x005E16B9 33B leaf image lookup through member AsciiString at +8.
// Evidence: retail lea esi [ecx+8] then rowed isEmpty 0x00001E2F then rowed findImageByName 0x002D92F6 through g_00DFF078; empty returns NULL.
#include "ascii_string.h"

#include "../../Include/GameClient/Image.h"

#include "../../Include/Common/Rva005E16B9.h"

const Image *Rva005E16B9::GetImage()
{
	if (!((const StringBase<char> *)&m_8)->isEmpty())
		return TheMappedImageCollection->findImageByName(m_8);
	return 0;
}
