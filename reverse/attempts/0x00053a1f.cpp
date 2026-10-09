// ?rva00053A1F@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z
// partial score=0.93 date=2026-10-09
// ?rva00053A1F@MilesAudioManager@@QAEMPAVAudioEventRTS@@@Z 0x53A1F 219B added lines (AudioSettings +0x70 int, class decl, BfmeAudioEventPrefix136 view for 0x2DA1CC, body)
#if 0
    char at6C[0x70 - 0x6C];
    int m_at70;                          // +0x70, near distance of global sounds (0x53A1F)
    int m_at74;                          // +0x74, far distance of global sounds (0x53A1F)
    float rva00053A1F(AudioEventRTS *event);
// Native owner position query (0x002DA1CC, rowed under the event prefix name).
class BfmeAudioEventPrefix136 { public: BfmeEventPositionView rva002DA1CC(bool &valid); };

// Retail 0x00053A1F (address-derived): linear distance falloff of an event
// from the Miles listener (+0x18): 0 when it has no position or lies at or past
// the far distance, 1 inside the near distance, else the linear ramp. Global
// infos (type bit 3) use the settings' +0x70/+0x74 distances.
float MilesAudioManager::rva00053A1F(AudioEventRTS *event)
{
    bool valid;
    BfmeEventPositionView pos = reinterpret_cast<BfmeAudioEventPrefix136 *>(event)->rva002DA1CC(valid);
    if (!valid)
        return 0.0f;
    const AudioEventInfo *info = event->getAudioEventInfo();
    bool global = (info->m_type & 8) != 0;
    Coord3D delta;
    delta.x = m_micPos.x - pos.x;
    delta.y = m_micPos.y - pos.y;
    delta.z = m_micPos.z - pos.z;
    float nearDistance;
    float farDistance;
    if (global) {
        nearDistance = (float)m_audioSettings->m_at70;
        farDistance = (float)m_audioSettings->m_at74;
    } else {
        nearDistance = info->m_maxDistance;
        farDistance = info->m_minDistance;
    }
    float length = delta.length();
    if (length >= farDistance)
        return 0.0f;
    if (length > nearDistance && farDistance > nearDistance)
        return (farDistance - length) / (farDistance - nearDistance);
    return 1.0f;
}

#endif
