// cl: /MD
// ?rva0073F895@Rva0073F895@@QAEHXZ @0x0073F895 213B, caller 0x0073FAB8.
// Fade state machine: state +0x40 (0 fade in, 1 held, 2 fade out, 3 off)
// steps the fade +0x44 by the 1/60 literal at 0x00BC625C, then returns the
// base colour +0x38 when fully faded in, 0 when faded out, otherwise the
// colour scaled through the rowed RGBColor setFromInt/getAsInt with full
// alpha.
// Structural inference: retail lays case 0 directly before case 1 (it falls
// through into the held store) and keeps the comiss operand order of
// fade >= 1, fade <= 0, fade < 1 and fade > 0 as written here.
struct RGBColor {
    float red;
    float green;
    float blue;
    int getAsInt() const;
    void setFromInt(int color);
};
class Rva0073F895 {
    char _pad[0x38];
    int m_base;
    char _pad3C[4];
    int m_state;
    float m_fade;
public:
    int rva0073F895();
};
int Rva0073F895::rva0073F895()
{
    switch (m_state) {
    case 0:
        m_fade += 1.0f / 60.0f;
        if (!(m_fade >= 1.0f))
            break;
        m_state = 1;
    case 1:
        m_fade = 1.0f;
        break;
    case 2:
        m_fade -= 1.0f / 60.0f;
        if (m_fade <= 0.0f) {
            m_fade = 0.0f;
            m_state = 3;
        }
        break;
    case 3:
        m_fade = 0.0f;
        break;
    }
    if (m_fade < 1.0f) {
        if (m_fade > 0.0f) {
            RGBColor c;
            c.setFromInt(m_base);
            c.red *= m_fade;
            c.green *= m_fade;
            c.blue *= m_fade;
            return c.getAsInt() | 0xff000000;
        }
        return 0;
    }
    return m_base;
}
