// cl: /MD /EHsc
// ??1Rva004D6208@@MAE@XZ retail 0x004D6208 72B.
// Dtor: vptr 0x860484 then array delete at +0x20 with null assign then Ascii releaseBuffer at +0x1c then vptr 0x860130.
// Evidence: vtable 0x860484 plus caller 0x004D6ABC plus neighbour setters.
#include <new>
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();

typedef int Int;
typedef bool Bool;
class AsciiString;

#include "../../Include/GameNetwork/NetCommandMsg.h"
inline NetCommandMsg::~NetCommandMsg() {}
class Rva004D6208 : public NetCommandMsg
{
protected:
	virtual ~Rva004D6208();
private:
	StringBase<char> m_str1c;
	unsigned char *m_data20;
};
Rva004D6208::~Rva004D6208()
{
	if (m_data20 != 0) {
		delete[] m_data20;
		m_data20 = 0;
	}
}
