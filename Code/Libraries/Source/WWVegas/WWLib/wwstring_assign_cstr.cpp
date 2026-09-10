// cl: /O1 /G7 /Oi- /DNDEBUG /MD
//
// StringClass::operator=(const char *), retail 0x000F0E8D, 68 bytes. Dedicated
// TU so wwstring.cpp cannot see this definition. Calls the already-landed
// Uninitialised_Grow, then writes the cached length and memcpy's the text.

#include <string.h>
#pragma function(strlen)
#pragma function(memcpy)

class StringClass
{
public:
	const StringClass &operator=(const char *string);

private:
	void Uninitialised_Grow(int new_len);

	static char *m_EmptyString;
	char *m_Buffer;
};

char *StringClass::m_EmptyString;

const StringClass &StringClass::operator=(const char *string)
{
	if (string != 0)
	{
		int len = (int)strlen(string);
		Uninitialised_Grow(len + 1);
		if (m_Buffer != m_EmptyString)
			*reinterpret_cast<int *>(m_Buffer - 4) = len;
		memcpy(m_Buffer, string, (size_t)(len + 1));
	}
	return *this;
}
