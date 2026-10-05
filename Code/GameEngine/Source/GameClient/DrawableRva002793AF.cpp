// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva002793AF@Rva002793AF@@QAEXABVAsciiString@@@Z @0x002793AF 65B
// Drawable-adjacent AsciiString selector at +0x348: if name is ReferenceDisplayName clear else set when nonempty.
// Evidence: callers 0x000C4E68 and 0x004B7ABA; callees rowed StringBase compare 0x000069B1 releaseBuffer 0x00036410 isEmpty 0x00001E2F set 0x000366F0; prev 0x00278689 Drawable.
#include "ascii_string.h"

class Rva002793AF
{
public:
	void rva002793AF(const AsciiString &name);
private:
	char m_pad[0x348];
	AsciiString m_str348;
};
void Rva002793AF::rva002793AF(const AsciiString &name)
{
	if (name.compare("ReferenceDisplayName") == 0)
		m_str348.clear();
	else if (!((const StringBase<char> *)&name)->isEmpty())
		((StringBase<char> *)&m_str348)->set(*(const StringBase<char> *)&name);
}
