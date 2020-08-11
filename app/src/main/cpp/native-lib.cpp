#include <jni.h>
#include <string>
#include <map>

using namespace std;

map<char, int> rome_numbers;

extern "C" JNIEXPORT void JNICALL
Java_com_example_calculatorstry2_MainActivity_init(
        JNIEnv *env,
        jobject /* this */) {
    rome_numbers['I'] = 1;
    rome_numbers['V'] = 5;
    rome_numbers['X'] = 10;
    rome_numbers['L'] = 50;
    rome_numbers['C'] = 100;
    rome_numbers['D'] = 500;
    rome_numbers['M'] = 1000;
}

string jstringToString(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes,
                                                                       env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *) pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_example_calculatorstry2_MainActivity_romeToArab(
        JNIEnv *env,
        jobject /* this */, jstring rome_num) {
    int res = 0;
    int tmp = 0;
    for (char i: jstringToString(env, rome_num)) {
        int n = rome_numbers[i];
        if (n < tmp) {
            res += tmp;
            tmp = n;
        } else if (n > tmp) {
            if (tmp == 0) tmp = n;
            else {
                res += n - tmp;
                tmp = 0;
            }
        } else if (n == tmp) {
            res += tmp + n;
            tmp = 0;
        }
    }
    return res + tmp;
}
