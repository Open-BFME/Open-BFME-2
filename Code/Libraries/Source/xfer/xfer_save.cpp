// cl: /DNDEBUG /MD
// Save-side stream transfer and block finalization recovered under their
// reciprocal WorldBuilder TU.

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
	virtual void slot3();
	virtual int write(const void *buffer, int size);
	virtual int skip(int count, int flag);
};

class BfmePositionVector
{
public:
	int *m_begin;
	int *m_end;
	int *m_capacity;

	int &back()
	{
		return m_end[-1];
	}

	void pop_back()
	{
		--m_end;
	}
};

class XferSave
{
public:
	virtual void XferEnum(void *context, const void *bytes, unsigned int count);
	virtual void endBlock();

private:
	BfmeByteStream * volatile m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	BfmePositionVector m_positions;
};

void XferSave::XferEnum(void *context, const void *bytes, unsigned int count)
{
	if (m_stream == 0)
		return;

	register const void *block = bytes;
	register unsigned int n = count;
	if (n != 0 && block == 0)
		return;

	if (m_flag && context != 0)
	{
		if (m_stream->write(&context, 4) != 4)
		{
			throw XferException(1, 0);
		}
	}

	if (n != 0)
	{
		if (m_stream->write(block, static_cast<int>(n)) != static_cast<int>(n))
		{
			throw XferException(1, 0);
		}
	}
}

void XferSave::endBlock()
{
	if (m_stream == 0)
		return;
	if (m_positions.m_begin == m_positions.m_end)
		return;

	if (m_flag)
	{
		int marker = 0x45424c4b;
		if (m_stream->write(&marker, 4) != 4)
		{
			throw XferException(1, 0);
		}
	}

	int blockSize = m_positions.back();
	m_positions.pop_back();

	int position = m_stream->skip(0, 1);
	if (position == -1)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(blockSize, 0) != blockSize)
	{
		throw XferException(1, 0);
	}

	if (m_stream->write(&position, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(position, 0) != position)
	{
		throw XferException(1, 0);
	}
}
