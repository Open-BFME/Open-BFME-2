// cl: /O1 /EHsc /MD
// STLport 4.5.3 random-access __distance reference expression.
// Target preceding RET boundary; native calculation subtracts referenced pointers
// and divides their byte difference by 40. Element contents and identity unknown.
struct Rva0053FCD7Element { unsigned char storage[40]; };
int Rva0053FCD7Distance(Rva0053FCD7Element *const &first,
                       Rva0053FCD7Element *const &last)
{
    return last - first;
}
