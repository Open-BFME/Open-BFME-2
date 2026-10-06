// cl: /MD /EHsc /O1
// The two target boundaries at 0x00515BCA and 0x00515C17 each construct the
// matched 0x00211E75 one-int handle from a local address, call the adjacent
// helper at 0x00515B0A with (handle, argument), then release the handle. Their
// only observed difference is the address-sized integer copied into the
// handle. The values below are target immediates; their meaning is unknown.
// The handle view reuses the matched constructor layout and rowed release call.

struct Impl00211E75;
class Rva00211E75
{
public:
	Rva00211E75(const int *arg);

private:
	Impl00211E75 *m_impl;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva00515Handle : public Rva00211E75
{
public:
	explicit Rva00515Handle(const int *arg) : Rva00211E75(arg) {}

	~Rva00515Handle()
	{
		Impl00211E75 *impl = *reinterpret_cast<Impl00211E75 **>(
			static_cast<Rva00211E75 *>(this));
		if (impl)
			ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(impl));
	}
};

// Address-derived view of the adjacent helper at RVA 0x00515B0A. Its callers
// establish the two stack arguments, but its larger implementation is not
// assigned a semantic name here.
void __cdecl rva00515B0A(Rva00515Handle *handle, int value);

// ?Rva00515BCA@@YAXH@Z @0x00515BCA 77B
void __cdecl Rva00515BCA(int value)
{
	const int callback = 0x00915921;
	Rva00515Handle handle(&callback);
	rva00515B0A(&handle, value);
}

// ?Rva00515C17@@YAXH@Z @0x00515C17 77B
void __cdecl Rva00515C17(int value)
{
	const int callback = 0x009158C2;
	Rva00515Handle handle(&callback);
	rva00515B0A(&handle, value);
}
