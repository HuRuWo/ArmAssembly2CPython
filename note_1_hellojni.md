### hellojni:NDKC代码和伪C代码以及汇编代码分析

#### NDK C++

```C++
extern "C" JNIEXPORT int JNICALL
Java_com_huruwo_armassembly2cpython_MainActivity_sumFromJNI(
        JNIEnv* env,
        jobject /* this */,int a,int b) {
    int c = a+b;
    return c;
}
```


#### IDA 伪C

```C++
int __fastcall Java_com_huruwo_armassembly2cpython_MainActivity_sumFromJNI(int a1, int a2, int a3, int a4)
{
  return a3 + a4;
}
```

#### 对比分析

可以看到两个方法大有不同，因为在编译成二进制再回来语言的过程中新增也丢失了很多细节。


##### 返回: int 数据类型

都是int没问题

##### __fastcall 编译器新增

指示参数传递的入栈出栈问题

- 当参数个数多于一个时，按照什么顺序把参数压入堆栈
- 函数调用后，由谁来把堆栈恢复原装

- stdcall
- cdecl
- fastcall
>函数的第一个和第二个DWORD参数（或者尺寸更小的）通过ecx和edx传递，其他参数通过从右向左的顺序压栈
被调用函数清理堆栈
函数名修改规则同stdcall
- thiscall
- naked call

暂时了解fastcall即可

##### 参数JNIEnv 以及 jobject 未被识别 

需要手动修复识别 导入头文件c.h 这里没用上可以不管

- JNIEnv
JNIEnv类型实际上代表了Java环境，通过这个JNIEnv* 指针，就可以对Java端的代码进行操作。例如，创建Java类中的对象，调用Java对象的方法，获取Java对象中的属性等等。JNIEnv的指针会被JNI传入到本地方法的实现函数中来对Java端的代码进行操作。

- jobject
如果native方法不是static的话，这个obj就代表这个native方法的类实例
如果native方法是static的话，这个obj就代表这个native方法的类的class对象实例(static方法不需要类实例的，所以就代表这个类的class对象)


IDA确实直接缺省了第二个参数，因为实际上没有用到。

##### 逐行对比方法内部内容

由于之前的NDK写法过于简陋，现修改如下

```c++
std::string v5 = "Hello from C++";
const char *v3 =  v5.c_str();
jstring v2 = env->NewStringUTF(v3);
return v2;
```
对比IDA

```c++
int v2; // [sp+0h] [bp-38h]
char *v3; // [sp+4h] [bp-34h]
char v5[12]; // [sp+20h] [bp-18h] BYREF

std::string::basic_string<decltype(nullptr)>();
v3 = (char *)sub_8252(v5);
v2 = _JNIEnv::NewStringUTF(a1, v3);
std::string::~string(v5);
return v2;
```

###### 字符串赋值呢?

在伪C代码里面 看不到 v5的赋值信息

即使我只写一行

`std::string v5 = "Hello from C++";`

反编译过来也是

```c++
  char v1[12]; // [sp+10h] [bp-18h] BYREF
  std::string::basic_string<decltype(nullptr)>();
  std::string::~string(v1);
  return &_stack_chk_guard;
```

`std::string::basic_string<decltype(nullptr)>(); `这行也是编译器新增的 用于类型推断

实际上有用的是

`std::string::~string(v1);`

所以伪C代码不完全可信

##### c_str 和 sub_8252

可以推断出两个方法是一样的，但是IDA没有识别出这个方法来。

##### 剩下的没什么好看的


#### 汇编代码 

##### 针对函数:sumFromJNI 汇编代码

IDA的汇编代码加载了反编译的额外信息
作为对比可以看出IDA对这些数据做了什么

```
SUB             SP, SP, #0x14


STR             R0, [SP,#0x14+var_4]
STR             R1, [SP,#0x14+var_8]


STR             R2, [SP,#0x14+var_C]
STR             R3, [SP,#0x14+var_10]


LDR             R0, [SP,#0x14+var_C]
LDR             R1, [SP,#0x14+var_10]

ADD             R0, R1

STR             R0, [SP,#0x14+var_14]
LDR             R0, [SP,#0x14+var_14]

ADD             SP, SP, #0x14
BX              LR
```
SP = SP-14

STR 寄存器数据到储存器 后面是存储器的地址
寻址方式 基址变址:[SP+立即数]

LDR 存储器数据读到寄存器 后面是存储器的地址
寻址方式 基址变址:[SP+立即数]

ADD  R0 = R1+R0

STR LDR 操作同一个地址

STR R0数据到存储器
LDR 存储器数据回到R0

演示一遍

![](note_pic/note01_1_02.png)