#include <stdio.h>  
#include <stdbool.h>  
#include <assert.h>  
#include <stdlib.h>  
#include <string.h> // memset   

#define TDEBUG
  
#define CHECK_RESULT(b) \
{ \
        if (b) \
            printf("%-30s passed.\n", __func__); \
        else \
        { \
            printf("%-30s failed, exit now.\n", __func__); \
            exit(-1); \
        } \
} 
  
#ifdef TDEBUG  
    #define tprint(x...) printf(x)  
#else  
    #define tprint(x...)  
#endif  
   
void reverse_str(char *str)  
{  
    if (str == NULL) return;      
    int i = 0, j = 0;  
    char c;  
    j = strlen(str)-1;  
      
    for (i=0; i<j; i++, j--)  
        c = str[i], str[i] = str[j], str[j] = c;  
    return;       
}  
  
void reverse_str2(char *str)  
{  
    if (str == NULL) return;  
    char *p, *q, t;  
    p = str;  
    while (*str != '\0')  
        str++;  
    q = str - 1;  
    while (p < q)  
    {  
        t = *p, *p = *q, *q = t;  
        p++, q--;  
    }  
    return;  
}  
  
void test_reverse_str(void)  
{  
    char a[11] = "0123456789";  
    char *p, *q;  
    p = a;  
    tprint("before: %s\n", a);  
    reverse_str(a);  
    reverse_str2(a);  
    tprint("after:  %s\n", a);  
    q = a;  
    CHECK_RESULT(!strncmp(p, q, 11));  
    return;   
}  
  
int check_bit_in_byte(unsigned char byte)  
{  
    int i, j = 0;  
    for (i=0; i<8; i++)  
        j += ((byte >> i) & 0x01);  
  
    return j;     
}  
  
bool test_check_bit_in_byte(void)  
{  
    int i;  
    i = check_bit_in_byte(0b10101111);  
    tprint("1 in byte is: %d\n", i);  
    CHECK_RESULT(i == 6);  
    i = check_bit_in_byte(0b10101010);  
    tprint("1 in byte is: %d\n", i);  
    CHECK_RESULT(i == 4);  
  
    return true;          
}  
  
char *str_copy(char *s, char *t)  
{  
    assert (s != NULL && t != NULL);  
    char *p = t;  
      
    while ((*(t++) = *(s++)) != '\0')  
        NULL;  
    return (p);  
}

/* sample code from `man strncpy` */
char *str_ncopy(char *s, char *t, size_t n) 
{
    assert (s != NULL && t != NULL);
    size_t i;
    for (i=0; i<n && s[i] != '\0'; i++) 
        t[i] = s[i];
    for (; i<n; i++)
        t[i] = '\0';
    return (t);
}  
  
void test_str_copy(void)  
{  
    char a[10] = "abcd";  
    char b[10];  
    char c[10];  
    assert(1);  
    str_copy(a, b);  
    str_copy(a, c);  
    CHECK_RESULT(!strncmp(a, b, 5));          
    CHECK_RESULT(!strncmp(a, c, 5));          
    tprint("src: %s, dest: %s, dest: %s\n", a, b, c);  
}  
  
char *str_cat(char *s, char *t)  
{  
    assert(s != NULL && t != NULL);  
    char *p = t;  
      
    while (*t != '\0') t++;  
    while ((*t++ = *s++) != '\0') NULL;  
  
    return (p);       
}  
  
void test_str_cat(void)  
{  
    char a[10] = "1234";  
    char b[16] = "abcd";  
    str_cat(a, b);  
    CHECK_RESULT(!strncmp(b, "abcd1234", 9));  
    tprint("%s\n",str_cat(a, b));  
}  
  
int str_len(char *s)  
{  
    assert(s != NULL);  
    int i = 0;  
    while (*s != '\0') s++, i++;  
  
    return (i);  
}  
  
void test_str_len(void)  
{  
    char a[10] = "abcd";  
    CHECK_RESULT(strlen(a) == 4);     
    tprint("len: %d\n", str_len(a));  
}  
  
void mem_copy(void *s, void *t, int len)  
{  
    assert( s != NULL && t != NULL && len > 0); // do remember judging "len".      
    unsigned char *ps = (unsigned char *)s;  
    unsigned char *pt = (unsigned char *)t;  
  
    int i;  
    for (i=0; i<len; i++)  
        *pt++ = *ps++;    
}  
  
// should not overlap.  
void test_mem_copy(void)  
{  
    long long unsigned int a = 0x1122334455667788llu;  
    long long unsigned int *b = malloc(sizeof(long long unsigned int) * 3);  
    memset(b, 0, sizeof(long long unsigned int));  
    mem_copy(&a, b, 8);  
    CHECK_RESULT(a == *b);     
    tprint("mem_copy: %16llx\n", *b);  
  
    free(b);  
}  
  
// big endian: low address, high value.  
// https://www.cs.umd.edu/class/sum2003/cmsc311/Notes/Data/endian.html
void test_endian(void)  
{  
    unsigned int a = 0x01030400;  
    unsigned char *c = (unsigned char *)&a;  
    int i = system("cat /proc/cpuinfo | grep GenuineIntel >/dev/null");  
  
    if (i == 0) {  
        CHECK_RESULT(i == *c);  
    }  
    else  
        printf("No checking for this CPU type.\n");  
  
    if (*c == 0x00)   
        tprint("big endian.\n");  
    else if (*c == 0x01)  
        tprint("little endian.\n");  
    else  
        tprint("test failed.\n");         
}

void test_size(void)
{
    short a;
    int b;
    long c;
    long long d;
    tprint("size: short(%lu), int(%lu), long(%lu), long long(%lu)\n", sizeof(a), sizeof(b), sizeof(c), sizeof(d));
    CHECK_RESULT(sizeof(a) == 2 && sizeof(b) == 4 && sizeof(c) == 8 && sizeof(d) == 8);
}  
  
int main()  
{  
    test_reverse_str();  
    test_check_bit_in_byte();  
    test_str_copy();  
    test_str_cat();  
    test_str_len();   
    test_mem_copy();  
    test_endian(); 
    test_size(); 
    return 0;     
}  
