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

def dZeta(value_d,x):
    Delta = (mpfr(160)/((x-mpfr(1))*(mpfr(9)*x-mpfr(9))))*gmpy2.exp10(value_d)
    value_k = gmpy2.ceil(Delta**(mpfr(10)/(mpfr(9)*x-mpfr(9))))

    delta = gmpy2.log10(gmpy2.mpfr(2)*value_k)
    value_m = gmpy2.ceil(value_d + delta)
    value_m = gmpy2.ceil(value_m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(value_m)

    zeta = mpfr(0)
    z = mpfr(0)

    for i in range(1,int(value_k)+1):
        z = gmpy2.log(mpfr(i))/(mpfr(i)**(x))
        zeta = zeta + z   
    return zeta

def ddZeta(value_d,x):
    Delta = (mpfr(2560)/(((x-mpfr(1))**mpfr(2))*(mpfr(9)*x-mpfr(9))))*gmpy2.exp10(value_d)
    value_k = gmpy2.ceil(Delta**(mpfr(10)/(mpfr(9)*x-mpfr(9))))

    delta = gmpy2.log10(gmpy2.mpfr(2)*value_k)
    value_m = gmpy2.ceil(value_d + delta)
    value_m = gmpy2.ceil(value_m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(value_m)

    zeta = mpfr(0)
    z = mpfr(0)

    for i in range(1,int(value_k)+1):
        z = (gmpy2.log(mpfr(i))**mpfr(2))/(mpfr(i)**(x))
        zeta = zeta + z   
    return zeta

def fmax(value_d,u,v,a):
    return Zeta(value_d,u) + mpfr(0.5)/gmpy2.exp10(value_d) - a

def fmin(value_d,u,v,a):
    return Zeta(value_d,v) - mpfr(0.5)/gmpy2.exp10(value_d) - a

def dfmax(value_d,u,v,a):
    return dZeta(value_d,u) + mpfr(0.5)/gmpy2.exp10(value_d)

def dfmin(value_d,u,v,a):
    return dZeta(value_d,v) - mpfr(0.5)/gmpy2.exp10(value_d)

def ddfmax(value_d,u,v,a):
    return ddZeta(value_d,u) + mpfr(0.5)/gmpy2.exp10(value_d)

def ddfmin(value_d,u,v,a):
    return ddZeta(value_d,v) - mpfr(0.5)/gmpy2.exp10(value_d)

def phi(value_d,x,a):
    return x + (Zeta(value_d,x) - a)/dZeta(value_d,x)

def dphimax(value_d,u,v,a):
    return max(fmax(value_d,u,v,a),-fmin(value_d,u,v,a))*ddfmax(value_d,u,v,a)/(dfmin(value_d,u,v,a)**mpfr(2))


def calc(value_d,a):
    u = (a+mpfr(1))/a
    v = a/(a-mpfr(1))
    while True:
        if v - u <= mpfr(0.01):
            break
        w = (u+v)/mpfr(2)
        if Zeta(value_d,w) > a:
            u = w
        else:
            v = w
   
    L = dphimax(value_d,u,v,a)
    n = gmpy2.ceil(gmpy2.log(mpfr(25)/gmpy2.exp10(value_d))/gmpy2.log(L))
    A = mpfr(1) + dfmax(value_d,u,v,a)/dfmin(value_d,u,v,a) + max(fmax(value_d,u,v,a),-fmin(value_d,u,v,a))*ddfmax(value_d,u,v,a)/(dfmin(value_d,u,v,a)**mpfr(2))
    B = mpfr(1)/dfmin(value_d,u,v,a) + max(fmax(value_d,u,v,a),-fmin(value_d,u,v,a))/(dfmin(value_d,u,v,a)**mpfr(2))
    d = gmpy2.ceil(gmpy2.log10(mpfr(4)*gmpy2.exp10(value_d)*B*(mpfr(1)-A**mpfr(n))/(mpfr(1)-A)))
    m = gmpy2.ceil(gmpy2.log10(mpfr(4)*gmpy2.exp10(value_d)*(mpfr(1)-A**mpfr(n+1))/(mpfr(1)-A)))
    print("n:",n,"d:",d,"m:",m)
    m = gmpy2.ceil(m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(m)
    
    x = u
    for i in range(int(n)):
        x = phi(d,x,a)
    return x



if __name__ == '__main__':
    a = input('输入a:')
    a = mpfr(a)
    value_d = input('输入求解精度：')
    value_d = mpz(value_d)
    x = calc(value_d,a)
    print(x)
    exact_str = "{0:." + str(value_d) + "f}"
    x_output = exact_str.format(x)
    print("x:", x_output)