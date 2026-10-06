// cl: /DNDEBUG /MD /EHsc
// ?read@RAMFile@@UAEHPAXH@Z @ 0x00605564 (70B): slot 3 (offset 0xC) of vtable
// 0x0087AA00. ZH GameEngine RAMFile::read verbatim: null m_data returns -1,
// clamp to m_size-m_pos via cmovg, memcpy when bytes>0 and buffer set,
// advance m_pos. Contiguous with rowed RAMFile close 0x00605547 and RAMFile
// dtor 0x00605504. cmov needs /arch:SSE (no /G flag emits it). memcpy is a
// plain extern E8 to the rowed import thunk 0x006291A8.

#define NULL 0

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);
extern "C" __declspec(dllimport) int __cdecl isspace(int c);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);
extern "C" __declspec(dllimport) double __cdecl atof(const char *text);

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;

	StringBase() : m_data(0) {}
	void releaseBuffer();

public:
	void concat(const T *text, int length);
	void set(const StringBase<T> &other);	// rowed 0x000366F0
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() { releaseBuffer(); }

	void clear();
	// Inline, as retail expands it: openFromArchive calls StringBase<char>::set (0x000366F0)
	// directly, not the out-of-line copy at 0x00001733 (link census, 2026-10-06).
	AsciiString &operator=(const AsciiString &other) { set(other); return *this; }

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}

	const char *str() const
	{
		return m_data ? m_data->data : "";
	}
};

void *__cdecl operator new[](unsigned int s);
void __cdecl operator delete[](void *block);

class File
{
public:
	File();
	enum seekMode { START, CURRENT, END };

	virtual ~File();								// slot 0
	virtual bool open(const char *filename, int access = 0);	// slot 1
	virtual void close(void);						// slot 2
	virtual int read(void *buffer, int bytes);			// slot 3
	virtual int write(const void *buffer, int bytes);		// slot 4
	virtual int seek(int pos, seekMode mode);			// slot 5
	virtual void nextLine(char *buf, int bufSize);			// slot 6
	virtual bool scanInt(int &newInt);				// slot 7
	virtual bool scanReal(float &newReal);				// slot 8
	virtual bool scanString(AsciiString &newString);		// slot 9
	virtual bool print(const char *format, ...);			// slot 10
	virtual int size(void);						// slot 11
	virtual int position(void);					// slot 12
	virtual char *readEntireAndClose(void);				// slot 13
	virtual File *convertToRAMFile(void);				// slot 14
	virtual void lock(void);						// slot 15
	virtual void unlock(void);					// slot 16

	__forceinline const char *getName(void) const
	{
		const char *data = (const char *)m_nameStr;
		return data ? data + 8 : "";
	}

	__forceinline int getAccess(void) const
	{
		return m_access;
	}

protected:
	void *m_nameStr;	// +0x04 AsciiString untouched here
	int m_access;		// +0x08
	bool m_open;		// +0x0c
	bool m_deleteOnClose;	// +0x0d
	void *m_mutex;		// +0x10
};

class RAMFile : public File
{
public:
	RAMFile();
	virtual ~RAMFile();
	virtual void close(void);
	virtual int write(const void *buffer, int bytes);
	virtual bool open(const char *filename, int access);	// slot 1
	virtual bool open(File *file);				// slot 17
	virtual int read(void *buffer, int bytes);
	virtual int seek(int pos, seekMode mode);
	virtual void nextLine(char *buf, int bufSize);
	virtual bool scanInt(int &newInt);
	virtual bool scanReal(float &newReal);
	virtual bool scanString(AsciiString &newString);
	virtual char *readEntireAndClose(void);
	// ?RAMFile::convertToRAMFile present-unmatched
	virtual File *convertToRAMFile(void) { return this; }
	virtual bool openFromArchive(File *archiveFile, const AsciiString &filename, int offset, int size);
	virtual bool copyDataToFile(File *file);

protected:
	char *m_data;	// +0x14
	int m_pos;	// +0x18
	int m_size;	// +0x1c
};

// ??0RAMFile@@QAE@XZ, RVA 0x006054E7 (29 bytes). Table 0x0087AA00
// contains the verified RAMFile read/seek/close/scan methods; the constructor
// calls File 0x006024FD and clears data/position/size at +0x14/+0x18/+0x1C.
// The former DieModuleData spelling was refuted by this independent identity.
RAMFile::RAMFile() : m_data(0), m_pos(0), m_size(0)
{
}

