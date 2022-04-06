#include <jni.h>
#include <string>

extern "C" JNIEXPORT void JNICALL
Java_com_huruwo_armassembly2cpython_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string s = "Hello";
}

extern "C" JNIEXPORT void JNICALL
Java_com_huruwo_armassembly2cpython_MainActivity_sumFromJNI(
        JNIEnv* env,
        jobject /* this */,int a,int b) {
    int c = a+b;
}