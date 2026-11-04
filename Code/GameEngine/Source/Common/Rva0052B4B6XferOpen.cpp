// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// ?rva0052B4B6@Rva0052B4B6@@QAE_NPAVXfer@@@Z, retail 0x0052B4B6 (73 bytes,
// RET 4): for a non-null stream, open it through the rowed XferSave::Open
// 0x0060D10A (version 1, flag = !vslot 4) on this object and fail when that
// does; then clear the 16 bytes at +0x41, MD5Init the context the pointer
// at +0x54 names (rowed 0x00606220) and clear the byte at +0x58. The owner
// is an XferSave-based writer whose name is not established; names are
// address-derived.
#include <string.h>

struct MD5_CTX;
extern "C" void MD5Init(MD5_CTX *context);	// GameSpy md5c.c

class Xfer;

class XferSave
{
public:
	unsigned char Open(Xfer *stream, int version, bool flag);
};

class Rva0052B4B6
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual bool slot4();
	bool rva0052B4B6(Xfer *stream);
private:
	char m_pad04[0x41 - 0x04];
	unsigned char m_digest[0x10];
	char m_pad51[0x54 - 0x51];
	MD5_CTX *m_md5;	// +0x54
	bool m_58;
};

bool Rva0052B4B6::rva0052B4B6(Xfer *stream)
{
	if (stream && !((XferSave *)this)->Open(stream, 1, !slot4()))
		return false;
	memset(m_digest, 0, sizeof(m_digest));
	MD5Init(m_md5);
	m_58 = false;
	return true;
}
