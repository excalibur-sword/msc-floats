#pragma warning(push)
#if !defined(__INTEL_COMPILER)
#pragma warning(disable : 4514) // unreferenced inline function
#pragma warning(disable : 4710) // function not inlined
#pragma warning(disable : 4820) // padding added
#if !defined(_DEBUG)
#pragma warning(disable : 4711) // function selected for automatic inline expansion
#endif
#endif
#include "double_float_80.h"
#include <emmintrin.h>
#include <stdio.h> // printf
#pragma warning(pop)

using f80 = float_80_t;
using df80 = double_float_80_t;

// Rump’s example
template <typename T> T Rump(void) {
  T a = 77617.0;
  T b = 33096.0;
  T b2 = b*b;
  T b4 = b2*b2;
  T b6 = b4*b2;
  T b8 = b4*b4;
  T a2 = a*a;
  T firstExpr = 11*a2*b2 - b6 - 121*b4 - 2;
  return 333.75*b6 + a2*firstExpr + 5.5*b8 + (a/(2.0*b));
}

template <typename T> void PrintRump(void);
template <> void PrintRump<double>(void) {
  printf("Rump<double>:          %+1.9e\n", Rump<double>());
}
template <> void PrintRump<f80>(void) {
  printf("Rump<float_80>:        %+1.9e\n", Rump<f80>().ToDouble());
}
template <> void PrintRump<df80>(void) {
  printf("Rump<double_float_80>: %+1.9e\n", Rump<df80>().Hi().ToDouble());
}

const double F64_EPS = 2.2204460492503131e-16;
const int SIN_TAYLOR_SZ = 15;

// Computes sin(x) using Taylor series. Assumes |x| <= pi/32.
f80 SinTaylor(const f80 &x) {
  if (x.IsZero()) return x;

  f80 x2 = -x*x, s = x, t = x;
  double threshold = 0.5*Abs(x).ToDouble()*F64_EPS;
  for (int i = 2; i < SIN_TAYLOR_SZ; i += 2) {
    t /= i*(i + 1);
    t *= x2;
    s += t;
    printf("%2d = %+1.14e\n", i + 1, s.ToDouble());
    if (threshold > Abs(t).ToDouble()) break;
  }
  return s;
}

df80 SinTaylor(const df80 &x) {
  if (x.IsZero()) return x;

  df80 x2 = -x*x, s = x, t = x;
  f80 threshold = 0.5*Abs(x.Hi())*F80_EPS;
  for (int i = 2; i < SIN_TAYLOR_SZ; i += 2) {
    t /= i*(i + 1);
    t *= x2;
    s += t;
    printf("%2d = %+1.14e %+1.14e\n", i + 1, s.Hi().ToDouble(), s.Lo().ToDouble());
    if (threshold > Abs(t.Hi())) break;
  }
  return s;
}

int main(void) {
  // clear flush-to-zero, and
  // clear denormals-are-zero mode
  _mm_setcsr(_mm_getcsr() & 0x7fbfu);

  // masks all fpu exceptions,
  // sets rounding to nearest, and
  // sets the precision to double extended, and
  // sets affine infinity
  fpu_set_cw(0x133fu);

  PrintRump<double>();
  PrintRump<f80>();
  PrintRump<df80>();

  const f80 x = F80_PI/40;
  printf("\nsinus<float_80> using Taylor series\n");
  SinTaylor(x);
  printf("\nsinus<double_float_80> using Taylor series\n");
  SinTaylor((df80)x);

  return 0;
}
