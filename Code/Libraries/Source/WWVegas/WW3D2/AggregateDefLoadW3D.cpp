// cl: /DNDEBUG /MD /EHsc
// AggregateDefClass::Load_W3D. BFME1 clean donor revision
// 5cae4bdffcc0fb2dd6f0a2a6c1a7328bd0fb0cfc, game/Libraries/Source/WWVegas/WW3D2/agg_def.cpp.
// Target vtable VA 0x00BD6C70 slot +4 identifies retail RVA 0x001A3350.
// Bool ABI and subordinate slots +0xC/+0x10/+0x18 are confirmed by target calls.
// Chunk constants and semantic names come from the reference; the 164-byte
// target extent includes its four-entry switch table at RVA 0x001A33E4.
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

struct W3dTextureReplacerHeaderStruct {
    unsigned ReplacedTexturesCount;
};

class ChunkLoadClass {
public:
    bool Open_Chunk();
    bool Close_Chunk();
    unsigned long Cur_Chunk_ID();
    unsigned long Read(void *, unsigned long);
};
class ChunkSaveClass;
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
};
bool AggregateDefClass::Load_W3D(ChunkLoadClass &chunk_load)
{
    W3dTextureReplacerHeaderStruct header = { 0 };
    while (chunk_load.Open_Chunk()) {
        bool error = true;
        switch (chunk_load.Cur_Chunk_ID()) {
        case 0x601: error = Read_Header(chunk_load); break;
        case 0x602: error = Read_Info(chunk_load); break;
        // The donor only uses this read result in WWDEBUG_SAY, elided by
        // the release configuration. Retail preserves the read itself.
        case 0x603: chunk_load.Read(&header, sizeof(header)); break;
        case 0x604: error = Read_Class_Info(chunk_load); break;
        }
        chunk_load.Close_Chunk();
        if (error != true) return error;
    }
    return true;
}
