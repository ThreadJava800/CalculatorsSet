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

jstring stringToJstring(JNIEnv *env, string value) {
    return env->NewStringUTF(value.c_str());
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_example_calculatorstry2_MainActivity_romeToArab(
        JNIEnv *env,
        jclass clazz, jstring rome_num) {
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

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_calculatorstry2_MainActivity_arabToRome(
        JNIEnv *env,
        jclass clazz, jstring arab_num) {
    string res = "";
    string arab_num_str = jstringToString(env, arab_num);
    long thousands = 0; //num of 1000
    int hundreds = 0; //num of 100
    int decs = 0; //num of 10
    int ed = 0; //num of 1
    if (arab_num_str.length() >= 4) {
        string tmp = "";
        for (int i = arab_num_str.length() - 4; i >= 0; i--) {
            tmp += arab_num_str[i];
        }
        thousands = atoi(tmp.c_str());
        for (int i = 0; i < thousands; i++) {
            res += 'M';
        }
    }
    if (arab_num_str.length() >= 3) {
        hundreds = (int) arab_num_str[arab_num_str.length() - 3] - 48;
        if (hundreds == 4) {
            res += "CD";
        } else if (hundreds == 5) {
            res += 'D';
        } else if (hundreds == 6) {
            res += "DC";
        } else if (hundreds == 7) {
            res += "DCC";
        } else if (hundreds == 8) {
            res += "DCCC";
        } else if (hundreds == 9) {
            res += "CM";
        } else {
            for (int i = 0; i < hundreds; i++) {
                res += 'C';
            }
        }
    }
    if (arab_num_str.length() >= 2) {
        decs = (int) arab_num_str[arab_num_str.length() - 2] - 48;
        if (decs == 4) {
            res += "XL";
        } else if (decs == 5) {
            res += 'L';
        } else if (decs == 6) {
            res += "LX";
        } else if (decs == 7) {
            res += "LXX";
        } else if (decs == 8) {
            res += "LXXX";
        } else if (decs == 9) {
            res += "XC";
        } else {
            for (int i = 0; i < decs; i++) {
                res += 'X';
            }
        }
    }
    if (arab_num_str.length() >= 1) {
        ed = (int) arab_num_str[arab_num_str.length() - 1] - 48;
        if (ed == 4) {
            res += "IV";
        } else if (ed == 5) {
            res += 'V';
        } else if (ed == 6) {
            res += "VI";
        } else if (ed == 7) {
            res += "VII";
        } else if (ed == 8) {
            res += "VIII";
        } else if (ed == 9) {
            res += "IX";
        } else {
            for (int i = 0; i < ed; i++) {
                res += 'I';
            }
        }
    }

    return stringToJstring(env, res);
}