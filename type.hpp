#ifndef _TYPE_HPP_
#define _TYPE_HPP_

using uint = unsigned int;
using uchar = unsigned char;

uint sext(uint data, int index) {
    //将最高位index符号位扩展
    if (data >> index & 1) {
        //扩展为32位
        data = data | (0xffffffff >> index << index);
    }
    return data;
}
uint last_zero(uint data) {
    //将最低位置0
    return data & ~1;
}

uint fetch(char *tmp) {
    uint res = 0;
    int temp = 0;
    for (int i = 0; tmp[i] != '\n' && tmp[i] != '\0'; ++i) {
        if (tmp[i] >= '0' && tmp[i] <= '9')
            temp = tmp[i] - '0';
        else
            temp = tmp[i] - 'A' + 10;
        res = (res << 4) + temp;
    }
    return res;
}
#endif
