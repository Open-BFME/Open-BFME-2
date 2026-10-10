// ?xfer@MilesAudioManager@@UAEXPAVXfer@@@Z
// partial score=0.9928366762177651 date=2026-10-10
// NOT a verified ledger recovery: normal source/identity/link gates remain.
// Private proof froze root122aa9e90b over official5b5fa79e24 with BF1 donor575ba2b04743.
// Native boundary 0x0005E3E5..0x0005E959 (1396); WB7AA970 DoXfer supplies identity.
// Existing MilesAudioManager.cpp is the home; xfer overrides secondary Snapshot +0x0C.
// Whole private TU emits1396. Normal map gives1386/1396 equal bytes with three
// unresolved typed STL calls. Independently proving nine whole helper bodies
// and all relocation destinations leaves zero parent byte differences.
// Helper placements below are READ-ONLY leads, neither admitted rows nor pins.
// Before landing: claim each body; instantiate Save helpers in the existing
// no-EH stlport_vector_e8_allocate_copy.cpp with its actual O1/SSE/G7/MD flags.
// The EHsc Miles home emits the WRONG236B Save overflow; declare its push_back
// specialization out-of-line there, then verify the proper184B provider.
// Add genuine ICF rows only with normal --icf-owner and gen-alias proof.
// The existing58DC6 pin targets an UNROWED231B serializer, so linking is blocked
// until it is recovered. Eight additional bounded EH/optimization profiles leave
// the same two frame/result-home byte differences in that helper; no new lever.
// Its existing bank and independently logged47 lifetime forms should be reused.
// Home integration declarations/layout, all supported by native accesses:
// #include <limits>; XferVersion has two unsigned-char members; Xfer virtual
// slots3=isCRC,10=xferVersion,28=xferReal,31=xferInt retain their native offsets.
// Declare virtual MilesAudioManager::xfer(Xfer*) and GlobalVolumeData::rva0005CE7E(Xfer*).
// Full this+90 is a float, C00 a bool appended after existing BF8 eight-byte member.
// Dispatch declarations are existing50C61/50C79/50C91 owned AudioReceiver views.
// Existing rva5B256 takes an ignored int* third argument; native passes &version.
// Its verified body never dereferences that argument; no guessed value/ABI pin.
// std numeric_limits quiet_NaN emits existing native7BDA2C bits0x7FA00000.
// No new asm, naked bodies, address-named globals, pins, or Code edits were landed.
// Current class layouts are target-established; readable field purposes inferred
// from the native transfer order and corresponding WorldBuilder assertions.
// helper ??$_Construct@UAudioTriggerAreaSave@@U1@@_STL@@YAXPAUAudioTriggerAreaSave@@ABU1@@Z 0x60c9d9 23 owner-source=Code/Libraries/Source/WWVegas/WWLib/StlSweepW6Rva0060C9D9.cpp
// helper ?allocate@?$allocator@UAudioTriggerAreaSave@@@_STL@@QBEPAUAudioTriggerAreaSave@@IPBX@Z 0x523d6c 28 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_deque_e8_o1.cpp
// helper ??$__uninitialized_copy@PAUAudioTriggerAreaSave@@PAU1@@_STL@@YAPAUAudioTriggerAreaSave@@PAU1@00ABU__false_type@0@@Z 0x4c3121 38 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_vector_e8_o1.cpp
// helper ??$__uninitialized_fill_n@PAUAudioTriggerAreaSave@@IU1@@_STL@@YAPAUAudioTriggerAreaSave@@PAU1@IABU1@ABU__false_type@0@@Z 0x507958 37 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_vector_e8_o1.cpp
// helper ?_M_insert_overflow@?$vector@UAudioTriggerAreaSave@@V?$allocator@UAudioTriggerAreaSave@@@_STL@@@_STL@@IAEXPAUAudioTriggerAreaSave@@ABU3@ABU__false_type@2@I_N@Z 0x57c80 184 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_vector_e8_allocate_copy.cpp
// helper ?push_back@?$vector@UAudioTriggerAreaSave@@V?$allocator@UAudioTriggerAreaSave@@@_STL@@@_STL@@QAEXABUAudioTriggerAreaSave@@@Z 0x539a2e 55 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_vector_e8_allocate_copy.cpp
// helper ??0?$_List_base@VPlayingAudioRef@@V?$allocator@VPlayingAudioRef@@@_STL@@@_STL@@QAE@ABV?$allocator@VPlayingAudioRef@@@1@@Z 0x4ec36c 41 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_list_int_o1.cpp
// helper ?clear@?$_List_base@VPlayingAudioRef@@V?$allocator@VPlayingAudioRef@@@_STL@@@_STL@@QAEXXZ 0x54d27 51 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_list_opaqueref_erase.cpp
// helper ??1?$_List_base@VPlayingAudioRef@@V?$allocator@VPlayingAudioRef@@@_STL@@@_STL@@QAE@XZ 0x55548 23 owner-source=Code/Libraries/Source/WWVegas/WWLib/stlport_list_opaqueref_erase.cpp

