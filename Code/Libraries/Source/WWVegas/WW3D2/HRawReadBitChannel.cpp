// cl: /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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
// BFME1 raw-animation bit-channel reader. Target Load_W3D calls this
// helper at 18EAE2; allocation is 24 bytes and pre-3.0 adjusts PivotIdx.
class ChunkLoadClass;
class BitChannelClass {
public:
    BitChannelClass();
    bool Load_W3D(ChunkLoadClass &cload);
private:
    unsigned int PivotIdx, Type;
    int DefaultVal, FirstFrame, LastFrame;
    unsigned char *Bits;
    friend class HRawAnimClass;
};
class HRawAnimClass {
    bool read_bit_channel(ChunkLoadClass &cload, BitChannelClass **newchan, bool pre30);
};
bool HRawAnimClass::read_bit_channel(ChunkLoadClass &cload, BitChannelClass **newchan, bool pre30)
{
    *newchan = new BitChannelClass;
    bool result = (*newchan)->Load_W3D(cload);
    if (result && pre30) {
        (*newchan)->PivotIdx += 1;
    }
    return result;
}
