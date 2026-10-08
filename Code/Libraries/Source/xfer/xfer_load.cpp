// cl: /DNDEBUG /MD
// Load-side block traversal recovered under its reciprocal WorldBuilder TU.

typedef bool Bool;

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	void *text;
	int tag;
};


class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual int read(void *buffer, int size);
	virtual void slot4();
	virtual int skip(int count, int flag = 0);
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual int current();
};

class Gen009D8C30
{
public:
	void bfmeSkipPrefixed();
private:
	unsigned char m_pad[0x14];
	BfmeByteStream *m_stream;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);

	// Retail vtable RVA 0x0087AF18 puts XferImpl at slot 38 (+0x98).
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();

protected:
	virtual void XferImpl(unsigned int type, void *data, unsigned int size);

	unsigned char m_pad04[0x0c];
	Bool m_isLoading;
	unsigned char m_pad11[3];
	BfmeByteStream *m_stream;
	int m_blockCount;
	int m_currentBlock;
};

int Xfer::beginBlock(const char *name)
{
	if (m_stream == 0)
		return 0;

	int marker;
	if (m_stream->read(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (marker == 0x44534352)
	{
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();
		if (m_stream->read(&marker, 4) != 4)
		{
			throw XferException(1, 0);
		}
	}

	if (marker != 0x424c4f4b)
	{
		int position = m_stream->skip(0, 1) - 4;
		throw XferException(0,
			"Block '%s' expected but BLOK ID was not found at %i", name, position);
	}

	if (m_isLoading)
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();

	if (m_stream->read(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	m_currentBlock = m_stream->current();
	++m_blockCount;
	return marker;
}

void Xfer::endBlock()
{
	if (m_stream == 0 || m_blockCount == 0)
		return;

	if (m_isLoading)
	{
		int marker;
		if (m_stream->read(&marker, 4) != 4)
		{
			throw XferException(1, 0);
		}

		if (marker != 0x45424c4b)
		{
			int position = m_stream->skip(0, 1) - 4;
			throw XferException(0,
				"Block end expected but EBLK ID was not found at %i", position);
		}
	}

	m_currentBlock = -1;
	--m_blockCount;
}

void Xfer::skipBlock(const char *name)
{
	if (m_stream == 0)
		return;

	int marker;
	if (m_stream->read(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (marker != 0x424c4f4b)
	{
		int position = m_stream->skip(0, 1) - 4;
		throw XferException(0,
			"Block '%s' expected but BLOK ID was not found at %i", name, position);
	}

	if (m_isLoading)
		reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();

	if (m_stream->read(&marker, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(marker) != marker)
	{
		throw XferException(0,
			"Could not skip over block '%s' to %i", name, marker);
	}
}

typedef void (__cdecl *BfmeSkipCallback)(void *snapshot, void *ctx, int extra);

class BlockStreamReader
{
public:
	void skipBadBlock(void *snapshot, int size);

private:
	unsigned char m_pad0[8];
	BfmeSkipCallback m_callback;
	void *m_ctx;
	unsigned char m_pad1[4];
	BfmeByteStream *m_stream;
	int m_count;
	int m_extra;
};

void BlockStreamReader::skipBadBlock(void *snapshot, int size)
{
	if (m_stream->skip(size, 0) != size)
	{
		throw XferException(0, "Could not skip over BAD block to %i", size);
	}

	if (m_callback)
		m_callback(snapshot, m_ctx, m_extra);
	m_extra = -1;
	--m_count;
}

// ?bfmeSkipPrefixed@Gen009D8C30@@QAEXXZ @0x0060C59D 93B.
// Skip length-prefixed data via stream read plus skip. Evidence: callers beginBlock skipBlock rowed;
// callee formatText rowed 0x0060C36E plus throw pin 0x00629094; neighbours share /DNDEBUG /MD /O1.
void Gen009D8C30::bfmeSkipPrefixed()
{
	unsigned char prefix;
	if (m_stream->read(&prefix, 1) != 1)
	{
		throw XferException(1, 0);
	}
	if (prefix == 0)
		return;
	int n = (prefix == 0xff) ? 4 : prefix;
	m_stream->skip(n, 1);
}

// WorldBuilder 0x0165C090 names XferLoad::XferImpl in xfer_load.cpp
// (assert lines 171..196); retail 0x0060C7AD..0x0060C8B1 is its slot-38 body.
// ByteStream reads and the existing skip helper establish the tag/payload protocol.
class XferLoad : public Xfer
{
public:
    virtual void XferImpl(unsigned int type, void *data, unsigned int size);
};

void XferLoad::XferImpl(unsigned int type, void *data, unsigned int size)
{
    if ((size && !data) || !m_stream)
        return;

    if (m_isLoading && type)
    {
        unsigned int marker;
        for (;;)
        {
            if (m_stream->read(&marker, 4) != 4)
                throw XferException(1, 0);
            if (marker != 0x44534352)
                break;
            reinterpret_cast<Gen009D8C30 *>(this)->bfmeSkipPrefixed();
        }
        if (marker != type)
        {
            // Reverse the little-endian tag bytes into printable four-character IDs.
            const unsigned char *markerBytes = reinterpret_cast<const unsigned char *>(&marker);
            char found[5] = {char(markerBytes[3]), char(markerBytes[2]),
                             char(markerBytes[1]), char(markerBytes[0]), 0};
            const unsigned char *typeBytes = reinterpret_cast<const unsigned char *>(&type);
            char expected[5] = {char(typeBytes[3]), char(typeBytes[2]),
                                char(typeBytes[1]), char(typeBytes[0]), 0};
            throw XferException(0, "Expected '%s' but found '%s'", expected, found);
        }
    }
    if (size && m_stream->read(data, size) != int(size))
        throw XferException(1, 0);
}
