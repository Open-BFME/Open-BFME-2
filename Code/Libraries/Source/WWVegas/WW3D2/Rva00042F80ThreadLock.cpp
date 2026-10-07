// cl: /O2 /G6 /DNDEBUG /MD /EHsc
// Complete 12B body 42F80..42F8C invokes the independently rowed
// BFME_DX8_Thread_Lock 11F520 and returns the unchanged receiver.
// The original wrapper owner/name and constructor role are unproven.
void BFME_DX8_Thread_Lock();
struct Rva00042F80LockReceiver {
    Rva00042F80LockReceiver &enter();
};
Rva00042F80LockReceiver &Rva00042F80LockReceiver::enter() {
    BFME_DX8_Thread_Lock();
    return *this;
}
