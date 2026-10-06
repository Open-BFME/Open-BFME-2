// cl: /MD
// ?set@Rva001F3D03Slot@@QAEXMM@Z @0x001F3D03 30B.
// Forwards two floats to GameClientRandomVariable at +0x14 via rowed
// ?setRange@GameClientRandomVariable@@QAEXMMW4DistributionType@1@@Z with
// UNIFORM (1). Caller at 0x004A23E6. Honest Rva name; /O1 for the x87
// fld/fstp shuffle plus add plus tail call.
class GameClientRandomVariable {
public:
    enum DistributionType {
        CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
    };
    void setRange(float low, float high, DistributionType type);
};
class Rva001F3D03Slot {
public:
    void set(float a, float b);
    char m_lead[0x14];
    GameClientRandomVariable m_var;
};
void Rva001F3D03Slot::set(float a, float b)
{
    m_var.setRange(a, b, GameClientRandomVariable::UNIFORM);
}
