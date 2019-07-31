//
// Created by Yif on 2019/6/22.
//
#include <jni.h>
#include <cstdio>
#include <android/log.h>
#define  LOGI(...) __android_log_print(ANDROID_LOG_INFO, "========= Info =========   ", __VA_ARGS__)

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, "========= Error =========   ", __VA_ARGS__)

#define  LOGD(...)  __android_log_print(ANDROID_LOG_INFO, "========= Debug =========   ", __VA_ARGS__)

#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN, "========= Warn =========   ", __VA_ARGS__)

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnilearndemo_JNIUtils_calculate(JNIEnv *env, jclass type, jint a, jint b) {

    // TODO
    int i,result = 0;
    for(i = a;i<=b;i++){
        result +=i;
    }
    return result;
}
/**
 * 模拟崩溃异常
 */

void crash(){
    int *p=NULL;
    //每次进行非空判断，避免出现空指针
    *p=1;
    if(*p!=NULL){
        *p = 1;
    }
    //模拟野指针崩溃
    int *q;
    *q = 2;
    //数组异常，但是程序不会崩溃
//    int data[10];
//    data[11]=2;
    printf("%d\n",*p);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnilearndemo_JNIUtils_callInstance(JNIEnv *env, jclass type, jint i) {
//    crash();

    // TODO 当源文件为.cpp时，只需要传env ->就可以；而当源文件为.c时，就需要传入(*env)->
    //查找类
    jclass cls_jniutils = env -> FindClass("com/example/jnilearndemo/JNIUtils");
    //判断是否找到，没找到返回
    if(cls_jniutils==NULL){
        return;
    }
    //然后在查找该类下的方法,参数查找的类，查找的方法，方法对应的签名
    jmethodID method_static = env ->GetStaticMethodID(cls_jniutils,"staticMethod","(Ljava/lang/String;)V");
    if(method_static==NULL){
        return;
    }
    //传递参数为String，所以要创建String对象
    jstring data = env->NewStringUTF("call static method");
    if(data==NULL){
        return;
    }
    //修改java中的静态变量，找到对应的成员变量
    jfieldID field_name = env->GetStaticFieldID(cls_jniutils,"name","Ljava/lang/String;");
    if(field_name==NULL){
        return;
    }
    jstring new_name = env->NewStringUTF("yif");
    //对成员变量进行重新设置
    env->SetStaticObjectField(cls_jniutils,field_name, new_name);
    //调用之前methodId所对应的的静态方法
    env ->CallStaticVoidMethod(cls_jniutils,method_static,data);

    //异常捕获
    if(env->ExceptionOccurred()){
        env->ExceptionDescribe();
        env->ExceptionClear();
        jclass cls_exception = env->FindClass("java/lang/Exception");
        env->ThrowNew(cls_exception,"call java static method ndk error");
        return;
    }
    //模拟ndk崩溃继续执行后面代码
    LOGI("ndk error");
    //最后释放之前创建的对象,这里为局部引用
    env ->DeleteLocalRef(cls_jniutils);
    env->DeleteLocalRef(data);
    env->DeleteLocalRef(new_name);
}

//C++调用java的实例方法与实例变量
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnilearndemo_JNIUtils_callInstanceMethod(JNIEnv *env, jobject instance, jint i) {
   jclass cls_jniutils = env->FindClass("com/example/jnilearndemo/JNIUtils");
   if(cls_jniutils==NULL){
       return;
   }
   jmethodID method_instance = env->GetMethodID(cls_jniutils,"method","(Ljava/lang/String;)V");
   if(method_instance==NULL){
       return;
   }
   //首先获取构造方法，再通过构造方法获取类对象，根据类对象调用实例方法；构造方法通过<init>进行标识，传递参数为空，返回值也为空
   jmethodID method_construct = env->GetMethodID(cls_jniutils,"<init>","()V");
   if(method_construct==NULL){
       return;
   }
   //创建相应的对象，最后参数为空，不需要传递参数
   jobject jnutils = env->NewObject(cls_jniutils,method_construct,NULL);
   if(jnutils==NULL){
       return;
   }
   jstring msg = env->NewStringUTF("call instance method");

   //调用Java中的实例变量
   jfieldID filed_instance = env->GetFieldID(cls_jniutils,"address","Ljava/lang/String;");
   if(filed_instance==NULL){
       return;
   }

   jstring address = env->NewStringUTF("suzhou");
   //设置实例变量，需要传递对象
   env -> SetObjectField(jnutils,filed_instance,address);
   env -> CallVoidMethod(jnutils,method_instance,msg);

   env->DeleteLocalRef(msg);
   env->DeleteLocalRef(cls_jniutils);
   env->DeleteLocalRef(jnutils);
   env->DeleteLocalRef(address);
}