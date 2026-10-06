// cl: /DNDEBUG /MD
//
// ?rva0060C3C3@Rva0060C3C3@@QAE_NPAURva0060C3C3Stream@@PAH@Z @0x0060C3C3 155B.
// Stream-header bind method: if this+0x14 already bound return false; else read
// a 4-byte magic and version through the stream's slot-3 reader, require magic
// 0x45414c41 and version 0x52545331/0x52545332, clear *extra, take an extra
// gated read for the second version, then bind this+0x14 to the stream with
// this+0x10 set from the trailing flags word. Evidence: 8 callers pass a
// stream plus int; prev/next share /DNDEBUG /MD /O1.
struct Rva0060C3C3Stream
{
	virtual void vs0();
	virtual void vs1();
	virtual void vs2();
	virtual int read(void *out, int len);
};

struct Rva0060C3C3
{
	char m_pad[0x10];
	unsigned char m_10;
	char m_pad11[3];
	void *m_14;
	int m_18;
	bool rva0060C3C3(Rva0060C3C3Stream *s, int *extra);
};

bool Rva0060C3C3::rva0060C3C3(Rva0060C3C3Stream *s, int *extra)
{
	if (m_14 != 0)
		return false;
	int magic;
	int version;
	int flags;
	if (s->read(&magic, 4) != 4)
		return false;
	if (s->read(&version, 4) != 4)
		return false;
	if (magic != 0x45414c41)
		return false;
	if (version != 0x52545331 && version != 0x52545332)
		return false;
	*extra = 0;
	if (version != 0x52545331)
		s->read(extra, 4);
	if (s->read(&flags, 4) == 4) {
		m_14 = s;
		m_10 = (flags != 0);
		m_18 = 0;
		return true;
	}
	return false;
}
