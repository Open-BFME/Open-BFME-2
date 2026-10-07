// Native Ghidra 0x000520F4..0x0005213E, 74B, thiscall RET8.
// The AudioEventInfo tail pair and dirty-byte roles are measured views;
// their original field meanings remain unresolved.
class AudioEventInfo {
public:
    int getVolumeSlider();
    char reserved[0xb8];
    void *tail[2];
};
class AudioEventInfoRef {
public:
    AudioEventInfo *info;
};
class MilesAudioManager {
public:
    class GlobalVolumeData {
    public:
        unsigned char rva000520F4(const AudioEventInfoRef &, int);
        char reserved[0x1c4];
    };
};

unsigned char MilesAudioManager::GlobalVolumeData::rva000520F4(
    const AudioEventInfoRef &eventInfo, int volumeBaseIndex)
{
    AudioEventInfo *info = eventInfo.info;
    void **pair = info->tail;
    int pairOffset = 0;
    if (pair[0] == pair[1])
        pairOffset = 2;
    int slider = info->getVolumeSlider();
    int base = (volumeBaseIndex + slider * 2 + 0x62) * 4;
    const unsigned char *bytes = reinterpret_cast<const unsigned char *>(this);
    if (bytes[base + pairOffset] != 0)
        return true;
    return bytes[base + (pairOffset | 1)] != 0;
}
