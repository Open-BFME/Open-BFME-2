// cl: /G7 /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Native 0x004334AF/12: the dynamic audio priority override sets bit 7
// at +0xC4 then forwards its AudioPriority enum to the base setter +0x44.
// Caller 0x00433A64 passes Dict::getInt. ZH DynamicAudioEventInfo.cpp and
// BFME1 ba7ddda7 supply the same override purpose. This corrects the old
// float LineGroupClass view; source spelling of this physical owner is unknown.
enum AudioPriority { AP_LOWEST, AP_LOW, AP_NORMAL, AP_HIGH, AP_CRITICAL };
class AudioEventInfo
{
public:
    void Rva0041FDEE(AudioPriority value);
private:
    unsigned char m_pad00[0x44];
    AudioPriority m_priority;
};
class Rva004334AF
{
public:
    void rva004334AF(AudioPriority value);
private:
    AudioEventInfo m_info;
    unsigned char m_pad48[0xC4-0x48];
    unsigned char m_overridden;
};
void Rva004334AF::rva004334AF(AudioPriority value)
{
    m_overridden |= 0x80;
    m_info.Rva0041FDEE(value);
}
