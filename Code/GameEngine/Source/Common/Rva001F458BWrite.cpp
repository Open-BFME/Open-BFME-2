// cl: /MD
// ?Rva001F458BWrite@@YAAAVFile@@AAV1@ABURva001F458BText@@@Z @0x001F458B 29B.
// File::write at vtable +0x10 with (start and finish-start) from ostringstream text.
// Donor BFME1 fx_particle_system_bulk.cpp writeStreamText via FileWriteShim.
// Callers at 0x001FB7B4 and 0x00564315 in writeINI bodies using str() text.
// Honest Rva name; /O1 for frameless esi-return idiom.
class File {
public:
    virtual ~File();
    virtual bool open(const char* n, int a = 0);
    virtual void close();
    virtual int read(void* b, int bsz);
    virtual int write(const void* b, int bsz);
};
struct Rva001F458BText {
    const char* m_start;
    const char* m_finish;
};
File& Rva001F458BWrite(File& file, const Rva001F458BText& text)
{
    file.write(text.m_start, (int)(text.m_finish - text.m_start));
    return file;
}
