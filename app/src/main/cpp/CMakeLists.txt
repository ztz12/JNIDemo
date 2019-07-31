# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
# 指定cmake版本
cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
# add_library命令用于向cmake添加依赖库或者源文件 参数(函数名称，库类型，依赖源文件相对路径)
add_library( # Sets the name of the library.
        # 生成函数库的名称，即libnative-lib.so或libnative-lib.a(lib和.so/.a默认缺省)
        JNILearning
        #生成库类型，动态库为SHARED 静态库为STATIC
        # Sets the library as a shared library.
        SHARED
        #依赖 c/cpp相对路径
        # Provides a relative path to your source file(s).
        JNILearning.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
# 定位ndk中的库
find_library( # Sets the name of the path variable.
        # 设置path变量的名称，这里为NDK中的日志库
        log-lib
        #指定cmake查询库的名称
        #即在ndk开发包中查询liblog.so函数库，将其路径赋值给log-lib
        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
#指定想要关联的原生库
target_link_libraries( # Specifies the target library.
        # 指定目标库，与上面指定的函数库名一致
        JNILearning
        # 链接的库，根据log-lib变量对应liblog.so函数库
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})