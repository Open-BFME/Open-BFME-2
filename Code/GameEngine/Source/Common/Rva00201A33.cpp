// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include "ascii_string.h"
#include <list>
#include "../GameClient/GUI/HeaderTemplateView.h"

// BFME1 donor guide 968ca36c32; BFME2 native 0x201A33/81B.
// Caller 0x201A84 reads the returned font at +0; parser 0x201CAF uses
// TheHeaderTemplateManager and creates the same template on a miss.
// Full bytes verify the canonical string/list form under unchanged O1/SSE/G7.

HeaderTemplate *HeaderTemplateManager::findHeaderTemplate(AsciiString name)
{
	HeaderTemplateList::iterator it = m_headerTemplateList.begin();
	while (it._M_node != m_headerTemplateList.end()._M_node)
	{
		HeaderTemplate *data = *it;
		if (data->m_name.compare(name) == 0)
			return data;
		++it;
	}
	return 0;
}
