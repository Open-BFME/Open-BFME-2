// cl: /DNDEBUG /MD /EHsc
/*
 * Command & Conquer Generals Zero Hour(tm)
 * Copyright 2025 Electronic Arts Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
// AggregateDefClass::Read_Info, ported from BFME1 donor revision
// 5cae4bdffcc0fb2dd6f0a2a6c1a7328bd0fb0cfc,
// game/Libraries/Source/WWVegas/WW3D2/agg_def.cpp.
// Target vtable VA 0x00BD6C70 slot +0x10 names retail RVA 0x001A3460.
// Target independently confirms info +0x20 (36 bytes), unsigned count +0x40,
// bool result, and Read_Subobject dispatch through slot +0x14. The last
// ret 4 ends at RVA 0x001A34C8, followed by eight padding int3 bytes.
// Field names and the read-loop algorithm are carried from the donor.
extern "C" void * __cdecl memset(void *, int, unsigned);
#pragma intrinsic(memset)
class ChunkLoadClass {
public:
    unsigned long Read(void *, unsigned long);
};
class ChunkSaveClass;
struct W3dAggregateInfoStruct {
    char BaseModelName[32];
    unsigned SubobjectCount;
};
class AggregateDefClass {
public:
    virtual ~AggregateDefClass();
    virtual bool Load_W3D(ChunkLoadClass &);
    virtual bool Save_W3D(ChunkSaveClass &);
protected:
    virtual bool Read_Header(ChunkLoadClass &);
    virtual bool Read_Info(ChunkLoadClass &);
    virtual bool Read_Subobject(ChunkLoadClass &);
    virtual bool Read_Class_Info(ChunkLoadClass &);
private:
    unsigned m_Version;
    unsigned char m_SubobjectList[0x18];
    W3dAggregateInfoStruct m_Info;
};
bool AggregateDefClass::Read_Info(ChunkLoadClass &chunk_load)
{
    bool ret_val = false;
    ::memset(&m_Info, 0, sizeof(m_Info));
    if (chunk_load.Read(&m_Info, sizeof(m_Info)) == sizeof(m_Info)) {
        ret_val = true;
        for (unsigned isubobject = 0;
             isubobject < m_Info.SubobjectCount && ret_val == true;
             ++isubobject) {
            ret_val = Read_Subobject(chunk_load);
        }
    }
    return ret_val;
}
