// cl: /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?Rva0040D041Get@@YGPBVAsciiString@@H@Z @0x0040D041 26B: chain from bfmeFind1038 0x0040D008 returns +0x64 AsciiString or TheEmptyString when null. Evidence: calls rowed 0x0040D008; TheEmptyString 0x009E0878; same TU family as rowed Rva0040D366Get 0x0040D366.
class BfmeY1038
{
public:
	char m_pad[0x64];
	AsciiString m_64;
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
const AsciiString *__stdcall Rva0040D041Get(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return &AsciiString::TheEmptyString;
	return &y->m_64;
}
