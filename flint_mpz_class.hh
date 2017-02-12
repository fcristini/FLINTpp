// a lot of help for operators in 
// http://en.cppreference.com/w/cpp/language/operators

#ifndef flint_mpz_class_hh
#define flint_mpz_class_hh 1

///#include <stdexcept>
#include <string>
#include "flint/fmpz.h"

#define __PPLITE_CONSTANT(X) __builtin_constant_p(X)
#define __PPLITE_CONSTANT_TRUE(X) (__PPLITE_CONSTANT(X) && (X))
/*
#define __PPLITE_DECLARE_COMPOUND_OPERATOR(fun)    \
  flint_mpz_class & fun(const flint_mpz_class &);  \
  flint_mpz_class & fun(signed char);              \
  flint_mpz_class & fun(unsigned char);            \
  flint_mpz_class & fun(signed int);               \
  flint_mpz_class & fun(unsigned int);             \
  flint_mpz_class & fun(signed short int);         \
  flint_mpz_class & fun(unsigned short int);       \
  flint_mpz_class & fun(signed long int);          \
  flint_mpz_class & fun(unsigned long int);        \
  flint_mpz_class & fun(float);                    \
  flint_mpz_class & fun(double);

#define __PPLITE_DECLARE_INCREMENT_OPERATOR(fun) \
  inline flint_mpz_class & fun();                \
  inline flint_mpz_class fun(int);

#define __PPLITE_DECLARE_COMPARISON_OPERATOR(fun)    \
  friend bool fun(const flint_mpz_class &, const flint_mpz_class &);  \
  friend bool fun(const flint_mpz_class &, signed char);              \
  friend bool fun(const flint_mpz_class &, unsigned char);            \
  friend bool fun(const flint_mpz_class &, signed int);               \
  friend bool fun(const flint_mpz_class &, unsigned int);             \
  friend bool fun(const flint_mpz_class &, signed short int);         \
  friend bool fun(const flint_mpz_class &, unsigned short int);       \
  friend bool fun(const flint_mpz_class &, signed long int);          \
  friend bool fun(const flint_mpz_class &, unsigned long int);        \
  friend bool fun(const flint_mpz_class &, float);                    \
  friend bool fun(const flint_mpz_class &, double);
*/

class flint_mpz_class
{
public:
  // Costruttori e distruttori
  flint_mpz_class() {
    fmpz_init(mp);
  }
  flint_mpz_class(int l) { 
    init_si(l);
  }
  flint_mpz_class(signed long l) { 
    init_si(l);
  }
  flint_mpz_class(unsigned long l) { 
    init_ui(l);
  }
  flint_mpz_class(double d) { 
    init_d(d);
  }
  flint_mpz_class(const flint_mpz_class &z) { 
    fmpz_init(mp);
    fmpz_set(mp, z.mp);
  }
#if __cplusplus >= 201103L
  flint_mpz_class(flint_mpz_class &&z) {
    *mp = *z.mp;
    fmpz_init(z.mp);
  }
#endif

  explicit flint_mpz_class(const char *s, int base = 0)
  {
    fmpz_init(mp);
    if (set_str(s, base) != 0) {
      fmpz_clear (mp);
      ///throw std::invalid_argument ("fmpz_set_str");
    }
  }
  explicit flint_mpz_class(const std::string &s, int base = 0)
  {
    fmpz_init(mp);
    if (set_str(s.c_str(), base) != 0) {
      fmpz_clear (mp);
      ///throw std::invalid_argument ("fmpz_set_str");
    }
  }

  ~flint_mpz_class() { fmpz_clear(mp); }

public:
  fmpz_t mp;

  // Inizializzazione
  void init_ui(unsigned long l) {
      fmpz_init(mp);
      fmpz_set_ui(mp, l);
  }
  void init_si(signed long l) {
    if (__PPLITE_CONSTANT_TRUE(l >= 0)) {
      init_ui(l);
    }
    else if (__PPLITE_CONSTANT_TRUE(l <= 0)) {
      init_ui(-static_cast<unsigned long>(l));
      fmpz_neg(mp, mp);
    }
    else {
      fmpz_init(mp);
      fmpz_set_si(mp, l);
    }
  }
  void init_d (double d) {
    fmpz_init (mp);
    fmpz_set_d (mp, d);
  }

  // Assegnamento
  void assign_ui(unsigned long l) {
      fmpz_set_ui(mp, l);
  }
  void assign_si(signed long l) {
    if (__PPLITE_CONSTANT_TRUE(l >= 0)) {
      assign_ui(l);
    }
    else if (__PPLITE_CONSTANT_TRUE(l <= 0)) {
      assign_ui(-static_cast<unsigned long>(l));
      fmpz_neg(mp, mp);
    }
    else {
      fmpz_set_si(mp, l);
    }
  }
  void assign_d (double d) {
    fmpz_set_d (mp, d);
  }

public:
  void swap(flint_mpz_class& z) { std::swap(*mp, *z.mp); }

  // assignment operators
  flint_mpz_class & operator=(const flint_mpz_class &z) { fmpz_set(mp, z.mp); return *this; }
#if __cplusplus >= 201103L
  flint_mpz_class & operator=(flint_mpz_class &&z) noexcept { swap(z); return *this; }
#endif
  flint_mpz_class & operator=(int l) { assign_si(l); return *this; }
  flint_mpz_class & operator=(signed long l) { assign_si(l); return *this; }
  flint_mpz_class & operator=(unsigned long l) { assign_ui(l); return *this; }
  flint_mpz_class & operator=(double d) { assign_d(d); return *this; }
  flint_mpz_class & operator=(const char *s) {
    if (set_str (s, 0) != 0) {
      ///throw std::invalid_argument ("fmpz_set_str");
    }
    return *this;
  }
  flint_mpz_class & operator=(const std::string &s) {
    if (set_str(s.c_str(), 0) != 0) {
      ///throw std::invalid_argument ("fmpz_set_str");
    }
    return *this;
  }

