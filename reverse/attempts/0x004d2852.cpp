// ?processFileProgress@ConnectionManager@@AAEXPAVNetFileProgressCommandMsg@@@Z
// partial score=0.88 date=2026-10-07
// Clean C++ near miss for ConnectionManager::processFileProgress.
// Supporting Rva004D5767WordField and Rva004D2C8EConnectionManagerLayout
// declarations are present in the committed ConnectionManager.cpp.
#pragma optimize("s", on)
void ConnectionManager::processFileProgress(NetFileProgressCommandMsg *msg)
{
    Int oldProgress = ((Rva004D2C8EConnectionManagerLayout *)this)->s_fileProgressMap[msg->getPlayerID()][((Rva004D5767WordField *)msg)->get()];
    const Int &progress = ((NetWrapperCommandMsg *)msg)->getDataLength();
    Int fileID = ((Rva004D5767WordField *)msg)->get();
    const Int &newProgress = oldProgress > progress ? oldProgress : progress;
    ((Rva004D2C8EConnectionManagerLayout *)this)->s_fileProgressMap[msg->getPlayerID()][fileID] = newProgress;
}
#pragma optimize("", on)
