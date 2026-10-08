// cl: /DNDEBUG /MD
// ?rva00478231@Rva00478231@@QAEX_N@Z @0x00478231 (46B): GarrisonContain
// removeAllContained shape after the slot38-leaf precedent — the donor TU's
// class model has the wrong vtable slots, so this uses flat classes: a
// gap-templated vtable carrying recalcApparentControllingPlayer at slot 0x50
// and getContainCount(int) at slot 0x114; the rowed GarrisonContain
// validateRallyPoint is reached on this-0x20 through an address-honest pin
// (its true protection is inherited-only); OpenContain::removeAllContained
// is called non-virtually through its pin at 0x004635C0. All three guarded
// by getContainCount(0) > 0. Honest address name; owning class unproven.

template <int N> class Rva00478231Gaps : public Rva00478231Gaps<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00478231Gaps<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva00478231Low : public Rva00478231Gaps<20>
{
public:
	virtual void recalcApparentControllingPlayer() = 0; // slot 0x50
};

template <int N> class Rva00478231Mid : public Rva00478231Mid<N - 1>
{
public:
	virtual void mid(char (*)[N]) = 0;
};
template <> class Rva00478231Mid<1> : public Rva00478231Low
{
public:
	virtual void mid(char (*)[1]) = 0;
};

// The rally-point check is the rowed protected GarrisonContain::validateRallyPoint.
class GarrisonContain
{
	friend class Rva00478231;
protected:
	void validateRallyPoint();
};

class OpenContain
{
public:
	virtual void removeAllContained(bool exposeStealthUnits);
};

class Rva00478231 : public Rva00478231Mid<48>
{
public:
	virtual unsigned int getContainCount(unsigned int arg) = 0; // slot 0x114
	void rva00478231(bool exposeStealthUnits);
};

// ?validateRallyPoint@Rva00478231@@QAEXXZ @0x00478141 (pinned): the rowed
// GarrisonContain method is protected-only; this address-honest spelling
// carries the call. Declared, never defined here.

// ?rva00478231@Rva00478231@@QAEX_N@Z
void Rva00478231::rva00478231(bool exposeStealthUnits)
{
	if (getContainCount(0) > 0u) {
		((GarrisonContain *)((char *)this - 0x20))->validateRallyPoint();
		((OpenContain *)this)->OpenContain::removeAllContained(exposeStealthUnits);
		recalcApparentControllingPlayer();
	}
}
