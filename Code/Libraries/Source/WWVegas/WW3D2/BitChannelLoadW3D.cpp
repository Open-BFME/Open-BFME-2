// cl: /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/shims/sweep
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// BFME1 motchan.cpp BitChannel loader with target 24-byte field layout.
// HRaw read_bit_channel at18D4A0 calls this parser; target reads the 10-byte
// W3D bit-channel header and stores Bits at+14. Target omits the donor's
// assertion-only chunk-length query and unconditionally frees the old array.
#include "always.h"
#include "chunkio.h"
#include "w3d_file.h"
class BitChannelClass {
public:
    bool Load_W3D(ChunkLoadClass &cload);
private:
    unsigned long PivotIdx;
    unsigned long Type;
    int DefaultVal;
    int FirstFrame;
    int LastFrame;
    unsigned char *Bits;
    void Free() { delete [] Bits; Bits = 0; }
};
bool BitChannelClass::Load_W3D(ChunkLoadClass & cload)
{
	Free();



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
