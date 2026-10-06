// cl: /MD /Oi-
// ?rva0054273B@Rva0054273B@@QAE_NXZ @0x0054273B 86B
// XML comment-end skip: after +2 expects "--" then scans to "-->" returning
// true on '>' else false on NUL. Evidence: retail bytes leaf lane plus
// neighbours Rva005426DBDecode and Rva005427F1Flush same flags and +0 layout.
class Rva0054273B
{
public:
	bool rva0054273B();
private:
	char *m_ptr;
};

bool Rva0054273B::rva0054273B()
{
	m_ptr += 2;
	if (*m_ptr != '-')
		return false;
	++m_ptr;
	if (*m_ptr != '-')
		return false;
	++m_ptr;
	if (*m_ptr == 0)
		return false;
	for (;;) {
		char *p = m_ptr;
		while (*p != 0 && *p != '-')
			++p;
		m_ptr = p;
		if (*p == 0)
			return false;
		++p;
		m_ptr = p;
		if (*p == 0)
			return false;
		if (*p != '-')
			continue;
		++p;
		m_ptr = p;
		if (*p == 0)
			return false;
		if (*p != '>')
			continue;
		++p;
		m_ptr = p;
		return true;
	}
}
