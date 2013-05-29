#include "jnivalue.h"
#include "jniexception.h"

using namespace std;

namespace jni {


  JNIValue::JNIValue() {
    type    = JVOID;
  }

  JNIValue::JNIValue(const JNIValue& val) {
    value = val.value;
    type  = val.type;
  }

  JNIValue::JNIValue(jvalue_type t, jvalue val) {
    if (t != JVOID) {
      // If the type is JVOID we don't save the jvalue, since we don't retrieve it anyway.
      value = val;
    }
    type  = t;
  }

  JNIValue::JNIValue(jobject o) {
    value.l = o;
    type = JOBJECT;
  }

  JNIValue::JNIValue(jboolean z) {
    value.z = z;
    type = JBOOLEAN;
  }

  JNIValue::JNIValue(jbyte b) {
    value.b = b;
    type = JBYTE;
  }

  JNIValue::JNIValue(jchar c) {
    value.c = c;
    type = JCHAR;
  }

  JNIValue::JNIValue(jdouble d) {
    value.d = d;
    type = JDOUBLE;
  }

  JNIValue::JNIValue(jfloat f) {
    value.f = f;
    type = JFLOAT;
  }

  JNIValue::JNIValue(jint i) {
    value.i = i;
    type = JINT;
  }

  JNIValue::JNIValue(jlong l) {
    value.j = l;
    type = JLONG;
  }

  JNIValue::JNIValue(jshort s) {
    value.s = s;
    type = JSHORT;
  }

  jvalue JNIValue::Get() {
    if (type == JVOID) {
      throw jni_error("Get called on void JNIValue");
    }
    return value;
  }

  jvalue_type JNIValue::GetType() {
    return type;
  }

  jboolean JNIValue::operator ==(JNIValue other) {
    if (type != other.GetType()) {
      return JNI_FALSE;
    } else {
      jvalue val2 = other.Get();
      switch(type) {
        case JVOID:    return JNI_TRUE; // void type == void type regardless of actual content.
        case JBOOLEAN: return value.z == val2.z;
        case JSHORT:   return value.s == val2.s;
        case JBYTE:    return value.b == val2.b;
        case JCHAR:    return value.c == val2.c;
        case JINT:     return value.i == val2.i;
        case JOBJECT:  return value.l == val2.l;
        case JLONG:    return value.j == val2.j;
        case JDOUBLE:  return value.d == val2.d;
        case JFLOAT:   return value.f == val2.f;
        default:       throw logic_error("Invalid or unknown JNIValue"); // should not happen
      }
    }
  }

  jboolean JNIValue::IsNull() {
    // Note: we also count void JNIValues as NULL values.
    return type == JVOID || (type == JOBJECT && value.l == NULL);
  }

  jboolean JNIValue::GetBoolean() {
    VERIFY_THAT(type == JBOOLEAN);
    return value.z;
  }

  jshort JNIValue::GetShort() {
    VERIFY_THAT(type == JSHORT);
    return value.s;
  }

  jbyte JNIValue::GetByte() {
    VERIFY_THAT(type == JBYTE);
    return value.b;
  }

  jchar JNIValue::GetChar() {
    VERIFY_THAT(type == JCHAR);
    return value.c;
  }

  jint JNIValue::GetInt() {
    VERIFY_THAT(type == JINT);
    return value.i;
  }

  jobject JNIValue::GetObject() {
    VERIFY_THAT(type == JOBJECT);
    return value.l;
  }

  jlong JNIValue::GetLong() {
    VERIFY_THAT(type == JLONG);
    return value.j;
  }

  jdouble JNIValue::GetDouble() {
    VERIFY_THAT(type == JDOUBLE);
    return value.d;
  }

  jfloat JNIValue::GetFloat() {
    VERIFY_THAT(type == JFLOAT);
    return value.f;
  }

}
