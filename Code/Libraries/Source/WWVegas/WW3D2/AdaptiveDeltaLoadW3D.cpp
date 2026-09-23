// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc
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
// Donor: BFME1 WW3D2/motchan.cpp. Target 0x195FF0 reads the same 16-byte
// channel header but stores data in its 0x1C-byte object without donor caches.
// Field+10 holds bytes; allocation reserves that count plus one extra dword.
// Declare array operators so MSVC keeps new[] on the target array allocator.

extern void *__cdecl operator new[](unsigned int);
extern void __cdecl operator delete[](void *);
class ChunkLoadClass {
public:
    unsigned long Cur_Chunk_Length();
    unsigned long Read(void *, unsigned long);
};
struct W3dAdaptiveDeltaAnimChannelStruct {
    unsigned long NumFrames;
    unsigned short Pivot;
    unsigned char VectorLen;
    unsigned char Flags;
    float Scale;
    unsigned long Data[1];
};
class AdaptiveDeltaMotionChannelClass {
public:
    bool Load_W3D(ChunkLoadClass &);
private:
    unsigned long PivotIdx;
    unsigned long Type;
    int VectorLen;
    unsigned long NumFrames;
    unsigned long DataByteCount;
    float Scale;
    unsigned long *Data;
};
bool AdaptiveDeltaMotionChannelClass::Load_W3D(ChunkLoadClass &cload)
{
    unsigned long size = cload.Cur_Chunk_Length();
    unsigned long datasize = size - sizeof(W3dAdaptiveDeltaAnimChannelStruct);
    unsigned long numInts = (datasize / sizeof(unsigned long)) + 1;
    W3dAdaptiveDeltaAnimChannelStruct chan;
    if (cload.Read(&chan, sizeof(W3dAdaptiveDeltaAnimChannelStruct)) != sizeof(W3dAdaptiveDeltaAnimChannelStruct)) {
        return false;
    }
    VectorLen = chan.VectorLen;
    Type = chan.Flags;
    PivotIdx = chan.Pivot;
    NumFrames = chan.NumFrames;
    Scale = chan.Scale;
    Data = new unsigned long[numInts + 1];
    DataByteCount = numInts * sizeof(unsigned long);
    Data[0] = chan.Data[0];
    if (cload.Read(Data + 1, datasize) != datasize) {
        delete[] Data;
        Data = 0;
        return false;
    }
    return true;
}
