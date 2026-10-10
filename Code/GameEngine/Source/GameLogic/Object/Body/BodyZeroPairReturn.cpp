// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Target004BD8A2..004BD8BD RET4 writes two zero floats through the hidden
// result pointer. The otherwise dead zeroed local is the value-return flags
// slot, as in the independently matched twelve-byte return at00596BB7.
// Original owner and payload type are unproved; only the measured two-float
// payload and nontrivial value-return ABI are modeled here.
struct BodyZeroPair004BD8A2 {
 float x,y;
 BodyZeroPair004BD8A2():x(0.0f),y(0.0f){}
 BodyZeroPair004BD8A2(const BodyZeroPair004BD8A2&);
 ~BodyZeroPair004BD8A2();
};
class Rva004BD8A2 {
public:virtual BodyZeroPair004BD8A2 rva004BD8A2();
};
BodyZeroPair004BD8A2 Rva004BD8A2::rva004BD8A2()
{
 return BodyZeroPair004BD8A2();
}
