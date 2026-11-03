/* Target facts (code addresses are RVAs; table addresses are VAs):
   0x002D6CDE stores 0x00C03354 at +0; 0x002D6D43 restores the same table.
   Its only slot is 0x002D72D5, the scalar deleting destructor, which calls
   0x002D6D43 and global delete 0x0002FD60. The next table, 0x00C03358,
   belongs to Anim2D (store 0x002D6D82), not an Anim2DTemplate base.
   0x002D7290 allocates 0x1C bytes before calling 0x002D6CDE at 0x002D72B8.
   The constructor writes next +4, AsciiString +8, images +0xC, frame count
   +0x10 (word), update delay +0x12 (word), mode +0x14 (dword, initially 3),
   and randomized-start +0x18 (byte). No base constructor or base cleanup occurs.
   0x002D72C0 and 0x002D6C81 prove the next link; 0x002D6AF5/0x002D6B2D
   prove the image array and unsigned frame count. 0x002D6D9B/0x002D6DB2/
   0x002D6DBC read randomized-start, frame count and unsigned update delay.
   0x000AF1DD returns the +8 name by value through StringBase's copy constructor.
   FieldParse table 0x00C031F0 binds parsers 0x002D72F1/0x002D73EC/0x002D7412
   and mode/delay/flag offsets 0x14/0x12/0x18; 0x002D75A3 passes that table.
   storeImage is rowed at 0x002D7355. All rowed methods remain declarations.
   Names and inline accessor semantics follow Zero Hour GeneralsMD Anim2D.h;
   the retail mode-name array is at 0x00DBCC84. */
#pragma once

#ifndef BFME2_ANIM2DTEMPLATE_H
#define BFME2_ANIM2DTEMPLATE_H

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Image;
class INI;
struct FieldParse;
enum Anim2DMode;

class Anim2DTemplate
{
    friend class INI;

public:
    Anim2DTemplate(AsciiString name);
    virtual ~Anim2DTemplate();

    AsciiString getName() const;
    const Image *getFrame(unsigned short frameNumber) const;
    unsigned short getNumFrames() const { return m_numFrames; }
    unsigned short getNumFramesBetweenUpdates() const { return m_framesBetweenUpdates; }
    Anim2DMode getAnimMode() const { return m_animMode; }
    bool isRandomizedStartFrame() const { return m_randomizeStartFrame; }
    void friend_setNextTemplate(Anim2DTemplate *animTemplate) { m_nextTemplate = animTemplate; }
    Anim2DTemplate *friend_getNextTemplate() const { return m_nextTemplate; }
    const FieldParse *getFieldParse() const { return s_anim2DFieldParseTable; }
    void storeImage(const Image *image);
    void allocateImages(unsigned short numFrames);

    Anim2DTemplate *m_nextTemplate;
    AsciiString m_name;
    const Image **m_images;
    unsigned short m_numFrames;
    unsigned short m_framesBetweenUpdates;
    Anim2DMode m_animMode;
    bool m_randomizeStartFrame;

protected:
    enum { NUM_FRAMES_INVALID = 0 };
    static void parseImage(INI *ini, void *instance, void *store, const void *userData);
    static void parseNumImages(INI *ini, void *instance, void *store, const void *userData);
    static void parseImageSequence(INI *ini, void *instance, void *store, const void *userData);
    static const FieldParse s_anim2DFieldParseTable[];
};

typedef char Anim2DTemplateSizeCheck[(sizeof(Anim2DTemplate) == 0x1C) ? 1 : -1];

#endif
