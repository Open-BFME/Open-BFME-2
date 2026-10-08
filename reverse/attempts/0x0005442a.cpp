// ?rva0005442A@MilesAudioManager@@QAE?AU?$_List_iterator@VPlayingAudioRef@@U?$_Nonconst_traits@VPlayingAudioRef@@@_STL@@@_STL@@HHH@Z
// partial score=0.99 date=2026-10-08
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Apply this body to the Miles unit; the include supplies its landed views.
#include "../../Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp"

// Local nullable owner from the third trial; its constructor failed to inline.
class NullablePlayingAudioCopy {
public:
    NullablePlayingAudioCopy(const PlayingAudioRef &other)
    {
        ::new (static_cast<void *>(m_storage)) Rva0036CA00Str(
            *reinterpret_cast<const Rva0036CA00Str *>(&other));
    }
    ~NullablePlayingAudioCopy()
    {
        if (value()->get())
            value()->~Rva0036CA00Str();
    }
    PlayingAudio *get() const { return value()->get(); }
    PlayingAudio *operator->() const { return get(); }
private:
    Rva0036CA00Str *value() const { return reinterpret_cast<Rva0036CA00Str *>(const_cast<unsigned int *>(m_storage)); }
    unsigned int m_storage[1];
};

// Native 0x5442A..0x544CB and WB 0x7917E0: prefer an unstacked
// matching music stream; retain the last stacked match when filter is zero.
PlayingAudioList::iterator MilesAudioManager::rva0005442A(int viewType, int musicSystem, int filter)
{
    PlayingAudioList::iterator found = m_playingStreams.end();
    for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        NullablePlayingAudioCopy playing(*it);
        if (!playing.get())
            continue;
        AudioEventRTS *event = playing->m_event.get();
        if (event->m_info->m_atB0 != 0)
            continue;
        if (event->m_viewType != viewType)
            continue;
        if (event->m_musicSystem != musicSystem)
            continue;
        if (playing->at44[0]) {
            if (!filter)
                found = it;
            continue;
        }
        return PlayingAudioList::iterator(static_cast<_STL::_List_node<PlayingAudioRef> *>(it._M_node));
    }
    return found;
}

