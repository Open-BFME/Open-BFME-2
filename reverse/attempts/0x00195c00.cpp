// ?Load_W3D@BitChannelClass@@QAE_NAAVChunkLoadClass@@@Z
// partial score=0.9 date=2026-09-07
// ?Load_W3D@BitChannelClass@@QAE_NAAVChunkLoadClass@@@Z
// partial score=0.90 date=2026-09-07
// The BFME1 body is a strong 192-byte analogue.  The unconditional delete is
// needed for retail's opening release sequence, but retail still differs in
// Read/failure cleanup placement and call-site shape.  Keep this adaptation
// available for a later compiler/layout pass rather than leaving it in Code.
#include "motchan.h"

bool BitChannelClass::Load_W3D(ChunkLoadClass & cload)
{
	delete[] Bits;
	Bits = NULL;

	int chunk_size = cload.Cur_Chunk_Length();

	W3dBitChannelStruct chan;
	if (cload.Read(&chan,sizeof(W3dBitChannelStruct)) != sizeof(W3dBitChannelStruct)) {
		return false;
	}

	FirstFrame = chan.FirstFrame;
	LastFrame = chan.LastFrame;
	Type = chan.Flags;
	PivotIdx = chan.Pivot;
	DefaultVal = chan.DefaultVal;

	uint32 numbits = LastFrame - FirstFrame + 1;
	uint32 numbytes = (numbits + 7) / 8;
	uint32 bytesleft = numbytes - 1;

	assert((sizeof(W3dBitChannelStruct) + bytesleft) == (unsigned)chunk_size);

	Bits = MSGW3DNEWARRAY("BitChannelClass::Bits") uint8[numbytes];
	assert(Bits);

	Bits[0] = chan.Data[0];
	if (bytesleft > 0) {
		if (cload.Read(&(Bits[1]),bytesleft) != bytesleft) {
			Free();
			return false;
		}
	}

	return true;
}
