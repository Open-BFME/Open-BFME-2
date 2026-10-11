// ?processAmbientStreams@MilesAudioManager@@QAEXPAU?$_List_iterator@VPlayingAudioRef@@U?$_Nonconst_traits@VPlayingAudioRef@@@_STL@@@_STL@@@Z
// partial score=0.99 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// DELTA BANK for Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// (the home TU is >64KB so it cannot be banked whole). Apply to the home TU at
// master 7c58cd8cee and measure with explain_mismatch --source <home TU>:
// result 1922B vs retail 1921B, every instruction equal except the
// hasExpired cleanup preheader: retail `mov edi,eax; mov eax,[ebp-0x20]`
// (copy &events from the begin() load), ours `mov eax,[ebp-0x20];
// mov edi,[ebp-0x34]` (reload, +1 byte). ~30 cleanup-loop shapes tried
// (for/while/do-while, next temp, alias refs/pointers, end copies, float
// fade temps, real vector::erase, begin/front/[0]): none move it.
//
// What closed the rest (keep these):
//  * shift loops written as loops (WB 0x78BB80), not memcpy: cl turns them
//    into the two rep movsd retail has, which frees esi/edi and puts `this`
//    in ebx;
//  * if (volume >= minimum) { found...; if (!found) {...} if (!found) {...} }
//    per WB, and `for (i = 0; i < 2 && bestEvent[i] != eventEnd; ++i)`;
//  * the fade fraction 0x5117B DEFINED in this TU before the caller (body
//    below): cl's same-unit register/memory summary lets it keep the
//    playing stream's +0x44 flag in dl across the call (retail does). This
//    means the 0x5117B row (now in Code/GameEngine/Source/GameClient/
//    Rva0005117BFraction.cpp) must be rehomed here and that file dropped,
//    same pattern as Rva000515E4Less;
//  * name compare in loop 2 evaluates the event's info first (helper R);
//  * `void *owner = m_atB90;` before the A8D0B call, fadeTime - g_00DBA4FC,
//    erase through reinterpret_cast<OpaqueRefList::iterator &>(streams[i]).
//
// Layout edits needed in the home TU (byte-neutral):
//  AudioSettings: `char at7C[4]` -> `int m_at7C;`
//  BfmeStringTailRecord144: at10[0x90-0x10] -> at10[0x88-0x10], float m_at88,
//    bool m_at8C, char at8D[3]
//  Rva0051D93: add `Rva0051D93(const BfmeAudioEventPrefix136 &source);`
//    (rowed 0x51D62) plus `struct BfmeAudioEventPrefix136;`
//  MilesAudioManager: declare processAmbientStreams(PlayingAudioList::iterator *);
//    `char at694[4]` -> `unsigned int m_at694;`
//    `char at6A8[2]` -> `bool m_at6A8; char at6A9;`
//  m_at90 (+0x90) is the frame duration (ms) the fades step by.
// Then append everything below at the end of the TU.

// Native 5F2BB..5FA3C RET4; WorldBuilder callgraph names processAmbientStreams.
// The event's volume product getter, rowed at 0x002D94E4 under an
// address-derived owner.
class Rva002D94E4 {public:float rva002D94E4(void) const;};

