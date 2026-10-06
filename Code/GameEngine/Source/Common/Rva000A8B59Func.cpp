// cl: /MD
// ?rva000A8B59@Rva000A8B59@@QAE_NH@Z @0x000A8B59 20B unlock.
// Guarded forward to rowed ?rva0010F11C@Rva0010F110@@QAE_NH@Z then return true.
// Evidence: mov ecx [ecx] test je push [esp+4] call 0x0010F11C mov al 1 ret 4; caller at 0x00055EF1.
// Honest address name; owner unknown so class Rva000A8B59.
class Rva0010F110
{
public:
    bool rva0010F11C(int x);
};

class Rva000A8B59
{
public:
    bool rva000A8B59(int x);
private:
    Rva0010F110 *m_ptr;
};

bool Rva000A8B59::rva000A8B59(int x)
{
    if (m_ptr != 0)
        m_ptr->rva0010F11C(x);
    return true;
}
