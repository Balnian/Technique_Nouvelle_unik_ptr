#include <iostream>
#include <string>

using namespace std;

template <class T>
class unik_ptr
{
   T* p;
public:
   unik_ptr()noexcept : p{} {}
   unik_ptr(T * q)noexcept : p{ q } {}
   unik_ptr(const unik_ptr&) = delete;
   ~unik_ptr() { delete p; }
   unik_ptr(unik_ptr&& autre) : p{ autre.p } { autre.p = {}; }
   void swap(unik_ptr& autre)
   {
      using std::swap;
      swap(p, autre.p);
   }
   unik_ptr& operator=(unik_ptr && autre)
   {
      swap(autre);
      return *this;
   }
   T& operator*()noexcept
   {
      return *p;
   }
   bool operator==(const unik_ptr& autre)
   {
      return p == autre;
   }

   bool operator!=(const unik_ptr& autre)const noexcept
   {
      return !(*this == autre);
   }

   T* operator->()noexcept
   {
      return p;
   }
   const T* operator->() const noexcept
   {
      return p;
   }
};

struct Noisy
{
   Noisy() { cout << "Noisy()" << endl; }
   ~Noisy() { cout << "~Noisy()" << endl; }
   Noisy(const Noisy &) { cout << "Noisy(const Noisy &)" << endl; }
   Noisy& operator =(const Noisy &) { cout << "Noisy& operator =(const Noisy &)" << endl; return *this; }
   Noisy(Noisy&&) { cout << "Noisy(Noisy&&)" << endl; }
   Noisy& operator=(Noisy&&) { cout << "Noisy& operator=(Noisy&&)" << endl; return *this; }

};



unik_ptr<Noisy> f(unik_ptr<Noisy> n)
{
   return n;
}

struct X
{
   X(int, float, string)
   {

   }
};
template<class T, class ... Args>
unik_ptr<T> make_unik(Args ... args)
{
   return unik_ptr<T>{new T{ args... }};
}
int main()
{
   /*unik_ptr<Noisy> p{ new Noisy };
   p = f(std::move(p));*/

   unik_ptr<X> p{ new X{3,3.14159f,"J'aime mon prof"} };
   auto q = make_unik<X>(3, 3.14159f, "J'aime mon prof");
}