// Ambient stream fade fraction (retail 0x0005117B, address-derived owner):
// 1 - fadeFrames / AudioSettings +0x78, clamped to [0, 1]. Its body has to
// be visible here: processAmbientStreams keeps a playing stream's +0x44
// flag in dl across the calls only because cl sees this callee touches
// neither edx nor memory (same as Rva000515E4Less and 0x5BD30 above).
class Rva0005117B {
public:
    float rva0005117B(float v);
private:
    char m_lead[0x10];
    AudioSettings *m_audioSettings;      // +0x10, MilesAudioManager's
};
float Rva0005117B::rva0005117B(float v)
{
    float f = 1.0f - v / (float)m_audioSettings->m_at78;
    if (f < 0.0f)
        v = 0.0f;
    else if (f > 1.0f)
        v = 1.0f;
    else
        v = f;
    return v;
}
struct AmbientInfoNameView {virtual void slot0();virtual const AsciiString &slot1();};
static __forceinline bool ambientSameName(AudioEventInfo *a, AudioEventInfo *b)
{
 const AsciiString &left=reinterpret_cast<AmbientInfoNameView*>(a)->slot1();
 const AsciiString &right=reinterpret_cast<AmbientInfoNameView*>(b)->slot1();
 return reinterpret_cast<const StringBase<char> &>(right).compare(reinterpret_cast<const StringBase<char> &>(left))==0;
}
static __forceinline bool ambientSameNameR(AudioEventInfo *b, AudioEventInfo *a)
{
 const AsciiString &left=reinterpret_cast<AmbientInfoNameView*>(a)->slot1();
 const AsciiString &right=reinterpret_cast<AmbientInfoNameView*>(b)->slot1();
 return reinterpret_cast<const StringBase<char> &>(right).compare(reinterpret_cast<const StringBase<char> &>(left))==0;
}
void MilesAudioManager::processAmbientStreams(PlayingAudioList::iterator *streams)
{
    unsigned int view = 1 << m_at678;
    if ((m_at690 & view) || (m_at694 & view) || !slot56(16))
        return;
    QueuedAudioEvents &events = m_queuedEvents[m_at678];
    QueuedAudioEvents::iterator eventEnd = events.end();
    PlayingAudioList::iterator streamEnd = m_playingStreams.end();
    float minimum = m_audioSettings->m_atB8;
    int fadeTime = m_audioSettings->m_at78;

    // Loudest queued markers not yet playing, and the loudest marker that
    // matches each playing stream.
    float bestVolume[2];
    QueuedAudioEvents::iterator bestEvent[2];
    float oldVolume[2];
    QueuedAudioEvents::iterator sameEvent[2];
    for (int init = 0; init < 2; ++init) {
        sameEvent[init] = eventEnd;
        oldVolume[init] = 0;
        bestEvent[init] = eventEnd;
        bestVolume[init] = minimum;
    }

    bool hasExpired = false;
    for (QueuedAudioEvents::iterator it = events.begin(); it != eventEnd; ++it) {
        BfmeStringTailRecord144 *event = it;
        float volume = rva00059AD0(event, 0);
        if (it->m_at8C) {
            it->m_at88 += m_at90;
            if (it->m_at88 >= fadeTime) {
                hasExpired = true;
                continue;
            }
            volume *= 1.0f - it->m_at88 / fadeTime;
        }
        if (volume >= minimum) {
            bool found = false;
            for (int i = 0; !found && i < 2; ++i) {
                if (streams[i] != streamEnd) {
                    PlayingAudioRef playing = *streams[i];
                    if (ambientSameName(event->m_info, playing->m_event->m_info)) {
                        found = true;
                        if (volume > oldVolume[i]) {
                            oldVolume[i] = volume;
                            sameEvent[i] = it;
                        }
                    }
                }
            }
            if (!found) {
            for (int i = 0; i < 2 && bestEvent[i] != eventEnd; ++i) {
                if (ambientSameNameR(bestEvent[i]->m_info, event->m_info)) {
                    if (volume > bestVolume[i]) {
                        for (int j = i; j < 1; ++j) {
                            bestEvent[j] = bestEvent[j + 1];
                            bestVolume[j] = bestVolume[j + 1];
                        }
                        bestEvent[1] = eventEnd;
                        bestVolume[1] = minimum;
                        break;
                    } else {
                        found = true;
                    }
                }
            }
            }
            if (!found) {
            for (int k = 0; k < 2; ++k) {
                if (volume > bestVolume[k]) {
                    for (int j = 1; j > k; --j) {
                        bestEvent[j] = bestEvent[j - 1];
                        bestVolume[j] = bestVolume[j - 1];
                    }
                    bestEvent[k] = it;
                    bestVolume[k] = volume;
                    break;
                }
            }
            }
        }
    }

    int used = 0;
    bool stop[2];
    for (int i = 0; i < 2; ++i) {
        if (streams[i] != streamEnd) {
            ++used;
            stop[i] = false;
        } else {
            stop[i] = true;
        }
    }

    int available = m_maxAmbientStreams - used;
    bool done = false;
    while (used > 0 && !done) {
        int weakest = -1;
        float low = 3.402823466e38f;
        for (int i = 0; i < 2; ++i) {
            if (stop[i])
                continue;
            float value = oldVolume[i];
            if (value > 0.0f && !(*streams[i])->m_at44)
                value += m_audioSettings->m_at7C * 0.01f;
            if (value < low) {
                low = value;
                weakest = i;
            }
        }
        if (weakest == -1)
            break;
        if (available < 0 || low < bestVolume[available]) {
            stop[weakest] = true;
            ++available;
            --used;
        } else {
            done = true;
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (streams[i] != streamEnd) {
            PlayingAudioRef playing = *streams[i];
            playing->m_at44 = stop[i];
            if (stop[i]) {
                playing->m_at30 += m_at90;
            } else {
                playing->m_at30 -= m_at90;
                if (playing->m_at30 < 0.0f) {
                    playing->m_at30 = 0;
                    playing->m_at45 = false;
                } else {
                    playing->m_at45 = true;
                }
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (streams[i] != streamEnd) {
            PlayingAudioRef playing = *streams[i];
            float volume = oldVolume[i];
            volume = reinterpret_cast<Rva002D94E4 *>(playing->m_event.get())->rva002D94E4() * volume;
            if (playing->m_at44)
                volume *= reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30);
            if (volume < minimum) {
                playing->m_status = 1;
                playing->m_event->m_at4C = true;
                reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(
                    reinterpret_cast<OpaqueRefList::iterator &>(streams[i]));
                streams[i] = streamEnd;
            } else {
                if (!playing->m_at44)
                    volume *= reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30);
                volume *= reinterpret_cast<GlobalVolumeData *>(m_volumeData[m_at678])->rva0005910F(playing->m_event.get());
                reinterpret_cast<Rva000A8AEE *>(&playing->m_at0C)->rva000A8AEE(volume);
                if (m_at6A8)
                    rva00052FA0(playing);
            }
        }
    }

    int candidate = 0;
    for (int slot = 0; available > 0 && candidate < 2 && bestEvent[candidate] != eventEnd && slot < 2; ++slot) {
        if (streams[slot] == streamEnd) {
            PlayingAudioRef playing = allocatePlayingAudio();
            playing->m_event.rva00053D26(reinterpret_cast<BfmePoolHolder88 *>(
                new Rva0051D93(*reinterpret_cast<const BfmeAudioEventPrefix136 *>(bestEvent[candidate]))));
            playing->m_event->m_ownerType = 6;
            reinterpret_cast<GameMessage *>(playing->m_event.get())->friend_setList(
                reinterpret_cast<GameMessageList *>(m_nextHandle++));
            playing->m_event->generatePlayInfo();
            playing->m_event->rva002D9ADC();
            reinterpret_cast<Weapon *>(playing->m_event.get())->setLeechRangeActive(false);
            AsciiString filename = playing->m_event->getFilename();
            void *owner = m_atB90;
            reinterpret_cast<Rva000A8D0B *>(&playing->m_at0C)->rva000A8D0B(owner, filename, 0);
            playing->m_type = 4;
            playing->m_at30 = fadeTime - g_00DBA4FC;
            if (m_atBEC & (1 << m_at678)) {
                playing->m_at30 = 0;
                playing->m_at45 = false;
            } else {
                playing->m_at45 = true;
            }
            rva0005DB6C(filename);
            float volume = reinterpret_cast<Rva0005117B *>(this)->rva0005117B(playing->m_at30) * bestVolume[candidate];
            volume *= reinterpret_cast<GlobalVolumeData *>(m_volumeData[m_at678])->rva0005910F(playing->m_event.get());
            volume *= reinterpret_cast<Rva002D94E4 *>(playing->m_event.get())->rva002D94E4();
            reinterpret_cast<Rva000A8AEE *>(&playing->m_at0C)->rva000A8AEE(volume);
            reinterpret_cast<Rva000A8AD8 *>(&playing->m_at0C)->rva000A8AD8(
                reinterpret_cast<Rva002D94DD *>(playing->m_event.get())->rva002D94DD());
            rva00052FA0(playing);
            playAndStoreStream(playing, 0);
            --available;
            ++candidate;
        }
    }

    if (hasExpired) {
        QueuedAudioEvents::iterator it = events.begin();
        while (it != eventEnd) {
            if (it->m_at88 >= fadeTime) {
                unmapPhysicalHandle(it->m_playingHandle);
                it = reinterpret_cast<QueuedAudioEvents::iterator>(
                    reinterpret_cast<Rva000554A9 *>(&events)->rva000554A9(it));
                eventEnd = events.end();
            } else {
                ++it;
            }
        }
    }
    m_atBEC &= ~(1 << m_at678);
}
