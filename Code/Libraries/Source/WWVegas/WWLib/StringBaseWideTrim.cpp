// cl: /DNDEBUG /MD /EHs-c- /ICode/GameEngine/Source/Common/System
//
// BFME1 source model adapted to BFME2 StringBase<wchar_t>::trim(),
// RVA 0x00037F70, complete 127-byte body. BFME2 calls set(str, len)
// out of line; the donor inlined the setter branch. The shared helper
// remains exact at BFME2 RVA 0x00035800 (46 bytes).
//
// The leading helper is included from the actual visible TU body rather than
// declared as an ordinary external cdecl function.  SkipWhitespaceW.c defines
// file-static skipWhitespace(unsigned short*) and its visible keep-alive call;
// MSVC 7.1 consequently uses the private EAX-incoming convention seen at
// BFME2 RVA 0x00035800.  The same helper body is therefore available to this
// StringBase trim TU without an ABI-cast or a fabricated wrapper.

// Keep the helper out of line: retail trim has a direct REL32 to the
// file-static helper body rather than inlining its scan.
#define static __declspec(noinline) static
extern "C" {
#include "SkipWhitespaceW.c"
}
#undef static

typedef unsigned short WideChar;

#include "../../../../../reference/shims/bfme2_ascii/string_base.h"

template <>
void StringBase<WideChar>::trim()
{
    if (m_data)
    {
        // This call is intentionally to the actual file-static helper above;
        // its pointer arrives in EAX under MSVC's private static convention.
        const unsigned int c = (unsigned int)skipWhitespace(peek());

        if ((const WideChar *)c != peek())
        {
            int len = m_data ? m_data->length : 0;
            int skipped = c - (unsigned int)m_data - 8;
            skipped = skipped >> 1;
            len -= skipped;
            set((const WideChar *)c, len);
        }

        if (m_data)
        {
            int index = m_data->length;
            while (index > 0)
            {
                --index;
                if (_imp__iswspace((int)(unsigned short)(m_data ? m_data->data[index] : 0)))
                {
                    removeLastChar();
                }
                else
                {
                    break;
                }
            }
        }
    }
}
