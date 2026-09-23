// cl: /Ob2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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
// Donor: BFME1 WW3D2/hcanim.cpp, AdaptiveDelta read_channel overload.
// Target 0x18F230 allocates 0x1C bytes and calls ctor195F60 / loader195FF0.
// Their field stores support this local view; BFME1's cache fields are absent.
// The full101-byte wrapper ends at ret8 at18F292.

class ChunkLoadClass;
class AdaptiveDeltaMotionChannelClass
{
public:
    AdaptiveDeltaMotionChannelClass();
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
typedef char AdaptiveDeltaSizeCheck[sizeof(AdaptiveDeltaMotionChannelClass) == 0x1C ? 1 : -1];

class HCompressedAnimClass
{
private:
    bool read_channel(ChunkLoadClass &, AdaptiveDeltaMotionChannelClass **);
};
bool HCompressedAnimClass::read_channel(ChunkLoadClass &cload, AdaptiveDeltaMotionChannelClass **newchan)
{
    *newchan = new AdaptiveDeltaMotionChannelClass;
    bool result = (*newchan)->Load_W3D(cload);
    return result;
}
