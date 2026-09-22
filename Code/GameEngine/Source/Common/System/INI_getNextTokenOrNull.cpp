// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?getNextTokenOrNull@INI@@QAEPBDPBD@Z, retail 0x002DEED, 170 bytes.
// Dedicated shard TU (same-TU visibility law: grafting into the sibling
// INI_getNextToken TU would recolor its getNextTokenOrNull call site).
//
// BFME2 keeps a token cursor over the line buffer: while the buffer holds
// text, strtok continues the current line; once exhausted, nextToken pulls
// the next line into a scratch token, banks it in m_tokens, and returns a
// pointer to the banked copy (or "" when the scratch is empty). On
// exhaustion the buffer is cleared and the shared strtok tail decides.
// ZH's donor is a plain static strtok wrapper (no buffer/vector), so only
// the separators default (m_seps at this+0x418, BFME1 +0x414) transfers.

extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

template <typename T>
class StringBase
{
public:
	bool nextToken(StringBase<T> *out, const T *seps);

	friend class INI;
	friend class AsciiString;

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

private:
	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() { m_data = 0; }
	~AsciiString();
	bool isEmpty() const;
	void clear();
	const char *str() const
	{
		const char *text = (const char *)m_data;
		if (text != 0)
			text += 8;
		else
			text = "";
		return text;
	}
};

namespace _STL
{
template <typename T>
class allocator
{
};

template <typename T, typename A = allocator<T> >
class vector
{
public:
	void push_back(const T &value);
	T &back() { return *(m_finish - 1); }

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);

private:
	char m_pad0[0x418];
	const char *m_seps;
	char m_pad1[0x86C - 0x41C];
	AsciiString m_buffer;
	_STL::vector<AsciiString> m_tokens;
};

// ?getNextTokenOrNull@INI@@QAEPBDPBD@Z
const char *INI::getNextTokenOrNull(const char *seps)
{
	if (seps == 0)
		seps = m_seps;
	if (!m_buffer.isEmpty()) {
		AsciiString token;
		if (m_buffer.nextToken(&token, seps)) {
			m_tokens.push_back(token);
			AsciiString *finish = m_tokens.m_finish;
			const char *result = (const char *)finish[-1].m_data;
			if (result != 0)
				result += 8;
			else
				result = "";
			return result;
		}
		m_buffer.clear();
	}
	return strtok(0, seps);
}
