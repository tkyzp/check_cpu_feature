#include<stdio.h>


#define PKU_BIT (3)
#define PKU_MASK (1U << PKU_BIT)

#define CET_BIT (7)
#define CET_MASK (1U << CET_BIT)

int check_mpk(){
    unsigned int result = 0;
    asm(
        "mov $7, %%eax \n"
        "xor %%ecx, %%ecx \n"
        "cpuid \n"
        :"=c"(result)::"%edx", "%ebx"
    );
    result = result & PKU_MASK;
    return result;
}

int check_cet(){
    unsigned int result = 0;
    asm(
        "mov $7, %%eax \n"
        "xor %%ecx, %%ecx \n"
        "cpuid \n"
        :"=c"(result)::"%edx", "%ebx"
    );
    result = result & CET_MASK;
    return result;
}


int main(int argc, char const *argv[])
{
    printf("MPK:");
    if(check_mpk()){
        printf("supported\n");
    }else{
        printf("not support\n");
    }

    printf("CET:");
    if(check_cet()){
      printf("supported\n");
    }else{
        printf("not support\n");
    }
    return 0;
}
