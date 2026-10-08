// ?rva0005AEDD@MilesAudioManager@@QAEXHPAV?$vector@URva0005A084Element@@V?$allocator@URva0005A084Element@@@_STL@@@_STL@@@Z
// partial score=0.95 date=2026-10-08
// Excerpt for MilesAudioManager.cpp (cl flags of that file). Add to the class:
//   void rva0005AE2B(int type, Rva0005A084Vector *output); void rva0005AEDD(...);
//   AudioEventInfoHash &audioEventInfos() { return *reinterpret_cast<AudioEventInfoHash *>(&m_allAudioEventInfo); }
// typedef _STL::hash_map<AsciiString, AudioEventInfo *, rts::hash<AsciiString>, rts::equal_to<AsciiString> > AudioEventInfoHash;
// OpaqueRefCounted gains bool rva00050EFA(); AudioEventInfoRef gains AudioEventInfoRef(const AudioEventInfo *) (ICF 0x51914).
// All bytes match except REL32: hash_map::begin is emitted out of line (16B, retail calls hashtable::begin 0x427195
// directly) and the iterator ++ instantiates a 50B _M_skip_to_next (retail 0x3F7925 is 47B calling _M_bkt_num_key 0x223149 out of line).
// Retail 0x00051914 (rowed as AudioEventInfoRef's constructor in
// AudioEventInfoRefConstructor.cpp): a counted reference to an event info.
AudioEventInfoRef::AudioEventInfoRef(const AudioEventInfo *info)
    : m_ptr(reinterpret_cast<OpaqueRefCounted *>(const_cast<AudioEventInfo *>(info)))
{
    if (m_ptr)
        m_ptr->Add_Ref();
}

class Rva001D98BD { public: bool rva001D98BD(int type); };

// Native 0005AE2B..0005AEDD, RET8. Under the +0x9D4 mutex, appends a
// counted reference to every event info whose +0xB0 type is type and that
// the try-add-ref 0x00050EFA still holds; that extra reference is dropped
// once the info is queued.
void MilesAudioManager::rva0005AE2B(int type, Rva0005A084Vector *output)
{
    MilesMutexGuard guard(&m_mutex, 0);
    AudioEventInfoHash::iterator it;
    for (it = audioEventInfos().begin(); it != audioEventInfos().end(); ++it) {
        AudioEventInfo *info = it->second;
        OpaqueRefCounted *counted = reinterpret_cast<OpaqueRefCounted *>(info);
        if (info->m_atB0 == type && counted->rva00050EFA()) {
            output->push_back(*reinterpret_cast<const Rva0005A084Element *>(&AudioEventInfoRef(info)));
            counted->Release_Ref();
        }
    }
}

// Native 0005AEDD..0005AF92, RET8. As 0x5AE2B, with the type test made by
// the recursive 0x001D98BD (composite infos of type 5 test their children).
void MilesAudioManager::rva0005AEDD(int type, Rva0005A084Vector *output)
{
    MilesMutexGuard guard(&m_mutex, 0);
    AudioEventInfoHash::iterator it;
    for (it = audioEventInfos().begin(); it != audioEventInfos().end(); ++it) {
        AudioEventInfo *info = it->second;
        OpaqueRefCounted *counted = reinterpret_cast<OpaqueRefCounted *>(info);
        if (reinterpret_cast<Rva001D98BD *>(info)->rva001D98BD(type) && counted->rva00050EFA()) {
            output->push_back(*reinterpret_cast<const Rva0005A084Element *>(&AudioEventInfoRef(info)));
            counted->Release_Ref();
        }
    }
}

