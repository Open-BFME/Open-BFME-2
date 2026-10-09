// ?recalculateMicrophone@MilesAudioManager@@QAEXXZ
// partial score=0.95 date=2026-10-09
// ?recalculateMicrophone@MilesAudioManager@@QAEXXZ 0x52B53 971B - body only; declarations (MicrophoneSettings +0x00..0x44, m_micPos/m_micDir/m_cameraPos, m_listener, slot105/106, Rva0005276C/Rva00051CA2/Rva00051CF1) are in MilesAudioManager.cpp
#if 0
// WorldBuilder twin MilesAudioManager::recalculateMicrophone (0x78A8C0):
// pulls the listener from the camera toward the ground, faces it along the
// camera's ground heading and scales +0x8C by the shortest corner edge.
void MilesAudioManager::recalculateMicrophone(void)
{
    const MicrophoneSettings *settings = &m_audioSettings->m_microphoneSettings[m_at678];
    m_at6AB = false;
    Coord3D cameraPos;
    cameraPos.x = 0.0f;
    cameraPos.y = 0.0f;
    cameraPos.z = 0.0f;
    slot105(&cameraPos);
    Rva0005276C corners;
    slot106(&corners);
    if (m_cameraPos == cameraPos && ((Rva00051CF1 *)m_corners)->rva00051CF1((Rva00051CF1 &)corners))
        return;
    *(Rva0005276C *)m_corners = corners;
    m_cameraPos = cameraPos;

    Coord3D lookDir;
    {
        const Coord3D *corner = &m_corners[0].m_pos;
        lookDir.x = cameraPos.x - corner->x;
        lookDir.y = cameraPos.y - corner->y;
        lookDir.z = cameraPos.z - corner->z;
    }
    float lengthSqr = lookDir.x * lookDir.x + lookDir.y * lookDir.y + lookDir.z * lookDir.z;
    float fraction;
    if (lengthSqr * settings->m_at04 >= settings->m_at14) {
        float dist = sqrtf(lengthSqr);
        fraction = settings->m_at10 / dist;
    } else if (lengthSqr <= settings->m_at0C)
        fraction = 1.0f;
    else if (lengthSqr * settings->m_at04 <= settings->m_at0C) {
        float dist = sqrtf(lengthSqr);
        fraction = settings->m_at08 / dist;
    } else
        fraction = settings->m_at00;

    {
        Coord3D scaled;
        scaled.x = lookDir.x * fraction;
        scaled.y = lookDir.y * fraction;
        scaled.z = lookDir.z * fraction;
        Coord3D mic;
        mic.x = cameraPos.x - scaled.x;
        mic.y = cameraPos.y - scaled.y;
        mic.z = cameraPos.z - scaled.z;
        if (m_corners[0].m_valid) {
            m_micPos.x = (m_corners[0].m_pos.x - mic.x) * settings->m_at18 + mic.x;
            m_micPos.y = (m_corners[0].m_pos.y - mic.y) * settings->m_at18 + mic.y;
            m_micPos.z = mic.z;
        } else {
            m_micPos = mic;
        }
    }
    if (lookDir.x != 0.0f || lookDir.y != 0.0f) {
        m_micDir.x = -lookDir.x;
        m_micDir.y = -lookDir.y;
        m_micDir.z = 0.0f;
        m_micDir.Normalize();
    }
    if (m_listener) {
        AIL_set_3D_orientation(m_listener, m_micDir.x, m_micDir.y, -m_micDir.z, 0.0f, 0.0f, -1.0f);
        AIL_set_3D_position(m_listener, m_micPos.x, m_micPos.y, -m_micPos.z);
    }

    {
        Coord3D delta;
        delta.x = cameraPos.x - m_micPos.x;
        delta.y = cameraPos.y - m_micPos.y;
        delta.z = cameraPos.z - m_micPos.z;
        reinterpret_cast<GlobalVolumeData *>(m_volumeData[m_at678])->rva0005213E(settings, &delta);
    }

    float shortest = g_Va00BBDA30;
    for (int i = 1; i < 5; ++i) {
        int next = i + 1;
        if (next == 5)
            next = 1;
        if (m_corners[i].m_valid && m_corners[next].m_valid) {
            const AudioAreaCorner &a = m_corners[i];
            const AudioAreaCorner &b = m_corners[next];
            float ex = a.m_pos.x - b.m_pos.x;
            float ey = a.m_pos.y - b.m_pos.y;
            float edgeSqr = ex * ex + ey * ey;
            if (shortest > edgeSqr)
                shortest = edgeSqr;
        }
    }
    if (shortest >= settings->m_at3C)
        m_at8C = 0.0f;
    else if (shortest <= settings->m_at44)
        m_at8C = 1.0f;
    else
    {
        float dist = sqrtf(shortest);
        m_at8C = (settings->m_at38 - dist) / (settings->m_at38 - settings->m_at40);
    }
}

#endif
