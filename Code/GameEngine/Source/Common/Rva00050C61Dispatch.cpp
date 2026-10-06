// cl: /MD
// ?Rva00050C61Dispatch@@YAXPAVAudioReceiver@@PAX@Z @0x00050C61 24B virtual slot +0x94 forward with "AudioViewType"; callers 0x0005E456; siblings 0x00050C79 0x00050C91.
// ?Rva00050C79Dispatch@@YAXPAVAudioReceiver@@PAX@Z @0x00050C79 24B virtual slot +0x94 forward with "AudioViewTypeBits"; callers 0x0005E473.
// ?Rva00050C91Dispatch@@YAXPAVAudioReceiver@@PAX@Z @0x00050C91 24B virtual slot +0x94 forward with "MusicSystem"; callers 0x0005E4AA.
class AudioReceiver
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
    virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6c();
    virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7c();
    virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8c();
    virtual void slot90();
    virtual void slot94(const char*, void*, int);
};
void Rva00050C61Dispatch(AudioReceiver* receiver, void* value)
{
    receiver->slot94("AudioViewType", value, 4);
}
void Rva00050C79Dispatch(AudioReceiver* receiver, void* value)
{
    receiver->slot94("AudioViewTypeBits", value, 4);
}
void Rva00050C91Dispatch(AudioReceiver* receiver, void* value)
{
    receiver->slot94("MusicSystem", value, 4);
}
