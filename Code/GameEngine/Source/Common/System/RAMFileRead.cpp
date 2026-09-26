// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE
// ?read@RAMFile@@UAEHPAXH@Z @ 0x00605564 (70B): slot 3 (offset 0xC) of vtable
// 0x0087AA00. ZH GameEngine RAMFile::read verbatim: null m_data returns -1,
// clamp to m_size-m_pos via cmovg, memcpy when bytes>0 and buffer set,
// advance m_pos. Contiguous with rowed RAMFile close 0x00605547 and RAMFile
// dtor 0x00605504. cmov needs /arch:SSE (no /G flag emits it). memcpy is a
// plain extern E8 to the rowed import thunk 0x006291A8.

#define NULL 0

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);

class File
{
public:
	virtual int read(void *buffer, int bytes);
	virtual void nextLine(char *buf, int bufSize);

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
