#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
/**
 * CPP 源文件，返回一个字符串
 * @param env
 * @return
 */
Java_com_example_jnilearndemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}