int RAMFile::read(void *buffer, int bytes)
{
	if (m_data == NULL)
	{
		return -1;
	}

	int bytesLeft = m_size - m_pos;

	if (bytes > bytesLeft)
	{
		bytes = bytesLeft;
	}

	if ((bytes > 0) && (buffer != NULL))
	{
		memcpy(buffer, &m_data[m_pos], bytes);
	}

	m_pos += bytes;

	return bytes;
}

// ?nextLine@RAMFile@@UAEXPADH@Z @ 0x006055E7 (119B): slot 6 (offset 0x18) of
// vtable 0x0087AA00. ZH GameEngine RAMFile::nextLine verbatim: seek past
// newline with bounded buf copy, copy the newline itself, null-terminate,
// clamp m_pos to m_size. Contiguous with rowed read 0x00605564.
void RAMFile::nextLine(char *buf, int bufSize)
{
	int i = 0;
	// seek to the next new-line character
	while ((m_pos < m_size) && (m_data[m_pos] != '\n')) {
		if ((buf != NULL) && (i < (bufSize - 1))) {
			buf[i] = m_data[m_pos];
			++i;
		}
		++m_pos;
	}

	// we got to the new-line character, now go one past it.
	if (m_pos < m_size) {
		if ((buf != NULL) && (i < bufSize)) {
			buf[i] = m_data[m_pos];
			++i;
		}
		++m_pos;
	}
	if (buf != NULL) {
		if (i < bufSize) {
			buf[i] = 0;
		} else {
			buf[bufSize] = 0;
		}
	}
	if (m_pos >= m_size) {
		m_pos = m_size;
	}
}

// ?scanString@RAMFile@@UAE_NAAVAsciiString@@@Z @ 0x006056FA (128B): slot 9
// (offset 0x24) of vtable 0x0087AA00. ZH GameEngine RAMFile::scanString
// verbatim with BFME2 (temp,1) concat spelling like LocalFile::scanString.
bool RAMFile::scanString(AsciiString &newString)
{
	newString.clear();

	while ((m_pos < m_size) && isspace(m_data[m_pos])) {
		++m_pos;
	}

	if (m_pos >= m_size) {
		m_pos = m_size;
		return false;
	}

	do {
		char value[4];
		value[0] = m_data[m_pos];
		newString.concat(value, 1);
		++m_pos;
	} while ((m_pos < m_size) && (!isspace(m_data[m_pos])));

	return true;
}

// ?openFromArchive@RAMFile@@UAE_NPAVFile@@ABVAsciiString@@HH@Z @ 0x0060577A
// (146B): slot 18 (offset 0x48) of vtable 0x0087AA00. ZH GameEngine
// RAMFile::openFromArchive verbatim (no RefPack decode in BFME2 retail).
bool RAMFile::openFromArchive(File *archiveFile, const AsciiString &filename, int offset, int size)
{
	if (archiveFile == NULL) {
		return false;
	}

	if (File::open(filename.str(), 0x41) == false) {
		return false;
	}

	if (m_data != NULL) {
		delete[] m_data;
		m_data = NULL;
	}
	if (size > 0) {
		m_data = new char[size];

		if (archiveFile->seek(offset, File::START) == offset) {
			if (archiveFile->read(m_data, size) == size) {
				m_size = size;
				*(AsciiString *)(&m_nameStr) = filename;

				return true;
			}
		}
	}
	return false;
}

// ?scanInt@RAMFile@@UAE_NAAH@Z @ 0x0060580C (193B): slot 7 (offset 0x1C) of
// vtable 0x0087AA00. ZH GameEngine RAMFile::scanInt verbatim with BFME2
// (temp,1) concat spelling.
bool RAMFile::scanInt(int &newInt)
{
	newInt = 0;
	AsciiString tempstr;

	while ((m_pos < m_size) &&
		((m_data[m_pos] < '0') || (m_data[m_pos] > '9')) &&
		(m_data[m_pos] != '-')) {
		++m_pos;
	}

	if (m_pos >= m_size) {
		m_pos = m_size;
		return false;
	}

	do {
		char value;
		value = m_data[m_pos];
		tempstr.concat(&value, 1);
		++m_pos;
	} while ((m_pos < m_size) &&
		((m_data[m_pos] >= '0') && (m_data[m_pos] <= '9')));

	newInt = atoi(tempstr.str());
	return true;
}