  // string input/output functions
  int set_str(const char *s, int base)
  { return fmpz_set_str(mp, s, base); }
  int set_str(const std::string &s, int base)
  { return fmpz_set_str(mp, s.c_str(), base); }
  std::string get_str(int base = 10) const
  {
    ///__gmp_alloc_cstring temp(fmpz_get_str(0, base, mp));
    return std::string(fmpz_get_str(0, base, mp));
  }

/*
  // conversion functions
  mpz_srcptr __get_mp() const { return mp; }
  mpz_ptr __get_mp() { return mp; }
  mpz_srcptr get_mpz_t() const { return mp; }
  mpz_ptr get_mpz_t() { return mp; }
*/
  signed long int get_si() const { return fmpz_get_si(mp); }
  unsigned long int get_ui() const { return fmpz_get_ui(mp); }
  double get_d() const { return fmpz_get_d(mp); }

  // bool fits_schar_p() const { return fmpz_fits_schar_p(mp); }
  // bool fits_uchar_p() const { return fmpz_fits_uchar_p(mp); }
  //bool fits_sint_p() const { return fmpz_fits_sint(mp); }
  //bool fits_uint_p() const { return fmpz_fits_uint(mp); }
  //bool fits_sshort_p() const { return fmpz_fits_sshort(mp); }
  //bool fits_ushort_p() const { return fmpz_fits_ushort(mp); }
  //bool fits_slong_p() const { return fmpz_fits_slong(mp); }
  //bool fits_ulong_p() const { return fmpz_fits_ulong(mp); }
  // bool fits_float_p() const { return fmpz_fits_float_p(mp); }
  // bool fits_double_p() const { return fmpz_fits_double_p(mp); }
  // bool fits_ldouble_p() const { return fmpz_fits_ldouble_p(mp); }
/*
#if __GMPXX_USE_CXX11
  explicit operator bool() const { return mp->_mp_size != 0; }
#endif*/

  // Comparison
  inline bool operator==(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) == 0; }
  inline bool operator==(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) == 0; }
  inline bool operator==(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) == 0; }
  inline bool operator==(int rhs)                    const { return fmpz_cmp_si(mp,rhs) == 0; }
  inline bool operator!=(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) != 0; }
  inline bool operator!=(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) != 0; }
  inline bool operator!=(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) != 0; }
  inline bool operator!=(int rhs)                    const { return fmpz_cmp_si(mp,rhs) != 0; }
  inline bool operator< (const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) <  0; }
  inline bool operator< (unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) <  0; }
  inline bool operator< (signed long rhs)            const { return fmpz_cmp_si(mp,rhs) <  0; }
  inline bool operator< (int rhs)                    const { return fmpz_cmp_si(mp,rhs) <  0; }
  inline bool operator> (const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) >  0; }
  inline bool operator> (unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) >  0; }
  inline bool operator> (signed long rhs)            const { return fmpz_cmp_si(mp,rhs) >  0; }
  inline bool operator> (int rhs)                    const { return fmpz_cmp_si(mp,rhs) >  0; }
  inline bool operator<=(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) <= 0; }
  inline bool operator<=(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) <= 0; }
  inline bool operator<=(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) <= 0; }
  inline bool operator<=(int rhs)                    const { return fmpz_cmp_si(mp,rhs) <= 0; }
  inline bool operator>=(const flint_mpz_class& rhs) const { return fmpz_cmp   (mp,rhs.mp) >= 0; }
  inline bool operator>=(unsigned long rhs)          const { return fmpz_cmp_ui(mp,rhs) >= 0; }
  inline bool operator>=(signed long rhs)            const { return fmpz_cmp_si(mp,rhs) >= 0; }
  inline bool operator>=(int rhs)                    const { return fmpz_cmp_si(mp,rhs) >= 0; }

  // Arithmetic
  flint_mpz_class & operator+=(const flint_mpz_class& rhs) { *this = *this + rhs; return *this; }
  friend flint_mpz_class operator+(flint_mpz_class lhs, const flint_mpz_class& rhs) {
    flint_mpz_class ret;
    fmpz_add(ret.mp, lhs.mp, rhs.mp);
    return ret;
  }

  inline flint_mpz_class & operator-=(const flint_mpz_class& rhs) { *this = *this - rhs; return *this; }
  friend flint_mpz_class operator-(flint_mpz_class lhs, const flint_mpz_class& rhs) {
    flint_mpz_class ret;
    fmpz_sub(ret.mp, lhs.mp, rhs.mp);
    return ret;
  }
  
  inline flint_mpz_class & operator*=(const flint_mpz_class& rhs) { *this = *this * rhs; return *this; }
  friend flint_mpz_class operator*(flint_mpz_class lhs, const flint_mpz_class& rhs) {
    flint_mpz_class ret;
    fmpz_mul(ret.mp, lhs.mp, rhs.mp);
    return ret;
  }
  
  inline flint_mpz_class & operator/=(const flint_mpz_class& rhs) { *this = *this / rhs; return *this; }
  friend flint_mpz_class operator/(flint_mpz_class lhs, const flint_mpz_class& rhs) {
    flint_mpz_class ret;
    fmpz_cdiv_q(ret.mp, lhs.mp, rhs.mp);
    // debug
    //////std::cout << "Asked to divide " << lhs.get_str() << " by " << rhs.get_str() << "; ";
    //////std::cout << "Got " << ret.get_str() <<   std::endl;

    return ret;
  }

};

#endif // !defined(flint_mpz_class_hh)
