// cl: /O1 /DNDEBUG /MD
// BFME1's cached status query, adapted to BFME2's out-of-line cache setter.
enum WeaponStatus { WEAPON_STATUS_UNKNOWN };
class Weapon
{
public:
    WeaponStatus getStatus() const;
    WeaponStatus computeStatus(bool *cacheable) const;
    __declspec(noinline) void cacheStatus(WeaponStatus status) const;
private:
    char m_unknown[0x10];
    mutable WeaponStatus m_status;
};

void Weapon::cacheStatus(WeaponStatus status) const
{
    if (m_status != status)
        m_status = status;
}

WeaponStatus Weapon::getStatus() const
{
    bool cacheable = true;
    WeaponStatus status = computeStatus(&cacheable);
    if (cacheable)
        cacheStatus(status);
    return status;
}
