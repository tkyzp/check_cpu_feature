# 如何检查CPU是否支持某些特性

有时候，我们需要用到一些CPU特性，但我们不知道手上的CPU是否支持，这个时候通常需要去CPU产品的官网查看产品信息。但是有些特性可能不会在网站上列出来，比如，我们目前还无法直接在intel的官网上查到一款CPU是否支持MPK。

在x86的CPU上，我们可以借助CPUID指令。

以查询是否支持MPK为例，MPK又叫PKU，我们可以在[Intel的手册](https://community.intel.com/legacyfs/online/drupal_files/managed/a4/60/325384-sdm-vol-3abcd.pdf)上查到如下信息：

> If CPUID.(EAX=07H,ECX=0H):ECX.PKU [bit 3] = 1, the processor supports the protection-key feature for 4-level paging.

因此，我们只需要执行一下CPUID指令，然后检查一下返回值，即可知道是否支持MPK。

```
#define PKU_BIT (3)
#define PKU_MASK (1U << PKU_BIT)

int check_mpk(){
    unsigned int result = 0;
    asm(
        "mov $7, %%eax \n"
        "xor %%ecx, %%ecx \n"
        "cpuid \n"
        :"=c"(result)::"%ebx","%edx"
    );
    result = result & PKU_MASK;
    return result;
}
```

[CPUID指令参考](https://www.felixcloutier.com/x86/cpuid)