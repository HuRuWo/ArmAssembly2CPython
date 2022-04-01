#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_huruwo_armassembly2cpython_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string v5 = "Hello from C++";
    const char *v3 =  v5.c_str();
    jstring v2 = env->NewStringUTF(v3);
    return v2;
}

extern "C" JNIEXPORT int JNICALL
Java_com_huruwo_armassembly2cpython_MainActivity_sumFromJNI(
        JNIEnv* env,
        jobject /* this */,int a,int b) {
    int c = a+b;
    return c;
}