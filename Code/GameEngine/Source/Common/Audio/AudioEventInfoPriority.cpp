// cl: /O1 /G7 /MD /DNDEBUG
// The base audio priority setter at 0x0041FDEE takes a 32-bit enum, not Real.
// Identity: DynamicAudioEventInfo::xferNoName 0x004331C6 transfers a byte,
// zero-extends it and calls here; the priority INI path 0x00433A64 also passes
// Dict::getInt. The derived override at 0x004334AF sets bit 7 then forwards.
// Native bytes witness AudioEventInfo+0x44. ZH AudioEventInfo.h supplies the
// AudioPriority enum and DynamicAudioEventInfo.cpp the override semantics.
// BFME1 donor ba7ddda7 DynamicAudioEventInfo.cpp independently has the same
// no-name transfer and enum forwarder. Base setter spelling is unknown.
// The former LineGroupClass float alias was a different ABI and was not
// the relocation-free 14-byte real LineGroup setter at 0x00179010.
enum AudioPriority { AP_LOWEST, AP_LOW, AP_NORMAL, AP_HIGH, AP_CRITICAL };
class AudioEventInfo
{
public:
    void Rva0041FDEE(AudioPriority value);
private:
    unsigned char m_pad00[0x44];
    AudioPriority m_priority;
};
void AudioEventInfo::Rva0041FDEE(AudioPriority value)
{
    m_priority = value;
}
