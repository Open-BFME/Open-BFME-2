// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva00493313@Rva00493313@@QBE?AVAsciiString@@XZ @0x00493313 32B: return final-override name at +0x5c.
// Evidence: calls friend_getFinalOverride 0x00288609 then StringBase copy 0x000365F0; ret 4 hidden AsciiString return.
#include "ascii_string.h"

class Overridable {
public:
	const Overridable *friend_getFinalOverride() const;
private:
	char m_pad[0x10];
};

class Rva00493313 : public Overridable {
public:
	AsciiString rva00493313() const;
private:
	char m_pad10[0x5c - 0x10];
	AsciiString m_name5c;
};
AsciiString Rva00493313::rva00493313() const
{
	const Rva00493313 *fin = (const Rva00493313 *)friend_getFinalOverride();
	return fin->m_name5c;
}
