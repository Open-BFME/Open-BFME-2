// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?readLine@INI@@IAEXXZ @0x0002D669, 143 bytes. INI line reader (r15: unsigned-count fix).
//
// TARGET (retail facts): no-arg thiscall void (push esi/edi, ret); Ghidra
// FUN_0042d669 143B chain-exact (0x2D2C1+936=0x2D669, 0x2D669+143=0x2D6F8);
// calls size-like /12 body at 0x5D5847 (rowed vector<BfmeE12>::size), INT
// accessor at 0x6018B6 (rowed INIFileTable::getFileId), strncpy import
// (IAT 0xBBA620), rowed vector<AsciiString>::erase at 0x2CCFC, string clear
// at 0x36410 (rowed releaseBuffer bytes via canonical AsciiString::clear
// alias), strlen thunk at 0x629170 plus Xfer virtual slot 0x24 (xferUser)
// behind global 0xDDF57C. True branch copies a line into m_buffer (+0x14,
// 0x403 chars, last byte at +0x417 cleared), resets token cursor (vector at
// +0x870, AsciiString at +0x86C); false branch latches endOfFile (+0x430)
// and empties the buffer; tail hashes every line through s_xfer.
// Consumers: loadFile 0x2DC75, initFromINIMulti 0x2D7A8 (blocked 5578/662).
// No symbols.csv pin at 0x2D669.
//
// DONOR (reference facts, guidance only): BFME1 ini.cpp INI::readLine (void,
// no args): if (m_lineNum < (UnsignedInt)(m_lines.m_end - m_lines.m_begin))
// { line = m_lines.getText(m_lineNum++); strncpy(m_buffer,line,MAX-1);
// m_buffer[MAX-1]=0; } else { m_endOfFile=TRUE; m_buffer[0]=0; }
// if (s_xfer) s_xfer->xferUser(m_buffer, strlen(m_buffer)).
// Unsigned compare is donor-explicit; r14 signed cast emitted jge, retail is
// jae. INFERENCE: outer method is INI::readLine (arity/ABI/shape/consumer
// need agree); line-text meaning of getFileId slot + 12B views is inference,
// bytes/providers are target facts.

#include "ascii_string.h"

extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dst, const char *src, unsigned int n);
extern "C" unsigned int __cdecl strlen(const char *s);

struct BfmeE12
{
	float x, y, z;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	typedef T *iterator;
	unsigned int size() const;
	iterator erase(iterator first, iterator last);
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class INIFileTable
{
public:
	int getFileId(int fileIndex) const;

	int m_reserved;
	_STL::vector<BfmeE12> m_lineVec;
	char m_tail[0x86C - 0x848];
};

// Target proves a raw buffer/size call through slot 9, not its class or method name.
class BfmeIniTransferSlot09
{
public:
	virtual void _d0() = 0;
	virtual void _d1() = 0;
	virtual void _d2() = 0;
	virtual void _d3() = 0;
	virtual void _d4() = 0;
	virtual void _d5() = 0;
	virtual void _d6() = 0;
	virtual void _d7() = 0;
	virtual void _d8() = 0;
	virtual void slot09(void *data, int dataSize) = 0;
};

// Sole provider: retail VA 0x00DDF57C contains four initial zero bytes.
// The clear routine and reader share this pointer without naming its runtime class.
void *g_00DDF57C = 0;

class INI
{
protected:
	void readLine();

private:
	void *m_file;
	AsciiString m_filename;
	int m_08;
	int m_0C;
	int m_lineNum;
	char m_buffer[0x418 - 0x14];
	char m_pad418[0x430 - 0x418];
	unsigned char m_endOfFile;
	char m_pad431[0x838 - 0x431];
	INIFileTable m_fileTable;
	AsciiString m_tokenBuf;
	_STL::vector<AsciiString> m_tokens;
};

// ?readLine@INI@@IAEXXZ
void INI::readLine()
{
	if ((unsigned int)m_lineNum < m_fileTable.m_lineVec.size()) {
		int cur = m_lineNum;
		m_0C = cur;
		m_lineNum = cur + 1;
		const char *line = (const char *)m_fileTable.getFileId(cur);
		strncpy(m_buffer, line, 0x403);
		m_buffer[0x403] = 0;
		_STL::vector<AsciiString> &toks = m_tokens;
		AsciiString *first = toks.begin();
		AsciiString *last = toks.end();
		toks.erase(first, last);
		m_tokenBuf.clear();
	} else {
		m_endOfFile = 1;
		m_buffer[0] = 0;
	}
	if (g_00DDF57C != 0) {
		unsigned int len = strlen(m_buffer);
		((BfmeIniTransferSlot09 *)g_00DDF57C)->slot09(m_buffer, (int)len);
	}
}
