// ?rva000520F4@GlobalVolumeData@MilesAudioManager@@QAE_NABVAudioEventInfoRef@@H@Z
// partial score=0.8 date=2026-10-07
// Address-derived method candidate for MilesAudioManager::GlobalVolumeData.
// Target tail view: the two dwords at AudioEventInfo +0xB8/+0xBC select a
// pair of the four dirty bytes for this slider and volume-base index.
struct Rva000520F4AudioInfoTail {
    char at00[0xB8];
    void *m_atB8;
    void *m_atBC;
};

bool MilesAudioManager::GlobalVolumeData::rva000520F4(
    const AudioEventInfoRef &eventInfo, int volumeBaseIndex)
{
    AudioEventInfo *info = eventInfo.get();
    Rva000520F4AudioInfoTail *tail =
        reinterpret_cast<Rva000520F4AudioInfoTail *>(info);
    void **pair = &tail->m_atB8;
    int pairOffset = 0;
    if (pair[0] == pair[1])
        pairOffset = 2;
    int slider = info->getVolumeSlider();
    unsigned char *dirty = m_dirty[slider][volumeBaseIndex] + pairOffset;
    if (dirty[0] != 0)
        return true;
    return dirty[1] != 0;
}
