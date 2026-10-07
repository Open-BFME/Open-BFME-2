// ?rva000EB0E6@W3DTreeBuffer@@QAEXH@Z
// partial score=1.0 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// BFME W3DTreeBuffer indexed tree removal, retail 0x00733FD0 (341 bytes).
// The neighboring 0x00734790 update path passes its tree index here through
// ILT 0x0001512C.  Records are 0xE8 bytes and the count/dirty fields are at
// +0x44540/+0x44544, as witnessed by the adjacent tree-buffer bodies.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// BFME RenderObjClass: Delete_This is slot 0, Remove is slot +0x40 and the
// reference count is the first data word at +4.
class Rva000EB0E6RenderView
{
public:
	virtual void Delete_This(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void Remove(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};

class TerrainLogic { public: void rva00283CE7(unsigned key); };

extern TerrainLogic *TheTerrainLogic;


class W3DTreeBuffer
{
public:
	void rva000EB0E6(const Int index);

private:
	unsigned char m_pad0000[0x44540];
	Int m_numTrees;
	UnsignedByte m_anythingChanged;
};

// ?rva000EB0E6@W3DTreeBuffer@@QAEXH@Z
void W3DTreeBuffer::rva000EB0E6(const Int index)
{
	if (index < m_numTrees) {
		if (*(Int *)(reinterpret_cast<unsigned char *>(this) +
			index * 0xE8 + 0x600) >= 0) {
			if (*(UnsignedByte *)(reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x684) == 0 &&
				*(Int *)(reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x640) == 0) {
				if (*(Int *)(reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x688) == 1) {
					if (*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x69C) != 0)
						*(Int *)(reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x600) =
							*(Int *)(reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x690);
				} else {
					*(Int *)(reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x600) =
						*(Int *)(reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x68C);
				}

				if (*(Rva000EB0E6RenderView **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x698) != 0) {
					(*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x698))->Remove();
					if (*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x698) != 0) {
						(*(Rva000EB0E6RenderView **)(
							reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x698))->Release_Ref();
						*(Rva000EB0E6RenderView **)(
							reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x698) = 0;
					}
					*(volatile Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x698) = 0;
					_ReadWriteBarrier();
				}

				if (*(Rva000EB0E6RenderView **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x69C) != 0) {
					(*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x69C))->Remove();
					if (*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x69C) == 0)
						goto rva00733fd0_store_push;
					(*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x69C))->Release_Ref();
					*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x69C) = 0;
					goto rva00733fd0_store_push;
				} else {
                    TheTerrainLogic->rva00283CE7(*(UnsignedInt *)(reinterpret_cast<unsigned char *>(this) + index * 0xE8 + 0x618));
				}
				*(volatile Int *)(reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x688) = 0;
				*(volatile UnsignedByte *)(reinterpret_cast<unsigned char *>(this) +
					0x44544) = 1;
				return;
			}

			if (*(Rva000EB0E6RenderView **)(
				reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x698) != 0) {
				(*(Rva000EB0E6RenderView **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x698))->Remove();
				if (*(Rva000EB0E6RenderView **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x698) != 0) {
					(*(Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x698))->Release_Ref();
					*(volatile Rva000EB0E6RenderView **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x698) = 0;
					_ReadWriteBarrier();
				}
			}

			if (*(Rva000EB0E6RenderView **)(
				reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x69C) != 0) {
				(*(Rva000EB0E6RenderView **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x69C))->Remove();
				if (*(Rva000EB0E6RenderView **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x69C) == 0)
					goto rva00733fd0_finish;
				(*(Rva000EB0E6RenderView **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x69C))->Release_Ref();
			goto rva00733fd0_store_push;
			}

			goto rva00733fd0_finish;

	rva00733fd0_store_push:
			*(Rva000EB0E6RenderView **)(
				reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x69C) = 0;

	rva00733fd0_finish:
			*(Int *)(reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x688) = 0;
			m_anythingChanged = 1;
		}
	}
}
