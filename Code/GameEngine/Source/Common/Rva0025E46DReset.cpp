// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?CreateTheNetwork@@YAXXZ @0x0025E46D 96B
// Free network reset: destroy the current TheNetwork (0x00DFEA28), then
// allocate a 0x40-byte BFME2NativeNetwork, construct it through the rowed
// constructor 0x0025DB6D (its only caller is the call at 0x0025E4A8 here),
// store it and call the init slot +4.
// Retail calls vtable slot 0 with flag 0 and hands the result to operator
// delete even for null: that is `::delete` through a virtual dtor. The EH
// state around the constructor call, whose unwind entry frees the
// allocation, is the ordinary `new T` frame; the banked 0.93 attempt spelled
// both by hand and missed the frame.
class NetworkInterface
{
public:
	virtual ~NetworkInterface();
	virtual void init();
};

class BFME2NativeNetwork : public NetworkInterface
{
public:
	BFME2NativeNetwork();
private:
	char m_pad[0x3C];
};

extern NetworkInterface *TheNetwork;

void CreateTheNetwork()
{
	::delete TheNetwork;
	TheNetwork = new BFME2NativeNetwork;
	TheNetwork->init();
}
