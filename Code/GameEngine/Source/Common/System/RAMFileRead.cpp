// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE
// ?read@RAMFile@@UAEHPAXH@Z @ 0x00605564 (70B): slot 3 (offset 0xC) of vtable
// 0x0087AA00. ZH GameEngine RAMFile::read verbatim: null m_data returns -1,
// clamp to m_size-m_pos via cmovg, memcpy when bytes>0 and buffer set,
// advance m_pos. Contiguous with rowed RAMFile close 0x00605547 and RAMFile
// dtor 0x00605504. cmov needs /arch:SSE (no /G flag emits it). memcpy is a
// plain extern E8 to the rowed import thunk 0x006291A8.

#define NULL 0

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);
extern "C" __declspec(dllimport) int __cdecl isspace(int c);

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
};

class AsciiString : private StringBase<char>
{
public:
	void clear();

	void concat(const char *text, int length)
	{
		StringBase<char>::concat(text, length);
	}
};

class File
{
public:
	virtual int read(void *buffer, int bytes);
	virtual void nextLine(char *buf, int bufSize);
	virtual bool scanString(AsciiString &newString);

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
	virtual int read(void *buffer, int bytes);
	virtual void nextLine(char *buf, int bufSize);
	virtual bool scanString(AsciiString &newString);

protected:
	char *m_data;	// +0x14
	int m_pos;	// +0x18
	int m_size;	// +0x1c
};

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
