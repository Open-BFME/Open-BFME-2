// cl: /O2 /DNDEBUG /MD /EHs-c-
//
// ?set@?$StringBase@D@@QAEXPBDHH@Z, retail 0x00037C10, 93 bytes.
// StringBase<char> substring setter: measures the source with strlen
// (empty for null), clamps the (pos, n) range against the measured length
// (clearing through releaseBuffer when the range is empty or out of range)
// and forwards the clamped slice to the 2-arg set at 0x36780.
// Mirrors the landed StringBaseWideSet TU (0x37E90): the wide twin calls
// wcslen while the narrow twin calls strlen, which /O2 intrinsifies into
// the inline scan loop retail shows (lea esi,[eax+1] head).
//
// ?set@?$StringBase@D@@QAEXABV1@HH@Z, retail 0x00037C70, 119 bytes.
// StringBase<char> substring setter taking a StringBase source: the length
// is re-read from the source header at each clamp step (retail reads the
// length word three times), then the clamped slice of the source payload
// (with the empty-string fallback for a null header) forwards to the 2-arg
// set at 0x36780.

#include <string.h>

typedef char NarrowChar;

template <typename T>
class StringBase
{
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;

	void releaseBuffer();
	int getLength() const { return m_data ? m_data->length : 0; }

public:
	void set(const T *str, int pos, int count);
	void set(const StringBase &src, int pos, int count);
	void set(const T *str, int len);
};

template <>
void StringBase<NarrowChar>::set(const NarrowChar *str, int pos, int count)
{
	int len;
	if (str)
		len = (int)strlen(str);
	else
		len = 0;
	int end = pos + count;
	if (end < 0 || pos >= len) {
		releaseBuffer();
		return;
	}
	if (pos < 0) {
		count = end;
		pos = 0;
	}
	if (pos + count >= len)
		count = len - pos;
	set(str + pos, count);
}

template <>
void StringBase<NarrowChar>::set(const StringBase &src, int pos, int count)
{
	int end = pos + count;
	if (end < 0 || pos >= src.getLength()) {
		releaseBuffer();
		return;
	}
	if (pos < 0) {
		count = end;
		pos = 0;
	}
	if (pos + count >= src.getLength())
		count = src.getLength() - pos;
	const NarrowChar *payload = src.m_data ? src.m_data->data : "";
	set(payload + pos, count);
}
