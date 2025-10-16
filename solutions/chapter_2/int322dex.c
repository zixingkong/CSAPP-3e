#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 将十六进制字符串转换为32位补码的十进制整数
int hexToDecimal(char* hex) {
    // 移除可能的 0x 或 0X 前缀
    char* hexValue = hex;
    if (strlen(hex) >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
        hexValue = hex + 2;
    }
    
    // 将十六进制转换为无符号整数
    unsigned int value = 0;
    if (sscanf(hexValue, "%x", &value) != 1) {
        printf("错误：无效的十六进制格式\n");
        return 0;
    }
    
    // 32位补码直接转换为有符号整数
    return (int)value;
}

// 验证输入是否为有效的十六进制字符串
int isValidHex(char* str) {
    // 移除可能的 0x 前缀
    char* hexValue = str;
    if (strlen(str) >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        hexValue = str + 2;
    }
    
    int len = strlen(hexValue);
    if (len == 0 || len > 8) return 0; // 32位最多8个十六进制字符
    
    for (int i = 0; i < len; i++) {
        char c = hexValue[i];
        if (!((c >= '0' && c <= '9') || 
              (c >= 'a' && c <= 'f') || 
              (c >= 'A' && c <= 'F'))) {
            return 0;
        }
    }
    return 1;
}

// 显示32位二进制表示
void printBinary(unsigned int value) {
    printf("32位二进制表示：");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0 && i != 0) printf(" "); // 每4位加空格
    }
    printf("\n");
}

int main() {
    char hex[12]; // 足够存储32位十六进制输入
    
    printf("请输入32位十六进制补码（如 0x80000000）：");
    scanf("%11s", hex);
    
    // 验证输入
    if (!isValidHex(hex)) {
        printf("错误：请输入有效的十六进制数（最多8位）\n");
        return 1;
    }
    
    // 转换并输出结果
    int decimal = hexToDecimal(hex);
    unsigned int unsignedValue = (unsigned int)decimal;
    
    printf("十进制结果：%d\n", decimal);
    printf("十六进制输入：%s\n", hex);
    printBinary(unsignedValue);
    printf("符号位：%d (%s)\n", (unsignedValue >> 31) & 1, 
           (unsignedValue & 0x80000000) ? "负数" : "正数");
    
    return 0;
}