// ?scanReal@RAMFile@@UAE_NAAM@Z @ 0x006058CD (232B): slot 8 (offset 0x20) of
// vtable 0x0087AA00. ZH GameEngine RAMFile::scanReal verbatim with BFME2
// (temp,1) concat spelling.
bool RAMFile::scanReal(float &newReal)
{
	newReal = 0.0f;
	AsciiString tempstr;
	bool sawDec = false;

	while ((m_pos < m_size) &&
		((m_data[m_pos] < '0') || (m_data[m_pos] > '9')) &&
		(m_data[m_pos] != '-') && (m_data[m_pos] != '.')) {
		++m_pos;
	}

	if (m_pos >= m_size) {
		m_pos = m_size;
		return false;
	}

	do {
		char value[2];
		value[0] = m_data[m_pos];
		tempstr.concat(value, 1);
		if (m_data[m_pos] == '.') {
			sawDec = true;
		}
		++m_pos;
	} while ((m_pos < m_size) &&
		(((m_data[m_pos] >= '0') && (m_data[m_pos] <= '9')) ||
		((m_data[m_pos] == '.') && !sawDec)));

	newReal = (float)atof(tempstr.str());
	return true;
}

// ?seek@RAMFile@@UAEHHW4seekMode@File@@@Z @ 0x006055AA (61B): slot 5 (offset
// 0x14) of vtable 0x0087AA00, between the rowed read (3) and nextLine (6).
// ZH GameEngine RAMFile::seek verbatim: START/CURRENT/END switch, clamp to
// [0, m_size], store m_pos.
int RAMFile::seek(int pos, seekMode mode)
{
	int newPos;

	switch (mode)
	{
		case START:
			newPos = pos;
			break;
		case CURRENT:
			newPos = m_pos + pos;
			break;
		case END:
			newPos = m_size + pos;
			break;
		default:
			// bad seek mode
			return -1;
	}

	if (newPos < 0)
	{
		newPos = 0;
	}
	else if (newPos > m_size)
	{
		newPos = m_size;
	}

	m_pos = newPos;

	return m_pos;
}

// ?readEntireAndClose@RAMFile@@UAEPADXZ @ 0x00605682 (31B): slot 13 (offset
// 0x34) of vtable 0x0087AA00. ZH GameEngine RAMFile::readEntireAndClose
// verbatim (its DEBUG_CRASH compiles out): hand m_data to the caller, then
// close through slot 2.
char *RAMFile::readEntireAndClose(void)
{
	if (m_data == 0)
	{
		return new char[1];	// just to avoid crashing...
	}

	char *tmp = m_data;
	m_data = 0;	// will belong to our caller!

	close();

	return tmp;
}

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int flags);
};

extern FileSystem *TheFileSystem;

// ?open@RAMFile@@UAE_NPAVFile@@@Z @ 0x006059B5 (115B): slot 17 (offset 0x44)
// of vtable 0x0087AA00, the File* overload LocalFile::convertToRAMFile calls.
// ZH RAMFile::open(File*) verbatim, as BFME1's RAMFileOpen.cpp donor has it.
bool RAMFile::open(File *file)
{
	if (file == 0)
		return false;

	int access = file->getAccess();

	if (!File::open(file->getName(), access))
		return false;

	m_size = file->size();
	m_data = new char[m_size];

	if (m_data == 0)
		return false;

	m_size = file->read(m_data, m_size);

	if (m_size < 0)
	{
		delete [] m_data;
		m_data = 0;
		return false;
	}

	m_pos = 0;
	return true;
}

// ?open@RAMFile@@UAE_NPBDH@Z @ 0x006056BD (61B): slot 1 of vtable 0x0087AA00.
// ZH RAMFile::open(name, access) through BFME's three-argument
// FileSystem::openFile (rowed at 0x00600C34), then the slot-17 overload.
bool RAMFile::open(const char *filename, int access)
{
	File *file = TheFileSystem->openFile(filename, access, 0);

	if (file == 0)
	{
		return false;
	}

	bool result = open(file);

	file->close();

	return result;
}
