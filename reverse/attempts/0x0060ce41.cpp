// ??8XferSave@@UAEAAVXfer@@AAVPooledString@@@Z
// partial score=0.85 date=2026-10-11
// cl: /DNDEBUG /MD
// Save-side stream transfer and block finalization recovered under their
// reciprocal WorldBuilder TU.

extern "C" unsigned int __cdecl strlen(const char *);

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

// The pooled-string table at +0x2C: the rowed lookup 0x0060CB2B and the
// ICF-folded hash_map subscript 0x0060CDFD under their row spellings.
class Xfer;
class PooledString { public: const char *m_text; };
struct Rva0060CB2BNode { void *m_next; const char *m_key; int m_offset; };
class Rva0060CB2B { public: Rva0060CB2BNode *rva0060CB2B(const char *const &key) const; unsigned char m_data[0x10]; };
enum NameKeyType { NAMEKEY_INVALID = 0 };
class Rva00427157;
namespace rts { template <class T> struct hash; }
namespace _STL {
template <class T> struct equal_to;
template <class A, class B> struct pair;
template <class T> class allocator;
template <class K, class V, class H, class E, class A> class hash_map { public: V &operator[](const K &key); };
}
typedef _STL::hash_map<NameKeyType, const Rva00427157 *, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType>,
	_STL::allocator<_STL::pair<const NameKeyType, const Rva00427157 *> > > XferSaveStringTable;

class XferSave
{
public:
	virtual void XferEnum(void *context, const void *bytes, unsigned int count);
	virtual void endBlock();
	virtual Xfer &operator==(PooledString &str);

private:
	BfmeByteStream * volatile m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	BfmePositionVector m_positions;
	unsigned char m_pad18[0x28 - 0x18];
	int m_28;
	Rva0060CB2B m_table;	// +0x2C
	int m_3C;
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

// XferSave slot 11, retail 0x0060CE41 (281 bytes, ret 4): with a stream and
// the tagged flag set, a non-empty pooled string is written after the
// 'RCSD' marker either as 0xFF plus the offset already recorded for it in
// the +0x2C table, or as a length byte (at most 254) and its characters,
// recording +0x28 plus +0x3C as its offset. Any short write throws
// XferException(1, 0). The operator== spelling follows XferSaveAsText's
// pooled-string slot.
Xfer &XferSave::operator==(PooledString &str)
{
	if (m_stream == 0)
		return *(Xfer *)this;
	if (!m_flag || str.m_text == 0 || *str.m_text == 0)
		return *(Xfer *)this;
	{
		int marker = 0x44534352;
		if (m_stream->write(&marker, 4) != 4)
			throw XferException(1, 0);
	}
	const char *key = str.m_text;
	Rva0060CB2BNode *found = m_table.rva0060CB2B(key);
	if (found != 0)
	{
		unsigned char escape = 0xFF;
		if (m_stream->write(&escape, 1) != 1)
			throw XferException(1, 0);
		if (m_stream->write(&found->m_offset, 4) != 4)
			throw XferException(1, 0);
	}
	else
	{
		unsigned int length = strlen(key);
		if (length > 0xFE)
			length = 0xFE;
		if (m_stream->write(&length, 1) != 1)
			throw XferException(1, 0);
		if (m_stream->write(key, length) != (int)length)
			throw XferException(1, 0);
		((XferSaveStringTable *)&m_table)->operator[](*(const NameKeyType *)&key) = (const Rva00427157 *)(m_28 + m_3C);
	}
	return *(Xfer *)this;
}
