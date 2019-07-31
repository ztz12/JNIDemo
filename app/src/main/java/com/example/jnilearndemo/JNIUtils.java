package com.example.jnilearndemo;

import android.util.Log;

public class JNIUtils {
    static {
        //加载动态库
        System.loadLibrary("JNILearning");
    }
    public static String name = "ztz";
    public String address = "hangzhou";
    public static native int calculate(int a,int b);
    public static native void callInstance(int i);
    public native void callInstanceMethod(int i);
    public static void LogMessage(String msg){
        Log.i("C++调用java中的static方法", msg);
    }
    public static void staticMethod(String msg){
        LogMessage(msg);
//        LogMessage(null);
        LogMessage(name);
    }

    public void method(String msg){
        LogMessage(msg);
        LogMessage(address);
    }
}
