// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?concat@?$StringBase@D@@QAEXABV?$CharSource@D@@@Z @0x00036A30 60B
// Narrow StringBase CharSource concat: twin of wide 0x000374A0 same 60B shape.
// Evidence: pinned ensure 0x000364A0 and rowed set 0x000368C0 in same TU family,
// callers at 0x00222CB7 0x00317C8C 0x005279B3 0x0059B101, vtable slot 0 getLength.
template <typename T>
class CharSource {
public:
    virtual int getLength() const = 0;
    virtual void _gap() const = 0;
    virtual int getChars(T *dest) const = 0;
};

template <typename T>
class StringBase {
private:
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
    Header *m_data;
    void ensureUniqueBufferOfSize(int newLen, bool keepData, const CharSource<T> *src1, const CharSource<T> *src2);
public:
    void set(const CharSource<T> &source);
    void concat(const CharSource<T> &source);
};

template <>
void StringBase<char>::concat(const CharSource<char> &source)
{
    int len = source.getLength();
    if (len == 0)
        return;
    if (m_data != 0) {
        ensureUniqueBufferOfSize(m_data->length + len, true, 0, &source);
        return;
    }
    set(source);
}
