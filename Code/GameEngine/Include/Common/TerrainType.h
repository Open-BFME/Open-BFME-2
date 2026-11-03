// Target facts (retail RVAs): newTerrain 0x0031816C pushes 0x30 at 0x0031817F to global new 0x0002FDA0, calls constructor 0x00317F6F at 0x00318194, and retains the object in its list at 0x003181E9. Constructor 0x00317F86 and destructor 0x00318001 both store table 0x0080C66C (VA 0x00C0C66C) at +0. Its sole slot is deleting destructor 0x00318150, which calls destructor 0x00317FF0 and global delete 0x0002FD60; the following word starts "DefaultTerrain". There is no base constructor, base cleanup or additional virtual slot in these bodies; TerrainType has its own virtual destructor and sizeof 0x30.
// Target facts: constructor 0x00317F6F, assignment 0x0031804D and destructor 0x00317FF0 establish AsciiStrings at +4/+8, bytes at +0x0C/+0x1C, a next pointer at +0x20, and 12-byte vector storage at +0x10/+0x24. Both vector headers use folded constructor 0x00211E58; assignment calls 0x0021C21B and 0x00317EBB, and destruction calls 0x00317E7C for +0x24. Parser 0x00318242 appends name/real records to +0x24; these vector fields retain neutral storage names because their native C++ element identities are unsettled. Getters 0x000AF1DD/0x000AF1F8 read +8, friend_setName 0x00317C34 writes +4, and newTerrain calls assignment/setName at 0x003181C1/0x003181D7, so these methods remain out of line.
// Target facts: FieldParse table 0x0080C3A8 names Texture (+8), BlendEdges (+0x0C), Class (+0x10), RestrictConstruction (+0x1C) and TerrainObject (parser 0x00318242); parseTerrainDefinition 0x00200A65 passes that table. Zero Hour Common/TerrainTypes.h supplies the names m_name, m_texture, m_blendEdgeTexture, m_restrictConstruction, m_next and getFieldParse. Its MemoryPoolObject inheritance is not retained: retail allocates and deletes this object through the global operators and installs only its own table.

#pragma once

#ifndef BFME2_TERRAIN_TYPE_H
#define BFME2_TERRAIN_TYPE_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

struct FieldParse;

class TerrainType
{
public:
    TerrainType();
    virtual ~TerrainType();
    TerrainType &operator=(const TerrainType &that);

    AsciiString getTexture() const;
    AsciiString getNrmTexture() const;
    void friend_setName(AsciiString name);
    const FieldParse *getFieldParse() { return m_terrainTypeFieldParseTable; }

    static const FieldParse m_terrainTypeFieldParseTable[];

    AsciiString m_name; // +0x04
    AsciiString m_texture; // +0x08
    bool m_blendEdgeTexture; // +0x0C
    unsigned int field10[3]; // +0x10
    bool m_restrictConstruction; // +0x1C
    TerrainType *m_next; // +0x20
    unsigned int field24[3]; // +0x24
};

#endif
