// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00326CF0, 249 bytes.
// BFME2 multiline listbox helper: splits input UnicodeString at 0x0A/NUL and
// appends each line via GadgetListBoxAddEntryText (0x00326BEC), returning rows
// added. Ported from Open-BFME-1
// game/GameEngine/Source/GameClient/GUI/Gadget/Rva004BB670GadgetListBoxAddEntryTextLines.cpp.
// Evidence: callers at 0x0057CA02/0x0057D838, callees concat 0x00037410,
// copy ctor 0x00037050, releaseBuffer 0x00036E70, AddEntryText 0x00326BEC.
// Why TU-local StringBase: shared bfme2_ascii header declares isEmpty,
// getCharAt and concat(T) out-of-line (would emit calls), while retail inlines
// isEmpty/getLength/getCharAt and calls concat(ptr,1) via an inline single-char
// helper; UnicodeString itself is not defined in the shared header.

template <typename T> class StringBase
{
	friend class UnicodeString;
public:
	StringBase() : m_data(0) {}
	int getLength() const { return m_data ? m_data->length : 0; }
	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	T getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
	void concat(T c) { concat(&c, 1); }
	void clear() { releaseBuffer(); }
	void concat(const T *str, int len);
	~StringBase() { releaseBuffer(); }
private:
	StringBase(const StringBase<T> &src);
	void releaseBuffer();
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
};
// Kept COMDATs for ?getCharAt@?$StringBase@G@@QBEGH@Z and
// ?isEmpty@?$StringBase@G@@QBE_NXZ live in the /O2
// string_base_inline unit (duplicated ret / mov eax,1); this TU is /O1
// (jmp to shared ret / xor+inc). Emit our copies with speed favoured so
// they match the kept bytes, while the inlined copies in
// Rva00326CF0AddLines keep the caller's /O1 shape.
#pragma optimize("s", off)
#pragma optimize("t", on)
template <> unsigned short StringBase<unsigned short>::getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
template <> __forceinline bool StringBase<unsigned short>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
#pragma optimize("", on)

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &src) : StringBase<unsigned short>(src) {}
	~UnicodeString() {}
};

class GameWindow;

int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite);

int Rva00326CF0AddLines(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite)
{
	int length = text.getLength();
	UnicodeString line;
	int rowsAdded = 0;
	for (int i = 0; i <= length; ++i) {
		unsigned short character = (i < length) ? text.getCharAt(i) : 0;
		if (character == 0x0A || character == 0) {
			if (line.isEmpty())
				line.concat((unsigned short)' ');
			GadgetListBoxAddEntryText(listbox, line, color, row++, column, overwrite);
			++rowsAdded;
			line.clear();
		} else {
			line.concat(character);
		}
	}
	return rowsAdded;
}
