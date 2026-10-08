// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Trimmed from Open-BFME-1
// (Code/GameEngine/Source/Common/System/File.cpp): only the placed
// ?lock@File, ?close@File, ?open@File, ??1File, ?size@File, ?position@File,
// ?print@File, ?eof@File and ?unlock@File bodies are defined here, plus the
// MemoryReadFile read/seek/readEntireAndClose overrides (MemoryWriteFile's
// seek is the same ICF-folded body).
// Slots stay declared-only (destructor for the slot-0 delete-this dispatch,
// rest for layout) and the donor's other members stay out, so the
// unmatched-definition gate passes. Layout follows the donor: AsciiString is
// pointer-sized (+0x04), access +0x08, single-byte open/deleteOnClose flags,
// mutex handle +0x10; close is slot 2, open slot 1, lock slot 15, unlock
// slot 16. The member is a TU-local AsciiString whose inline set() reaches
// StringBase::set and whose forceinline dtor reaches the folded clear, so the
// open/close set calls and the destructor teardown stay direct. /O1: retail
// keeps its zero in ebx (cmp/mov bl + push ebx); default flags use immediates
// and drop a callee-saved save. Imports read straight out of retail: KERNEL32
// CreateMutexA + WaitForSingleObject + CloseHandle.

typedef void *FileHandle;

