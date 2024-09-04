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

def calc(value_d,x):
    Zmax = Zeta(value_d,2) + mpfr(0.5)/gmpy2.exp10(value_d)
    dZmax = dZeta(value_d,2) + mpfr(0.5)/gmpy2.exp10(value_d)
    ddZmax = ddZeta(value_d,2) + mpfr(0.5)/gmpy2.exp10(value_d)
    M = dZmax
    L = dZmax*Zmax
    T = ddZmax*(Zmax**(mpfr(2))) + (dZmax**mpfr(2))*Zmax
    print("M:",M,"L:",L,"T:",T)
    
    n = mpz(1)
    while True:
        h = (x-mpfr(2))/n
        Delta = ((mpfr(1)+h*M+h*h*M*M/mpfr(2))**(n)-mpfr(1))*(L*M/mpfr(4)+T/mpfr(12))*(h**mpfr(3))/(h*M + h*h*M*M/mpfr(2))
        if Delta < mpfr(0.125)/gmpy2.exp10(value_d):
            break
        else :
            n = n*mpfr(2)
    
    n1 = n/mpfr(2)
    n2 = n
    while True:
        if n2 - n1 <= 1:
            n = gmpy2.ceil(n2)
            h = (x-mpfr(2))/n
            break
        nbar = (n1+n2)/mpfr(2)
        h = (x-mpfr(2))/nbar
        Delta = ((mpfr(1)+h*M+h*h*M*M/mpfr(2))**(n)-mpfr(1))*(L*M/mpfr(4)+T/mpfr(12))*(h**mpfr(3))/(h*M + h*h*M*M/mpfr(2))
        if Delta < mpfr(0.125)/gmpy2.exp10(value_d):
            n2 = nbar
        else:
            n1 = nbar
    
    d = mpfr(2)*gmpy2.exp10(value_d)*((mpfr(1)+h*M+h*h*M*M/mpfr(2))**(n)-mpfr(1))*(h+h*h*M/mpfr(2))/(h*M + h*h*M*M/mpfr(2))
    d = gmpy2.ceil(gmpy2.log10(d))
    delta = mpfr(4)*gmpy2.exp10(value_d)*((mpfr(1)+h*M+h*h*M*M/mpfr(2))**(n)-mpfr(1))*(mpfr(1)+h*M/mpfr(2))/(h*M + h*h*M*M/mpfr(2))
    m = gmpy2.ceil(gmpy2.log10(delta))
    print("n:",n,"h:",h,"d:",d,"m:",m)
    
    m = gmpy2.ceil(m*gmpy2.log2(mpfr(10)))
    gmpy2.get_context().precision = int(m)
    
    y = mpfr(2)
    for i in range(int(n)):
        ybar = y + h*Zeta(d,y)
        y = y + h*(Zeta(d,y)+Zeta(d,ybar))/mpfr(2)
        print(y)
    return y
    

if __name__ == '__main__':
    x = input('输入x:')
    x = mpfr(x)
    value_d = input('输入求解精度：')
    value_d = mpz(value_d)
    y = calc(value_d,x)
    print(y)
    exact_str = "{0:." + str(value_d) + "f}"
    y_output = exact_str.format(y)
    print("y:", y_output)