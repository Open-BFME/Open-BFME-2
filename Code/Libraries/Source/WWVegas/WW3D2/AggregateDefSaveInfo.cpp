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
// AggregateDefClass::Save_Info, ported from BFME1 donor revision
// 5cae4bdffcc0fb2dd6f0a2a6c1a7328bd0fb0cfc,
// game/Libraries/Source/WWVegas/WW3D2/agg_def.cpp.
// Target vtable VA 0x00BD6C70 slot +0x20 names retail RVA 0x001A3960.
// Target independently confirms chunk 0x602, info +0x20 (36 bytes), vector
// pointer +0x0C, signed count +0x18, bool status and Save_Subobject slot +0x24.
// The ret 4 ends at RVA 0x001A39C5, followed by eleven padding int3 bytes.
// Vector/member names and the save-loop algorithm are carried from the donor.
// The local storage view expands the donor's inline Count/operator[] accessors;
// it claims only the target-confirmed vector pointer and active-count offsets.
class ChunkLoadClass;
class ChunkSaveClass {
public:
    bool Begin_Chunk(unsigned long);
    unsigned long Write(const void *, unsigned long);
    bool End_Chunk();
};
struct W3dAggregateSubobjectStruct;
struct W3dAggregateInfoStruct {
    char BaseModelName[32];
    unsigned SubobjectCount;
};
struct AggregateSubobjectListView {
    void *VTable;
    W3dAggregateSubobjectStruct **Vector;
    int VectorMax;
    bool IsValid;
    bool IsAllocated;
    int ActiveCount;
    int GrowthStep;
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
    virtual bool Save_Header(ChunkSaveClass &);
    virtual bool Save_Info(ChunkSaveClass &);
    virtual bool Save_Subobject(ChunkSaveClass &, W3dAggregateSubobjectStruct *);
private:
    unsigned m_Version;
    AggregateSubobjectListView m_SubobjectList;
    W3dAggregateInfoStruct m_Info;
};
bool AggregateDefClass::Save_Info(ChunkSaveClass &chunk_save)
{
    bool ret_val = false;
    if (chunk_save.Begin_Chunk(0x602) == true) {
        if (chunk_save.Write(&m_Info, sizeof(m_Info)) == sizeof(m_Info)) {
            ret_val = true;
            for (int isubobject = 0;
                 isubobject < m_SubobjectList.ActiveCount && ret_val == true;
                 ++isubobject) {
                ret_val = Save_Subobject(chunk_save, m_SubobjectList.Vector[isubobject]);
            }
        }
        chunk_save.End_Chunk();
    }
    return ret_val;
}
