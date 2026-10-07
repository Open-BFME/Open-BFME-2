// cl: /Ireference/shims/bfme2_ascii /GX-
// ?rva0059B49E@Rva0059B49E@@QAEXPADHH@Z at 0x0059B49E (97B).
// Bounded two-phase copy: length-clamped rva002AC2CF then memcpy remainder.
// Evidence: caller 0x0059B428 same shape; callees length 0x00513B94 rowed pin rva002AC2CF memcpy import; prev Rva0059B3E9Write same flags.

#include "ascii_string.h"

class Rva002226E5TextPlusString
{
public:
	int length() const;
};

class Rva002AC2CFTarget
{
public:
	void rva002AC2CF(int a0, int a1, int a2);
};

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

class Rva0059B49E
{
public:
	void rva0059B49E(char *dst, int off, int len);
private:
	char m_pad[0xC];
	const char *m_src;
};

void Rva0059B49E::rva0059B49E(char *dst, int off, int len)
{
	int total = ((Rva002226E5TextPlusString *)this)->length();
	if (off < total)
	{
		int cnt = len;
		if (off + len > total)
			cnt = total - off;
		((Rva002AC2CFTarget *)this)->rva002AC2CF((int)dst, off, cnt);
		len -= cnt;
		if (len <= 0)
			return;
		dst += cnt;
		off += cnt;
	}
	const char *src = m_src - total + off;
	memcpy(dst, src, len);
}

// Native 0x0059B428..0x0059B49E, RET12, reached by the rowed +4
// forwarder at 0x0059B420. Keep its established three-int ABI spelling;
// the first argument is a buffer address. The original node type is
// unknown. Its prefix length is the rowed text/string length plus +10;
// the final AsciiString operand is at +14, independently read in retail.
class Rva0059B428
{
 char m_opaque[0x10];
 int m_extraLen;
 const AsciiString *m_suffix;
public:
 void rva0059B428(int destination, int offset, int count);
};

void Rva0059B428::rva0059B428(int destination, int offset, int count)
{
 int total=((Rva002226E5TextPlusString *)this)->length()+m_extraLen;
 if (offset<total) {
  int chunk=count;
  if (offset+count>total)
   chunk=total-offset;
  ((Rva0059B49E *)this)->rva0059B49E((char *)destination,offset,chunk);
  count-=chunk;
  if (count<=0)
   return;
  destination+=chunk;
  offset+=chunk;
 }
 offset-=total;
 memcpy((char *)destination,m_suffix->str()+offset,count);
}
