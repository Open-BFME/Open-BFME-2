// cl: /Ireference/shims/bfme2_ascii /MD
// ?Rva002195B7CopyBackward@@YAPAVRva0021915B@@PAV1@00PAXH@Z @0x002195B7 47B
// copy_backward for Rva0021915B 8-byte entries using rowed assignment 0x0021915B.
// Same 47B shape as Rva0040D251CopyBackward (backwards --last/--dest loop with
// sar 3 count) plus the two dummy trailing args (tag pointer plus zero) that
// ride dead above the frame as in EightByteVectorCopyLoop; caller 0x00219947
// passes 5 args (first/last/dest/tag/0) with add esp,0x14.
// Evidence: stride 8 (sar 3) proves 8B entries; per-element call folds to rowed
// ??4Rva0021915B at 0x0021915B; forwarder at 0x00219947.

#include "ascii_string.h"

class Rva0021915B
{
public:
	Rva0021915B &operator=(const Rva0021915B &other);

private:
	AsciiString m_str;
	unsigned char m_byte;
};

Rva0021915B *__cdecl Rva002195B7CopyBackward(Rva0021915B *first, Rva0021915B *last, Rva0021915B *dest, void *tag, int extra)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		--last;
		--dest;
		*dest = *last;
	}
	return dest;
}

Rva0021915B *__cdecl Rva00219947Forward(Rva0021915B *first, Rva0021915B *last, Rva0021915B *dest, void *ignored)
{
	char tag;
	return Rva002195B7CopyBackward(first, last, dest, &tag, 0);
}
