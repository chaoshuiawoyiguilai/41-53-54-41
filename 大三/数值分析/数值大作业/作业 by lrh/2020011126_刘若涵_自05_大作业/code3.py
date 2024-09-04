import gmpy2
from gmpy2 import mpz
from gmpy2 import mpfr

def Zeta(value_d,x):
    Delta = (mpfr(4)/(x-mpfr(1)))*gmpy2.exp10(value_d)
    value_k = gmpy2.ceil(Delta**(mpfr(1)/(x-mpfr(1))))

    delta = gmpy2.log10(gmpy2.mpfr(2)*value_k)
    value_m = gmpy2.ceil(value_d + delta)
    value_m = gmpy2.ceil(value_m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(value_m)

    zeta = mpfr(0)
    z = mpfr(0)

    for i in range(1,int(value_k)+1):
        z = mpfr(1)/(mpfr(i)**(x))
        zeta = zeta + z
    return zeta

def f(t,x):
    return (t**(x-1)*gmpy2.exp(-t))

def gamma(value_d,x):
    N = max(mpfr(4)*(x**mpfr(2)),x*gmpy2.log(mpfr(6)*gmpy2.exp10(value_d)*x)-mpfr(1))
    N = gmpy2.ceil(N)
    
    n = mpfr(0.5)*(gmpy2.exp10(value_d)*(N**mpfr(3))*((x-1)*(x-2)*((x-3)**(x-3))/gmpy2.exp(x-3)+mpfr(2)*(x-1)*((x-2)**(x-2))/gmpy2.exp(x-2)+((x-1)**(x-1))/gmpy2.exp(x-1)))
    n = gmpy2.ceil(n**(mpfr(0.5)))
    
    h = N/n
    
    m = gmpy2.ceil(gmpy2.log10(gmpy2.mpfr(6)*n*gmpy2.exp10(value_d)))
    
    print("N:",N,"n:",n,"h:",h,"m:",m)
    
    m = gmpy2.ceil(m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(m)
    
    T = 0
    for i in range(int(n)):
        t = h*(f(mpfr(i)*h,x)+f(mpfr(i+1)*h,x))/mpfr(2)
        T = T + t
    
    return T

def calc(value_d,x):
    d = gmpy2.ceil(gmpy2.log10((Zeta(value_d,x)+gamma(value_d,x)+gmpy2.exp10(-value_d))*gmpy2.exp10(value_d)))
    print("d:",d)
    I = Zeta(d,x)*gamma(d,x)
    return I

if __name__ == '__main__':
    x = input('输入x:')
    x = mpfr(x)
    value_d = input('输入求解精度：')
    value_d = mpz(value_d)
    I = calc(value_d,x)
    print(I)
    exact_str = "{0:." + str(value_d) + "f}"
    I_output = exact_str.format(I)
    print("I:", I_output)