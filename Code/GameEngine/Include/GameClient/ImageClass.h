// Target facts: Image's constructor RVA 0x002D8FE4 and destructor RVA 0x002D91CC both store VA 0x00C037B8 at +0; neither calls a base constructor or destructor. The table has one slot, VA 0x006D9262 (??_GImage), followed at VA 0x00C037BC by the string "Data". Image has a virtual destructor and no other virtual functions; it does not inherit Zero Hour's MemoryPoolObject.
// Target layout: allocations at RVA 0x0004E8C3 and 0x0057CE45 request 0x34 bytes before calling 0x002D8FE4. That constructor initializes strings at +4/+8, integer texture dimensions at +0x0C/+0x10, UV floats at +0x14/+0x18/+0x1C/+0x20 (0,0,1,1), integer image dimensions at +0x24/+0x28, a pointer at +0x2C and status at +0x30. RVA 0x001ED63C names the +4 string; 0x002D937E consumes the +8 filename. RVA 0x002D905E allocates a four-byte texture holder through +0x2C; 0x002D91CC releases its pointee and frees the holder, then releases strings +8/+4 through 0x00036410.
// Target methods: setUV 0x0004D701, setImageSize 0x0004D717, setStatus 0x002D8E63, clearStatus 0x002D8E72, parseImageCoords 0x002D8E83, parseImageStatus 0x002D8F86, bfmeSetTexture 0x002D905E and rva002D937E 0x002D937E are ledger names. The parsers read texture dimensions +0x0C/+0x10, store UVs +0x14 and dimensions +0x24/+0x28, and swap the latter for status bit 1. Zero Hour GeneralsMD GameClient/Image.h supplies the corresponding member and accessor names; BFME2's texture holder replaces its raw-data pointer. RVA 0x001ED63C uses the field table at VA 0x00C036E8.

#pragma once
#ifndef BFME2_IMAGECLASS_H
#define BFME2_IMAGECLASS_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"

class BfmeMapPictureTexture;
class INI;
struct FieldParse;
extern const FieldParse m_imageFieldParseTable[];

class Image
{
public:
    Image();
    virtual ~Image();

    void setName(const AsciiString &name) { m_name = name; }
    const AsciiString &getName() const { return m_name; }
    void setFilename(const AsciiString &filename) { m_filename = filename; }
    const AsciiString &getFilename() const { return m_filename; }
    void setUV(Region2D *uv) { if (uv) m_UVCoords = *uv; }
    const Region2D *getUV() const { return &m_UVCoords; }
    void setTextureWidth(int width) { m_textureSize.x = width; }
    void setTextureHeight(int height) { m_textureSize.y = height; }
    const ICoord2D *getTextureSize() const { return &m_textureSize; }
    void setImageSize(ICoord2D *size);
    const ICoord2D *getImageSize() const { return &m_imageSize; }
    int getImageWidth() const { return m_imageSize.x; }
    int getImageHeight() const { return m_imageSize.y; }
    unsigned int setStatus(unsigned int bit);
    unsigned int clearStatus(unsigned int bit);
    unsigned int getStatus() const { return m_status; }
    void bfmeSetTexture(const BfmeMapPictureTexture &texture);
    void rva002D937E();
    const FieldParse *getFieldParse() const { return m_imageFieldParseTable; }
    static void parseImageCoords(INI *ini, void *instance, void *store, const void *userData);
    static void parseImageStatus(INI *ini, void *instance, void *store, const void *userData);

    AsciiString m_name;
    AsciiString m_filename;
    ICoord2D m_textureSize;
    Region2D m_UVCoords;
    ICoord2D m_imageSize;
    BfmeMapPictureTexture *m_texture;
    unsigned int m_status;
};

#endif
