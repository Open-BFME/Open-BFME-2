// cl: /MD /EHs-c-
// BFME2 1.06 StringBase<char>::trim, RVA 0x00037CF0.
// Narrow sibling of the reconstructed wide trim: skip leading space,
// set the remainder, then remove trailing whitespace one character at a time.
extern "C" __declspec(dllimport) int __cdecl isspace(int);
template <typename T>
class StringBase {
public:
    void trim();
    void set(const T *str, int len);
    void removeLastChar();
private:
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
    Header *m_data;
};
template <>
void StringBase<char>::trim()
{
    if (m_data) {
        const char *start = m_data->data;
        while (*start && isspace(*start))
            ++start;
        if (start != m_data->data) {
            int len = m_data ? m_data->length : 0;
            set(start, (int)((char *)m_data - start) + len + 8);
        }
        if (m_data) {
            int index = m_data->length;
            while (index > 0) {
                --index;
                if (isspace((char)(m_data ? m_data->data[index] : 0)))
                    removeLastChar();
                else
                    break;
            }
        }
    }
}
