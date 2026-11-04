// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Reader algorithm adapted from Open-BFME-1 GameNetwork/NetPacket.cpp,
// donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76.
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// Existing wrapper reader at 0x0058E0E2, 299 bytes.
// Target allocation is 0x38 bytes; the canonical wrapper contract records
// its constructor and setter offsets. The donor supplied the reader algorithm.
#include <new>
#include "../../Include/GameNetwork/NetCommandMsg.h"
#include "../../Include/GameNetwork/NetWrapperCommandMsg.h"
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int) throw();
class NetPacket
{
protected:
    static NetCommandMsg *readWrapperMessage(UnsignedByte *data, Int &i);
};

NetCommandMsg * NetPacket::readWrapperMessage(UnsignedByte *data, Int &i) {
	NetWrapperCommandMsg *msg = new NetWrapperCommandMsg;

	// get the wrapped command ID
	UnsignedShort wrappedCommandID = 0;
	memcpy(&wrappedCommandID, data + i, sizeof(wrappedCommandID));
	msg->setWrappedCommandID(wrappedCommandID);
	i += sizeof(wrappedCommandID);

	// get the chunk number.
	UnsignedInt chunkNumber = 0;
	memcpy(&chunkNumber, data + i, sizeof(chunkNumber));
	msg->setChunkNumber(chunkNumber);
	i += sizeof(chunkNumber);

	// get the number of chunks
	UnsignedInt numChunks = 0;
	memcpy(&numChunks, data + i, sizeof(numChunks));
	msg->setNumChunks(numChunks);
	i += sizeof(numChunks);

	// get the total data length
	UnsignedInt totalDataLength = 0;
	memcpy(&totalDataLength, data + i, sizeof(totalDataLength));
	msg->setTotalDataLength(totalDataLength);
	i += sizeof(totalDataLength);

	// get the data length for this chunk
	UnsignedInt dataLength = 0;
	memcpy(&dataLength, data + i, sizeof(dataLength));
	i += sizeof(dataLength);

	UnsignedInt dataOffset = 0;
	memcpy(&dataOffset, data + i, sizeof(dataOffset));
	msg->setDataOffset(dataOffset);
	i += sizeof(dataOffset);

	msg->setData(data + i, dataLength);
	i += dataLength;

	return msg;
}