// Native 5E3E5..5E959, WB7AA970 MilesAudioManager::DoXfer.
// Snapshot's established ZH spelling is xfer; the secondary receiver is +0x0C.
void MilesAudioManager::xfer(Xfer *transfer)
{
    if (transfer->isCRC()) return;
    MilesMutexGuard guard(&m_mutex, 0);
    if (transfer->isLoading()) {
        m_at6AC = true;
        *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x6B0) = 0;
    }
    XferVersion version;
    version.m_version = 1;
    version.m_currentVersion = 4;
    transfer->xferVersion(&version);
    int oldView = m_at678;
    Rva00050C61Dispatch(reinterpret_cast<AudioReceiver *>(transfer), &m_at678);
    if (oldView != m_at678) *reinterpret_cast<bool *>(reinterpret_cast<char *>(this) + 0x6A5) = true;
    Rva00050C79Dispatch(reinterpret_cast<AudioReceiver *>(transfer), &m_at690);
    transfer->xferBool(&m_at6A7);
    int view;
    for (view = 0; view < 3; ++view) {
        if (view == 2 && version.m_currentVersion >= 3 && !m_atC00) continue;
        Rva00050C91Dispatch(reinterpret_cast<AudioReceiver *>(transfer), &m_activeMusicSystem[view]);
        reinterpret_cast<GlobalVolumeData *>(m_volumeData[view])->rva0005CE7E(transfer);
        Rva00058DC6Xfer(transfer, &m_atA14[view]);
        if (version.m_currentVersion >= 4) XferAudioAffect(transfer, &m_at6B4[view]);
    }
    if (transfer->isLoading()) {
        m_savedTriggerAreas.clear();
        int count;
        transfer->xferInt(&count);
        while (count) {
            AudioTriggerAreaSave area;
            transfer->xferInt(&area.m_triggerID);
            transfer->xferReal(&area.m_level);
            m_savedTriggerAreas.push_back(area);
            --count;
        }
        m_at6AA = true;
    } else {
        int count = static_cast<int>(m_triggerAreas.size());
        transfer->xferInt(&count);
        for (_STL::vector<AudioTriggerArea>::iterator it = m_triggerAreas.begin(); it != m_triggerAreas.end(); ++it) {
            int triggerID = *reinterpret_cast<int *>(reinterpret_cast<char *>(it->m_trigger) + 0x44);
            transfer->xferInt(&triggerID);
            float level = it->m_level;
            transfer->xferReal(&level);
        }
    }
    transfer->xferInt(&m_atBE4);
    if (transfer->isLoading()) internalSetReverbRoomType(m_atBE4);
    if (version.m_currentVersion >= 2) transfer->xferUnsignedInt(reinterpret_cast<unsigned int *>(&m_at94));
    else m_at94 = -1;
    m_at90 = 0.0f;
    if (transfer->isLoading()) {
        m_cameraPos.x = _STL::numeric_limits<float>::quiet_NaN();
        m_cameraPos.y = _STL::numeric_limits<float>::quiet_NaN();
        m_cameraPos.z = _STL::numeric_limits<float>::quiet_NaN();
    }
    if (transfer->isLoading()) {
        int count;
        transfer->xferInt(&count);
        for (int index = 0; index < count; ++index) {
            PlayingAudioRef playing;
            rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
            startPendingMusicTracks();
        }
        for (view = 0; view < 3; ++view) {
            if (view == 2 && version.m_currentVersion >= 3 && !m_atC00) continue;
            for (int system = 0; system < 2; ++system) {
                MusicStack &stack = m_musicStack[view][system];
                int oldSize = static_cast<int>(stack.size());
                int count;
                transfer->xferInt(&count);
                for (int index = 0; index < count; ++index) {
                    PlayingAudioRef playing;
                    rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
                    if (playing.get() && static_cast<int>(stack.size()) == oldSize)
                        reinterpret_cast<Rva00058B90 *>(&stack)->rva00058B90(*reinterpret_cast<Rva0036CA00Str *>(&playing));
                    oldSize = static_cast<int>(stack.size());
                }
            }
        }
        for (view = 0; view < 3; ++view) {
            if (view == 2 && version.m_currentVersion >= 3 && !m_atC00) continue;
            reinterpret_cast<Rva000A8C9B *>(&m_playingMusic[view])->clear();
        }
        m_pendingFileText.clear();
        m_unknownFileNames.clear();
    } else {
        PlayingAudioList savedStreams;
        for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
            PlayingAudioRef &playing = *it;
            if (playing.get() && playing->m_event.get() &&
                (playing->m_event->getAudioEventInfo()->m_atB0 == 0 || playing->m_event->getAudioEventInfo()->m_atB0 == 1) &&
                (playing->m_event->m_viewType != 2 || m_atC00) && !playing->m_at44 &&
                !playing->m_event->at51[0]) savedStreams.push_back(playing);
        }
        int count = static_cast<int>(savedStreams.size());
        transfer->xferInt(&count);
        for (PlayingAudioList::iterator it = savedStreams.begin(); it != savedStreams.end(); ++it) {
            PlayingAudioRef &playing = *it;
            rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
        }
        for (view = 0; view < 3; ++view) {
            if (view == 2 && version.m_currentVersion >= 3 && !m_atC00) continue;
            for (int system = 0; system < 2; ++system) {
                MusicStack &stack = m_musicStack[view][system];
                int count = static_cast<int>(stack.size());
                transfer->xferInt(&count);
                for (MusicStack::iterator it = stack.begin(); it != stack.end(); ++it) {
                    PlayingAudioRef playing = *reinterpret_cast<PlayingAudioRef *>(&*it);
                    rva0005B256(transfer, playing, reinterpret_cast<int *>(&version));
                }
            }
        }
    }
    xferUnicodeStringVector(transfer, &m_pendingFileText);
    xferAsciiStringVector(transfer, &m_unknownFileNames);
}
