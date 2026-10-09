// ?rva0005FA3C@MilesAudioManager@@QAEXI@Z
// partial score=0.895969955969956 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/GameEngineDevice/Source/MilesAudioDevice
// stlport
// Replay against the matched owner TU for its proven declarations and callees.
#include "MilesAudioManager.cpp"
struct QueuedStopEvent {char at00[0x8C];bool m_at8C;};
// Native5FA3C..5FDC8 RET4; BF1 f989 rva006AFD00 is the primary clean
// stop-chain donor. BFME2 adds the independently measured +80 stop holds
// and queued-event +8C expiry request; all state collections are owned.
void MilesAudioManager::rva0005FA3C(unsigned int handle)
{
 if(handle<5)return;
 for(PlayingAudioList::iterator it=m_playingStreams.begin();it!=m_playingStreams.end();++it) {
  PlayingAudioRef audio=*it;
  if(!audio.get())continue;
  if(audio->m_event->m_playingHandle==handle) {
   --audio->m_event->m_at80;
   if(audio->m_event->m_at80<=0) {
    audio->m_event->m_at4C=true;
    if(!(audio->m_event->m_info->m_control&0x10))processAudioCompletion(audio);
    break;
   }
   return;
  }
 }
 for(PlayingAudioList::iterator it=m_playingSounds.begin();it!=m_playingSounds.end();++it) {
  PlayingAudioRef audio=*it;
  if(!audio.get())continue;
  if(audio->m_event->m_playingHandle==handle) {
   --audio->m_event->m_at80;
   if(audio->m_event->m_at80>0)return;
   audio->m_event->m_at4C=true;
   break;
  }
 }
 for(PlayingAudioList::iterator it=m_playing3DSounds.begin();it!=m_playing3DSounds.end();++it) {
  PlayingAudioRef audio=*it;
  if(!audio.get())continue;
  if(audio->m_event->m_playingHandle==handle) {
   --audio->m_event->m_at80;
   if(audio->m_event->m_at80>0)return;
   audio->m_event->m_at4C=true;
   break;
  }
 }
 for(int i=0;i<3;++i) {
  for(QueuedAudioEvents::iterator it=m_queuedEvents[i].begin();it!=m_queuedEvents[i].end();++it) {
   if(it->m_playingHandle==handle) {
    AudioEventRTS *event=reinterpret_cast<AudioEventRTS *>(it);
    if(--event->m_at80>0)return;
    reinterpret_cast<QueuedStopEvent *>(event)->m_at8C=true;
    break;
   }
  }
  if(m_playingMusic[i].get()&&m_playingMusic[i]->m_event->m_playingHandle==handle) {
   --m_playingMusic[i]->m_event->m_at80;
   if(m_playingMusic[i]->m_event->m_at80>0)return;
   reinterpret_cast<Rva000A8C9B *>(&m_playingMusic[i])->clear();
  }
  for(int j=0;j<2;++j) {
   MusicStack &stack=m_musicStack[i][j];
   for(MusicStack::iterator it=stack.begin();it!=stack.end();++it) {
    PlayingAudioRef &audio=reinterpret_cast<PlayingAudioRef &>(*it);
    if(audio.get()&&audio->m_event->m_playingHandle==handle) {
     --audio->m_event->m_at80;
     if(audio->m_event->m_at80>0)return;
     stack.erase(it);break;
    }
   }
  }
 }
 {
  Rva00054EBETable::iterator found=reinterpret_cast<Rva00055951 &>(m_requestSet).rva00055951(handle);
  if(found._M_cur) {
   Rva00051107AudioRequest *request=*reinterpret_cast<Rva00051107AudioRequestSet::iterator &>(found);
   --request->m_pendingEvent->m_at80;
   if(request->m_pendingEvent->m_at80>0)return;
   Rva00054EBETable::iterator copy=found;
   reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(reinterpret_cast<Rva00051B89KeyedSet::iterator &>(copy));
   deleteAudioRequest(request);
  }
 }
 for(Rva00051107AudioRequestList::iterator it=m_audioRequests.begin();it!=m_audioRequests.end();) {
  Rva00051107AudioRequest *request=*it;
  if(request&&request->m_request==0) {
   bool matches;
   if(request->m_pendingEvent.get())matches=request->m_pendingEvent->m_playingHandle==handle;
   else matches=request->m_at08==handle;
   if(matches) {
    if(request->m_pendingEvent.get())--request->m_pendingEvent->m_at80;
    if(request->m_pendingEvent.get()&&request->m_pendingEvent->m_at80>0)return;
    deleteAudioRequest(request);
    it=m_audioRequests.erase(it);continue;
   }
  }
  ++it;
 }
}
