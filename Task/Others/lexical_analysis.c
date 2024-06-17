#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义符号表和TOKEN代码
enum {
    //将IDENTIFIER的枚举值赋值为0后，编译器会自动按照默认规则为后面的枚举值赋值，也就是从IDENTIFIER的枚举值开始，递增1。
    IDENTIFIER = 0,     //变量或函数名
    NUMBER,             //数字常量
    OPERATOR,           //算术、逻辑、位运算符
    SEPARATOR,          //分号、括号、花括号等分隔符
    KEYWORD             //C语言关键字
};

// 定义最大标识符长度和关键字数量
#define MAX_IDENTIFIER_LENGTH 100
#define KEYWORD_COUNT 6

// 关键字列表
const char* keywords[KEYWORD_COUNT] = {
    "int", "float", "if", "else", "for", "while"
};

// 判断是否为关键字
int isKeyword(const char* identifier) {
    int i;
    for (i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(identifier, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// 词法分析函数
void lexicalAnalysis(const char* code) {
    int i = 0;
    while (code[i] != '\0') {
        // 跳过空格和换行符
        if (code[i] == ' ' || code[i] == '\n') {
            i++;
            continue;
        }
        
        // 标识符或关键字
        if ((code[i] >= 'a' && code[i] <= 'z') || (code[i] >= 'A' && code[i] <= 'Z') || code[i] == '_') {
            char identifier[MAX_IDENTIFIER_LENGTH];
            int j = 0;
            
            while ((code[i] >= 'a' && code[i] <= 'z') || (code[i] >= 'A' && code[i] <= 'Z') || (code[i] >= '0' && code[i] <= '9') || code[i] == '_') {
                identifier[j++] = code[i++];
            }
            
            identifier[j] = '\0';
            
            if (isKeyword(identifier)) {
                printf("Token: %s, Type: KEYWORD\n", identifier);
            } else {
                printf("Token: %s, Type: IDENTIFIER\n", identifier);
            }
            
            continue;
        }
        
        // 数字常量
        if (code[i] >= '0' && code[i] <= '9') {
            char number[MAX_IDENTIFIER_LENGTH];
            int j = 0;
            
            while (code[i] >= '0' && code[i] <= '9') {
                number[j++] = code[i++];
            }
            
            number[j] = '\0';
            
            printf("Token: %s, Type: NUMBER\n", number);
            
            continue;
        }
        
        // 操作符
        if (code[i] == '+' || code[i] == '-' || code[i] == '*' || code[i] == '/') {
            printf("Token: %c, Type: OPERATOR\n", code[i++]);
            continue;
        }
        
        // 分隔符
        if (code[i] == ';' || code[i] == '(' || code[i] == ')' || code[i] == '{' || code[i] == '}') {
            printf("Token: %c, Type: SEPARATOR\n", code[i++]);
            continue;
        }
        
        // 未知类型
        printf("Invalid token: %c\n", code[i++]);
    }
}

int main() {

    //下面是五个测试用例，可以分别解开注释运行代码进行词法分析。

    // //测试用例01：验证词法分析是否正常运行
    // const char* code = "int main() {\
    //                     int a = 10;\
    //                     float b = 3.14;\
    //                     if (a > b) {\
    //                         printf(\"a is greater than b\");\
    //                     } else {\
    //                         printf(\"b is greater than a\");\
    //                     }\
    //                     return 0;\
    //                 }\
    //                 ";

    // //测试用例02：测试不同类型的标识符和关键字
    // const char* code = "int foo = 5;\
    //                     float bar = 3.14;\
    //                     if (foo > bar) {\
    //                         printf(\"foo is greater than bar\");\
    //                     } else {\
    //                         printf(\"bar is greater than foo\");\
    //                     }\
    //                     ";

    // //测试用例03：测试运算符和分隔符
    // const char* code = "int a = 5;\
    //                     int b = 10;\
    //                     int c = a + b;\
    //                     printf(\"The sum of a and b is %d\", c);\
    //                     ";

    // //测试用例04：测试多层嵌套的控制语句
    // const char* code = "for (int i = 0; i < 10; i++) {\
    //                         if (i % 2 == 0) {\
    //                             printf(\"%d is an even number\n\", i);\
    //                         } else {\
    //                             printf(\"%d is an odd number\n\", i);\
    //                         }\
    //                     }\
    //                     ";

    //测试用例05：测试不同类型的分隔符和字符串常量
    const char* code = "int main() {\
                        char str[100] = \"Hello, World!\";\
                        printf(\"%s\n\", str);\
                        return 0;\
                    }\
                    ";

    lexicalAnalysis(code);
    
    return 0;
}
