/* Target facts (code addresses are RVAs): AudioFileCache has no virtual functions or vftable in BFME2. Constructor 0x000A8531 and nonvirtual destructor 0x000A7CF3 store no vptr; scalar deleting destructor 0x000510CF calls 0x000A7CF3 directly. Allocation 0x0005D3DA pushes 0x54 to operator new at 0x0005D3E3 and calls 0x000A8531 at 0x0005D3FD. No engine base is evidenced; the constructor calls a nonpolymorphic hash constructor 0x000A7E7A at +0, whose specialization is not established by its folded ledger name.
   Target layout: constructor 0x000A8550..0x000A8565 constructs three four-byte lists at +0x14; 0x000A8571 constructs the 0x0C-byte tree at +0x20 and 0x000A857D the failed-name set at +0x2C. Destructor 0x000A7D68 tests the hash count +0x10 and tears down +0x44, +0x2C, +0x20, the lists and the hash at 0x000A7D7A..0x000A7DBA. Constructor stores at 0x000A8589..0x000A85A1 establish four-byte counters +0x38/+0x3C/+0x40, thread +0x48, byte flag +0x4C and mutex +0x50. Shutdown 0x000A77B6..0x000A77D3 reads/clears +0x48 and sets +0x4C; 0x0010ECCA reads the owner's +0x50. Event request 0x000A825F/0x000A827F copies the four-byte owned reference at +0x44 through 0x000A89C9. Opaque member groups preserve storage without claiming unknown container specializations or reference identities.
   Target declarations: constructor 0x000A8531, destructor 0x000A7CF3, shutdown 0x000A77B3, eraseFromUnusedList 0x000A7E9E, deleteOpenAudioFile 0x000A80A8, rva000A8127 0x000A8127, freeUnusedSamples 0x000A81BE, requestFile by name 0x000A7EFA and by event 0x000A8241, readAudioFile 0x000A82CA and loader 0x000A8437 retain their ledger spellings and out-of-line calls. Donor fact: Zero Hour's MilesAudioManager.h names m_mutex; retail 0x0010ECD0 passes the +0x50 pointer to MilesMutexGuard. */
#pragma once

class AsciiString;
class BfmePoolRef10;
class OpenAudioFile;
class Rva00690FF0Handle;
struct Rva000A7E9EInput;
struct Rva000A80A8Item;

class AudioFileCache
{
public:
    AudioFileCache(void *mutex);
    ~AudioFileCache();

    void rva000A77B3();
    void eraseFromUnusedList(const Rva000A7E9EInput &);
    void deleteOpenAudioFile(Rva000A80A8Item *, int);
    void rva000A8127(Rva000A80A8Item *);
    void freeUnusedSamples();
    Rva00690FF0Handle requestFile(const AsciiString &, int);
    Rva00690FF0Handle requestFile(const BfmePoolRef10 &, int);
    void readAudioFile(OpenAudioFile *);
    unsigned long rva000A8437();

    unsigned char field00[0x10];
    unsigned int field10;
    unsigned char field14[0x0C];
    unsigned char field20[0x0C];
    unsigned char field2C[0x0C];
    unsigned int field38;
    unsigned int field3C;
    unsigned int field40;
    void *field44;
    void *field48;
    bool field4C;
    void *m_mutex;
};

typedef char AudioFileCacheSizeCheck[sizeof(AudioFileCache) == 0x54 ? 1 : -1];
