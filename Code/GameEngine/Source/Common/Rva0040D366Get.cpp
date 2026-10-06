// cl: /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?Rva0040D366Get@@YGPBVAsciiString@@H@Z @0x0040D366 26B: chain from bfmeFind1038 0x0040D008 returns +0x20 AsciiString or TheEmptyString when null. Evidence: calls rowed 0x0040D008; TheEmptyString 0x009E0878; single caller jmp at 0x0023D070; prev 0x0040D34C next 0x0040D380 in Common.
class BfmeY1038
{
public:
	char m_pad[0x20];
	AsciiString m_20;
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
const AsciiString *__stdcall Rva0040D366Get(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return &AsciiString::TheEmptyString;
	return &y->m_20;
}
