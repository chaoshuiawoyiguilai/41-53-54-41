import gmpy2
from gmpy2 import mpz
from gmpy2 import mpfr

def Zeta2(value_d):
    Delta = mpfr(4)*gmpy2.exp10(value_d)
    value_k = gmpy2.ceil(Delta)
    print(value_k)

    delta = gmpy2.log10(gmpy2.mpfr(2)*value_k)
    value_m = gmpy2.ceil(value_d + delta)
    print(value_m)
    value_m = gmpy2.ceil(value_m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(value_m)

    zeta = mpfr(0)
    z = mpfr(0)

    for i in range(1,int(value_k)+1):
        z = mpfr(1)/(mpfr(i)**mpfr(2))
        zeta = zeta+z
    
    return zeta

def Zeta8(value_d):
    Delta = (mpfr(4)/mpfr(7))*gmpy2.exp10(value_d)
    Delta = Delta**(mpfr(1)/mpfr(7))
    value_k = gmpy2.ceil(Delta)
    print(value_k)

    delta = gmpy2.log10(gmpy2.mpfr(2)*value_k)
    value_m = gmpy2.ceil(value_d + delta)
    print(value_m)
    value_m = gmpy2.ceil(value_m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(value_m)

    zeta = mpfr(0)
    z = mpfr(0)

    for i in range(1,int(value_k)+1):
        z = mpfr(1)/(mpfr(i)**mpfr(8))
        zeta = zeta + z
    
    return zeta

if __name__ == '__main__':
    value_d = input('输入求解精度：')
    value_d = mpz(value_d)

    zeta = Zeta8(value_d)
    exact_str = "{0:." + str(value_d) + "f}"
    zeta_output = exact_str.format(zeta)
    print("zeta:", zeta_output)
    pi = (mpfr(9450)*zeta)**(mpfr(1)/mpfr(8))
    pi_output = exact_str.format(pi)
    print("pi:", pi_output)