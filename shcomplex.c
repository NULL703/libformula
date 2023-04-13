/************************************************************************
公式库的复数计算函数和公式。
Copyright (C) 2022 NULL_703. All rights reserved.
Created on 2022.5.31  18:55
Created by NULL_703
Last change time on 2022.5.31  20:15
************************************************************************/
#include <shcomplex.h>

SHK_COMPLEX shk_clxaddsub(SHK_COMPLEX clx1, SHK_COMPLEX clx2, int calcMode)
{
    SHK_COMPLEX result = {0.0, 0.0};
    switch(calcMode)
    {
        case 0: {
            result.real = clx1.real + clx2.real;
            result.imag = clx1.imag + clx2.imag;
            break;
        }
        case 2: {
            result.real = clx1.real - clx2.real;
            result.imag = clx1.imag - clx2.imag;
            break;
        }
    }
    return result;
}

SHK_COMPLEX shk_clxadd(SHK_COMPLEX clx1, SHK_COMPLEX clx2)
{
    return shk_clxaddsub(clx1, clx2, 0);
}

SHK_COMPLEX shk_clxsub(SHK_COMPLEX clx1, SHK_COMPLEX clx2)
{
    return shk_clxaddsub(clx1, clx2, 1);
}

SHK_COMPLEX shk_clxmul(SHK_COMPLEX clx1, SHK_COMPLEX clx2)
{
    SHK_COMPLEX result = {0.0, 0.0};
    result.real = (clx1.real * clx2.real) - (clx1.imag * clx2.imag);
    result.imag = (clx1.imag * clx2.real) + (clx1.real * clx2.imag);
    return result;
}

SHK_COMPLEX shk_clxdiv(SHK_COMPLEX clx1, SHK_COMPLEX clx2)
{
    SHK_COMPLEX result = {0.0, 0.0};
    double temp = ((clx1.imag * clx2.real) - (clx1.real * clx2.imag));
    if(clx2.real == 0 && clx2.imag == 0)
        return result;
    result.real = ((clx1.real * clx2.real) + (clx1.imag * clx2.imag)) / temp;
    result.imag = ((clx1.imag * clx2.real) - (clx1.real * clx2.imag)) / temp;
    return result;
}