// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include /O1 /G7 /arch:SSE /EHsc /MD
// Native 0x00053A1F..0x00053AFA (219B), RET4. The scaled-volume worker
// 0x00059AD0 passes its event here; the position provider and distance-length
// calls independently identify this as distance attenuation. The original
// method name is unknown, so retain the caller's existing void-pointer ABI.
// Target accesses establish event info +8, type bit8 at info+48, limits at
// info+94/+98, settings +10, and microphone coordinates +18/+1C/+20.
// These field-view names describe those accesses, not recovered declarations.
// The shared event prefix supplies the proven position-return ABI.
#include "Lib/Coord3D.h"
#include "Common/BfmeAudioEventPrefix136.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct AudioDistanceSettings {
    char pad00[0x70];
    int m_at70, m_at74;
};

struct AudioDistanceInfo {
    char pad00[0x48];
    unsigned m_type;
    char pad4C[0x94 - 0x4C];
    float m_at94, m_at98;
};

struct AudioDistanceEvent {
    char pad00[8];
    const AudioDistanceInfo *m_info;
};

struct AudioDistanceDelta {
    // Retain retail's flag-test, three loads, three subtractions, three stores.
    // Snapshot the listener coordinates before writing the result; the local
    // read view and compiler fences emit no extra instructions. Stores in Z/Y/X
    // source order become X/Y/Z when MSVC hoists the two branches' common work.
    static __forceinline void subtract(Coord3D &delta, const volatile Coord3D &listener,
                                      const BfmeEventPositionView &pos) {
        _ReadWriteBarrier();
        float dx = listener.x - pos.x;
        float dy = listener.y - pos.y;
        float dz = listener.z - pos.z;
        _ReadWriteBarrier();
        delta.z = dz;
        delta.y = dy;
        delta.x = dx;
    }
};

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

float MilesAudioManager::rva00053A1F(void *rawEvent)
{
    AudioDistanceEvent *event = (AudioDistanceEvent *)rawEvent;
    bool valid;
    BfmeEventPositionView pos = reinterpret_cast<BfmeAudioEventPrefix136 *>(event)->rva002DA1CC(valid);
    if (valid) {
        const AudioDistanceInfo *info = event->m_info;
        const volatile Coord3D &listener = m_listenerPosition;
        Coord3D delta;
        float nearDistance, farDistance;
        if (info->m_type & 8) {
            AudioDistanceDelta::subtract(delta, listener, pos);
            nearDistance = (float)((AudioDistanceSettings *)m_audioSettings)->m_at70;
            farDistance = (float)((AudioDistanceSettings *)m_audioSettings)->m_at74;
        } else {
            AudioDistanceDelta::subtract(delta, listener, pos);
            nearDistance = info->m_at94;
            farDistance = info->m_at98;
        }
        float length = delta.length();
        if (!(length >= farDistance)) {
            if (length > nearDistance && farDistance > nearDistance)
                return (farDistance - length) / (farDistance - nearDistance);
            return 1.0f;
        }
    }
    return 0.0f;
}
