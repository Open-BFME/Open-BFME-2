// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1MemoryWriteFile@@UAE@XZ @0x0060237D 68B evidence: vtable VA 0x0087A7B8 at +0; delete[] at +0x14 via 0x0002FD80; StringBase char releaseBuffer at +0x24 via 0x00036410; base File dtor via 0x006025CE row; unblocks deleting dtor 0x006023F6

#include <new>

typedef void *FileHandle;

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


#include "../../../Include/Common/File.h"

class MemoryWriteFile : public File
{
public:
	virtual ~MemoryWriteFile();
	virtual bool open(const char *filename, int access);
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, seekMode mode);
	virtual void nextLine(char *buffer, int bytes);
	virtual bool scanInt(int &value);
	virtual bool scanReal(float &value);
	virtual bool scanString(AsciiString &value);
	virtual int size();
	virtual int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();
private:
	char *m_data;
	int m_size;
	int m_pos;
	int m_capacity;
	AsciiString m_name;
};

MemoryWriteFile::~MemoryWriteFile()
{
	delete[] m_data;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