extern "C" __declspec(dllimport) FileHandle __stdcall CreateMutexA(void *attrs, int owned, const char *name);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(FileHandle handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(FileHandle handle);

typedef char *va_list;
#define va_start(ap, v) (ap = (va_list)&v + ((sizeof(v) + 3) & ~3))
#define va_end(ap) (ap = (va_list)0)
extern "C" __declspec(dllimport) int __cdecl vsprintf(char *buffer, const char *format, va_list args);
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
#pragma function(memcpy)
void *operator new[](unsigned int bytes);

static const unsigned long FILE_INFINITE = 0xFFFFFFFF;

#include "ascii_string.h"


class File
{
public:
	File();
	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close();
	enum seekMode { START, CURRENT, END };
	enum { TEXT = 0x20 };

	virtual int read(void *buffer, int bytes) = 0;
	virtual int write(const void *buffer, int bytes) = 0;
	virtual int seek(int bytes, seekMode mode) = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual bool print(const char *format, ...);
	virtual int size();
	virtual int position();
	virtual char *readEntireAndClose() = 0;
	virtual void slot14() = 0;
	virtual void lock();
	virtual void unlock();

	bool eof();

protected:
	void setName(const char *name)
	{
		m_nameStr.set(name);
	}

private:
	AsciiString m_nameStr;
	int m_access;
	unsigned char m_isOpen;
	unsigned char m_deleteOnClose;
	unsigned char m_pad0E[2];
	FileHandle m_mutex;
};

void File::lock()
{
	if (m_mutex == 0)
		m_mutex = CreateMutexA(0, 1, 0);
	else
		WaitForSingleObject(m_mutex, FILE_INFINITE);
}

// ?unlock@File@@UAEXXZ
// Slot 16 of File's vtable (0x0087A808) and of every subclass that inherits
// it. BFME1 File::unlock verbatim (matched there at 0x009CB790, same 15 bytes):
// a File that was never locked has no mutex, hence the test.
void File::unlock()
{
	if (m_mutex != 0)
		ReleaseMutex(m_mutex);
}

// ??0File@@QAE@XZ, retail 0x006024FD, 70 bytes. Stores File's own vtable
// 0x0087A808 (tools/vftable_map.py: open/close at slots 1-2, print/size/
// position at 10-12, lock/unlock at 15-16, __purecall elsewhere, which is why
// the slots this unit does not define are pure here), zeroes the name,
// access, both flags and the mutex handle, then names the file "<no file>"
// through the one-arg StringBase::set (0x000055F5) under an EH frame for the
// name's teardown. Zero Hour File::File, plus BFME's mutex. RAMFile's ctor
// (0x006054E7) calls it as its base. Previously rowed as ModuleData's ctor
// from that one call site; the vtable it stores is File's, not a ModuleData's.
File::File()
	: m_access(0), m_isOpen(0), m_deleteOnClose(0), m_mutex(0)
{
	setName("<no file>");
}

// ?size@File@@UAEHXZ
// Slot 11 of File's vtable, inherited by LocalFile, RAMFile and
// StreamingArchiveFile. ZH / BFME1 File::size verbatim (BFME1 0x009CB670, 53B).
int File::size()
{
	int pos = seek(0, CURRENT);
	int size = seek(0, END);

	seek(pos, START);

	return size < 0 ? 0 : size;
}

// ?position@File@@UAEHXZ
// Slot 12. ZH / BFME1 File::position verbatim (BFME1 0x009CB6B0, 10B).
int File::position()
{
	return seek(0, CURRENT);
}

// ?print@File@@UAA_NPBDZZ
// Slot 10, inherited by every File subclass here. ZH / BFME1 File::print
// (BFME1 0x009CB6C0): 10K stack buffer, TEXT-mode check, vsprintf through the
// msvcr71 import, then write through slot 4.
bool File::print(const char *format, ...)
{
	char buffer[10*1024];
	int len;

	if (!(m_access & TEXT))
	{
		return false;
	}

	va_list args;
	va_start(args, format);
	len = vsprintf(buffer, format, args);
	va_end(args);

	if (len >= sizeof(buffer))
	{
		return false;
	}

	return (write(buffer, len) == len);
}

// ?eof@File@@QAE_NXZ
// ZH / BFME1 File::eof verbatim (BFME1 0x009CB740, same 30 bytes): position
// through slot 12 first, then size through slot 11.
bool File::eof()
{
	return position() == size();
}

// ?close@File@@UAEXXZ
// BFME1 File::close shape (their setName ends with deleteInstance; ours clears
// m_deleteOnClose first and then deletes through vtable slot 0 with a separate
// operator delete -- a plain delete this, not MemoryPoolObject's
// getObjectMemoryPool/dtor/freeBlock sequence). Retail calls the one-arg
// StringBase::set, so setName is the one-arg form here, not the two-arg +
// strlen spelling BFME1 uses.
void File::close()
{
	if (m_isOpen) {
		setName("<no file>");
		m_isOpen = 0;
		if (m_deleteOnClose) {
			m_deleteOnClose = 0;
			::delete this;
		}
	}
}

// ?open@File@@UAE_NPBDH@Z
// BFME1 File::open logic (their setName is the two-arg + strlen form; ours is
// the one-arg form like close, so no length push). Access-flag numbering is
// unchanged from Zero Hour (READ 1, WRITE 2, APPEND 4, TRUNCATE 0x10,
// TEXT 0x20, BINARY 0x40, STREAMING 0x100).
bool File::open(const char *filename, int access)
{
	if (m_isOpen) {
		return false;
	}
	setName(filename);
	if ((access & (0x100 | 0x02)) == (0x100 | 0x02)) {
		return false;
	}
	if ((access & (0x20 | 0x40)) == (0x20 | 0x40)) {
		return false;
	}
	if ((access & (0x01 | 0x02)) == 0) {
		access |= 0x01;
	}
	if (!(access & (0x01 | 0x04))) {
		access |= 0x10;
	}
	if ((access & (0x20 | 0x40)) == 0) {
		access |= 0x40;
	}
	m_access = access;
	m_isOpen = 1;
	return true;
}

// ??1File@@UAE@XZ
// BFME1 File::~File verbatim: clears delete-on-close (so a self-deleting File
// does not re-enter delete while being destroyed), closes, then releases the
// mutex. The trailing AsciiString teardown (0x36410 via the forceinline member
// dtor) is implicit.
File::~File()
{
	m_deleteOnClose = 0;
	close();
	if (m_mutex) {
		CloseHandle(m_mutex);
	}
}

// BFME's in-memory File pair, from the Open-BFME-1 donor File.cpp (no Zero Hour
// counterpart). Vtables 0x0087A748 (MemoryReadFile: real read, stub write) and
// 0x0087A7B8 (MemoryWriteFile: stub read, real write); both inherit File's
// print/lock/unlock at slots 10/15/16 and share one seek body at slot 5. Layout
// as the donor proved it: data +0x14, size +0x18, position +0x1c.
class MemoryReadFile : public File
{
public:
	virtual int read(void *buffer, int bytes);
	virtual int seek(int bytes, seekMode mode);
	virtual char *readEntireAndClose();

private:
	char *m_data;
	int m_size;
	int m_pos;
};

class MemoryWriteFile : public File
{
public:
	virtual int seek(int bytes, seekMode mode);

private:
	char *m_data;
	int m_size;
	int m_pos;
	int m_capacity;
};

// ?read@MemoryReadFile@@UAEHPAXH@Z, retail 0x006020F0, 70 bytes: slot 3 of
// vtable 0x0087A748. BFME1 donor MemoryReadFile::read (matched there at
// 0x009CB090): the clamp is unsigned, hence cmova.
int MemoryReadFile::read(void *buffer, int bytes)
{
	if (bytes < 0)
	{
		return -1;
	}

	unsigned int remaining = (unsigned int)m_size - (unsigned int)m_pos;
	if ((unsigned int)bytes > remaining)
	{
		bytes = remaining;
	}

	if (bytes)
	{
		if (buffer)
		{
			memcpy(buffer, m_data + m_pos, bytes);
		}
	}
	m_pos += bytes;

	return bytes;
}

// ?seek@MemoryReadFile@@UAEHHW4seekMode@File@@@Z, retail 0x00602136, 49 bytes:
// slot 5 of both memory-file vtables. BFME1 donor MemoryReadFile::seek (its
// row spells the mode as Int, but an override of File::seek has to take
// seekMode, as every other seek row in this ledger does). Out of range is -1,
// not a clamp.
int MemoryReadFile::seek(int bytes, seekMode mode)
{
	int pos;

	switch (mode)
	{
		case START:
			pos = bytes;
			break;
		case CURRENT:
			pos = m_pos + bytes;
			break;
		case END:
			pos = m_size + bytes;
			break;
		default:
			return -1;
	}

	if ((unsigned int)pos > (unsigned int)m_size)
	{
		return -1;
	}

	m_pos = pos;
	return pos;
}

// ?seek@MemoryWriteFile@@UAEHHW4seekMode@File@@@Z: the donor's identical body,
// folded by /OPT:ICF into the same 0x00602136.
int MemoryWriteFile::seek(int bytes, seekMode mode)
{
	int pos;

	switch (mode)
	{
		case START:
			pos = bytes;
			break;
		case CURRENT:
			pos = m_pos + bytes;
			break;
		case END:
			pos = m_size + bytes;
			break;
		default:
			return -1;
	}

	if ((unsigned int)pos > (unsigned int)m_size)
	{
		return -1;
	}

	m_pos = pos;
	return pos;
}

// ?readEntireAndClose@MemoryReadFile@@UAEPADXZ, retail 0x00602167, 61 bytes:
// slot 13 of vtable 0x0087A748. BFME1 donor body (matched there at 0x009CB190):
// a copy of the whole block, and an empty file still hands back an allocation.
char *MemoryReadFile::readEntireAndClose()
{
	if (m_size == 0)
	{
		close();
		return new char[1];
	}

	char *buffer = new char[m_size];
	memcpy(buffer, m_data, m_size);
	close();
	return buffer;
}
