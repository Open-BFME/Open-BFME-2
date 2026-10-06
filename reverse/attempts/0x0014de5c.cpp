// ?rva0014DE5C@@YGXPAM@Z
// partial score=0.7 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /arch:SSE
// VA 0x00DEDBF0 16-float source matrix (straight transpose, no identity).
float g_matrixSrc14DE5C[16];
void __stdcall rva0014DE5C(float *out) {
  volatile float tmp[16];
  float dummy = 1.0f;
  float a0 = g_matrixSrc14DE5C[2];
  float a1 = g_matrixSrc14DE5C[4];
  float a2 = g_matrixSrc14DE5C[8];
  float a3 = g_matrixSrc14DE5C[12];
  float a4 = g_matrixSrc14DE5C[1];
  float a5 = g_matrixSrc14DE5C[5];
  float a6 = g_matrixSrc14DE5C[9];
  float a7 = g_matrixSrc14DE5C[13];
  (void)dummy;
  tmp[0] = a0;
  out[1] = a1;
  out[2] = a2;
  out[3] = a3;
  out[4] = a4;
  out[5] = a5;
  out[6] = a6;
  out[7] = a7;
  float b0 = g_matrixSrc14DE5C[6];
  float b1 = g_matrixSrc14DE5C[10];
  float b2 = g_matrixSrc14DE5C[14];
  float b3 = g_matrixSrc14DE5C[3];
  float b4 = g_matrixSrc14DE5C[7];
  float b5 = g_matrixSrc14DE5C[11];
  float b6 = g_matrixSrc14DE5C[15];
  float b7 = g_matrixSrc14DE5C[0];
  tmp[1] = b0;
  tmp[2] = b1;
  tmp[3] = b2;
  tmp[4] = b3;
  tmp[5] = b4;
  tmp[6] = b5;
  tmp[7] = b6;
  out[0] = b7;
  out[8] = tmp[0];
  out[9] = tmp[1];
  out[10] = tmp[2];
  out[11] = tmp[3];
  out[12] = tmp[4];
  out[13] = tmp[5];
  out[14] = tmp[6];
  out[15] = tmp[7];
}
