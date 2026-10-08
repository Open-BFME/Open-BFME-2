#pragma once
#include "ascii_string.h"

// Clean donor layout: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Include/GameClient/Video.h. Field labels follow that donor.
// Native video insertion copies strings at +0/+4/+8 and data at +C/+10/+14/+18;
// its 122-byte copy constructor and 28-byte vector stride independently verify
// those offsets. The existing native destructor owns the pointer at +18.
// SubtitleManager's identity and the field labels remain donor interpretation;
// no claim about the pointee's complete layout is made here.
class SubtitleManager;
struct Video
{
    AsciiString m_filename;
    AsciiString m_internalName;
    AsciiString m_commentForWB;
    unsigned char m_hasSubtitles;
    float m_volume;
    unsigned char m_isDefault;
    SubtitleManager *m_subtitleManager;

    Video()
        : m_hasSubtitles(0), m_volume(1.0f), m_isDefault(0),
          m_subtitleManager(0)
    {
    }

    ~Video();

    __forceinline Video &operator=(const Video &other)
    {
        m_filename.setCopyInline(other.m_filename);
        m_internalName.setCopyInline(other.m_internalName);
        m_commentForWB.setCopyInline(other.m_commentForWB);
        m_hasSubtitles = other.m_hasSubtitles;
        m_volume = other.m_volume;
        m_isDefault = other.m_isDefault;
        m_subtitleManager = other.m_subtitleManager;
        return *this;
    }
};

typedef char BfmeVideoRecordWidth[(sizeof(Video) == 28) ? 1 : -1];
