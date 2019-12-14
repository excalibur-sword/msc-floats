option casemap: none
option proc: private
option prologue: none
option epilogue: none

.const
.data
.data?
.code

; void DoubleToLongDouble(
;  float_80_t &ld, const double &d
; );
; double to long double
;
align 8
DoubleToLongDouble proc public
  fnclex
  fld qword ptr [rdx]
  fstp tbyte ptr [rcx]
  ret
DoubleToLongDouble endp
;
; double LongDoubleToDouble(
;  const float_80_t &ld, double &d
; );
; long double to double
;
align 8
LongDoubleToDouble proc public
  fld tbyte ptr [rcx]
  fstp qword ptr [rdx]
  ret
LongDoubleToDouble endp
;
; void IntegerToLongDouble(
;  float_80_t &ld, const int &i
; );
; integer to long double
;
align 8
IntegerToLongDouble proc public
  fnclex
  fild dword ptr [rdx]
  fstp tbyte ptr [rcx]
  ret
IntegerToLongDouble endp
;
; void LongDoubleAdd(
;  float_80_t &ld, const float_80_t &v
; );
; long double += long double
;
align 8
LongDoubleAdd proc public
  fld tbyte ptr [rcx]
  fld tbyte ptr [rdx]
  faddp st(1), st(0)
  fstp tbyte ptr [rcx]
  ret
LongDoubleAdd endp
;
; void LongDoubleSubtract(
;  float_80_t &ld, const float_80_t &v
; );
; long double -= long double
;
align 8
LongDoubleSubtract proc public
  fld tbyte ptr [rcx]
  fld tbyte ptr [rdx]
  fsubp st(1), st(0)
  fstp tbyte ptr [rcx]
  ret
LongDoubleSubtract endp
;
; void LongDoubleMultiply(
;  float_80_t &ld, const float_80_t &v
; );
; long double *= long double
;
align 8
LongDoubleMultiply proc public
  fld tbyte ptr [rcx]
  fld tbyte ptr [rdx]
  fmulp st(1), st(0)
  fstp tbyte ptr [rcx]
  ret
LongDoubleMultiply endp
;
; void LongDoubleDivide(
;  float_80_t &ld, const float_80_t &v
; );
; long double /= long double
;
align 8
LongDoubleDivide proc public
  fld tbyte ptr [rcx]
  fld tbyte ptr [rdx]
  fdivp st(1), st(0)
  fstp tbyte ptr [rcx]
  ret
LongDoubleDivide endp
;
; void LongDoubleRcp(
;  float_80_t &f, const float_80_t &x
; );
; long double = 1/long double
;
align 8
LongDoubleRcp proc public
  fld1
  fld tbyte ptr [rdx]
  fdivp st(1), st(0)
  fstp tbyte ptr [rcx]
  ret
LongDoubleRcp endp
;
; void LongDoubleSqrt(
;  float_80_t &f, const float_80_t &x
; );
; long double = sqrt(long double)
;
align 8
LongDoubleSqrt proc public
  fld tbyte ptr [rdx]
  fsqrt
  fstp tbyte ptr [rcx]
  ret
LongDoubleSqrt endp
;
; void LongDoubleSin(
;  float_80_t &f, const float_80_t &x
; );
; long double = sin(long double)
;
align 8
LongDoubleSin proc public
  fld tbyte ptr [rdx]
  fsin
  fstp tbyte ptr [rcx]
  ret
LongDoubleSin endp
;
; void LongDoubleCos(
;  float_80_t &f, const float_80_t &x
; );
; long double = cos(long double)
;
align 8
LongDoubleCos proc public
  fld tbyte ptr [rdx]
  fcos
  fstp tbyte ptr [rcx]
  ret
LongDoubleCos endp
;
; void LongDoubleLn(
;  float_80_t &f, const float_80_t &x
; );
; long double = ln(long double)
;
align 8
LongDoubleLn proc public
  fldln2
  fld tbyte ptr [rdx]
  fyl2x
  fstp tbyte ptr [rcx]
  ret
LongDoubleLn endp
;
; void LongDoubleLog2(
;  float_80_t &f, const float_80_t &x
; );
; long double = log2(long double)
;
align 8
LongDoubleLog2 proc public
  fld1
  fld tbyte ptr [rdx]
  fyl2x
  fstp tbyte ptr [rcx]
  ret
LongDoubleLog2 endp
;
; void LongDoubleLog10(
;  float_80_t &f, const float_80_t &x
; );
; long double = log10(long double)
;
align 8
LongDoubleLog10 proc public
  fldlg2
  fld tbyte ptr [rdx]
  fyl2x
  fstp tbyte ptr [rcx]
  ret
LongDoubleLog10 endp
;
; int LongDoubleCompare(
;  const float_80_t &a,
;  const float_80_t &b
; );
; long double >, ==, < long double
;
align 8
LongDoubleCompare proc public
  or eax, -1
  fnclex
  fld tbyte ptr [rcx]
  fld tbyte ptr [rdx]
  xor ecx, ecx
  xor edx, edx
  inc ecx
  fcomip st(0), st(1)
  fstp st(0)
  cmovc eax, ecx
  cmovz eax, edx
  ret
LongDoubleCompare endp
;
; void fpu_get_cw(unsigned short int &cw);
; store fpu Control Word
;
align 8
fpu_get_cw proc public
  fnstcw word ptr [rcx]
  ret
fpu_get_cw endp
;
; void fpu_set_cw(unsigned short int &cw);
; load fpu Control Word
;
align 8
fpu_set_cw proc public
  fnclex
  fldcw word ptr [rcx]
  ret
fpu_set_cw endp
end
