/************************************************************************
公式库附属网络相关的专用函数。
Copyright (C) 2021-2022 NULL_703, All rights reserved.
Created on 2021.11.24  13:17
Created by NULL_703
Last change time on 2022.11.21  20:43
************************************************************************/
#include <network.h>
#include <functions.h>

const SHK_IPV4ADDR defaultIP = {0, 0, 0, 0};

SHK_IPV4CLASS shk_ipv4AddressType(SHK_IPV4ADDR ipv4Address)
{
    if(
        ipv4Address.IPV4_A > 0xff || ipv4Address.IPV4_B > 0xff || ipv4Address.IPV4_C > 0xff || 
        ipv4Address.IPV4_D > 0xff || ipv4Address.IPV4_A < 0x0 || ipv4Address.IPV4_B < 0x0 ||
        ipv4Address.IPV4_C < 0x0 || ipv4Address.IPV4_D < 0x0
    )
        return IPV4CLASS_INVALID;
    else if(ipv4Address.IPV4_A <= 127)
        return IPV4CLASS_A;
    else if(ipv4Address.IPV4_A > 127 && ipv4Address.IPV4_A <= 191)
        return IPV4CLASS_B;
    else if(ipv4Address.IPV4_A > 191 && ipv4Address.IPV4_A <= 223)
        return IPV4CLASS_C;
    else if(ipv4Address.IPV4_A > 223 && ipv4Address.IPV4_A <= 239)
        return IPV4CLASS_D;
    else if(ipv4Address.IPV4_A > 239 && ipv4Address.IPV4_A <= 247)
        return IPV4CLASS_E;
    else
        return IPV4CLASS_INVALID;
}

SHK_IPV4ADDR shk_netAddress(SHK_IPV4ADDR ipv4Address, SHK_IPV4ADDR subnetMask)
{
    SHK_IPV4ADDR result;
    result.IPV4_A = ipv4Address.IPV4_A & subnetMask.IPV4_A;
    result.IPV4_B = ipv4Address.IPV4_B & subnetMask.IPV4_B;
    result.IPV4_C = ipv4Address.IPV4_C & subnetMask.IPV4_C;
    result.IPV4_D = ipv4Address.IPV4_D & subnetMask.IPV4_D;
    return result;
}

SHK_IPV4ADDR shk_getSubnetmask(SHK_IPV4ADDR ipv4Address, int subnetNum)
{
    int n = 1, i = 0, ic = 0, offset = 0;
    SHK_IPV4ADDR result = {0xff, 0xff, 0xff, 0xff};
    char tempbin[0x18] = "000000000000000000000000";
    char binSection[9];
    int sectionValue[3];
    if(subnetNum <= 0) return defaultIP;
    if(subnetNum == 1) i = 0;
    else if(subnetNum == 2) i = 1;
    else
        while(n << ++i <= subnetNum);
    ic = i;
    switch(shk_ipv4AddressType(ipv4Address))
    {
        case IPV4CLASS_A: break;
        case IPV4CLASS_B: offset = 8; break;
        case IPV4CLASS_C: offset = 16; break;
        case IPV4CLASS_D:
        case IPV4CLASS_E:
        default: return defaultIP;
    }
    if(i > 0x18 - offset) return defaultIP;
    for(int j = 0; i > 0; j++, i--)
        tempbin[offset + j] = '1';
    for(int k = offset, l = 0, sectionNum = 0; k <= 0x18; k++, l++)
    {
        if(k % 8 == 0 && k != offset)
        {
            binSection[l] = '\0';
            sectionValue[sectionNum] = shk_BinToDec(binSection);
            sectionNum++;
            l = 0;
        }
        binSection[l] = tempbin[k];
    }
    ic = (offset / 8) + 1;    //根据IP地址的类型判断要取几个数，8个二进制位为一个IP字段
    switch(ic)
    {
        case 1: {
            result.IPV4_B = sectionValue[0];
            result.IPV4_C = sectionValue[1];
            result.IPV4_D = sectionValue[2];
            break;
        }
        case 2: {
            result.IPV4_C = sectionValue[0];
            result.IPV4_D = sectionValue[1];
            break;
        }
        case 3: result.IPV4_D = sectionValue[0]; break;
        default: return defaultIP;
    }
    return result;
}

SHK_IPV4ADDR shk_getNotypeIPmask(SHK_IPV4ADDR notypeIPAddress, int netprefix)
{
    int bitIndex = 0;    //变量IPV4bin的字符串索引
    int secIndex = 0;    //数组sectionValue的索引
    unsigned int sectionValue[4];
    SHK_IPV4ADDR result = {0xff, 0xff, 0xff, 0xff};
    char IPV4bin[0x21] = "00000000000000000000000000000000";    //IPV4地址0.0.0.0的二进制体现
    char IPaddressUnit[9];
    //IP地址合法性检验，如果该IP地址不能被分配类型则返回默认值（不能被分配类型的IP地址至少有一个字段的值不在规定范围内）
    if(shk_ipv4AddressType(notypeIPAddress) == IPV4CLASS_INVALID) return defaultIP;
    //网络前缀合法性检验
    if(netprefix > 32 || netprefix <= 0) return defaultIP;
    for(int i = 0; i < netprefix; i++)
        IPV4bin[i] = '1';
    while(bitIndex < 0x20)
    {
        //逐个字段进行赋值，每个字段将被分配8个二进制位，然后转换为十进制暂存在数组sectionValue中
        for(int k = 0; k < 8; k++, bitIndex++)
            IPaddressUnit[k] = IPV4bin[bitIndex];
        sectionValue[secIndex] = shk_BinToDec(IPaddressUnit);
        secIndex++;
    }
    //对IP地址的各字段进行赋值，并返回结果
    result.IPV4_A = sectionValue[0];
    result.IPV4_B = sectionValue[1];
    result.IPV4_C = sectionValue[2];
    result.IPV4_D = sectionValue[3];
    return result;
}