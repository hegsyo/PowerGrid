#ifndef UPDATER_H
#define UPDATER_H

#include "jniexception.h"
#include "javaenv.h"
#include "jniclass.h"
#include <QHash>

namespace jni {

  /**
   * @brief represents an error that occurred because a Java class could not be identified.
   */
  class class_id_error : public jni_error {
    public:
      /**
       * @brief Constructs a class_id_error with the given message
       * @param msg the message describing this class_id_error
       */
      class_id_error(const string& msg) : jni_error(msg) {}
  };

  class Updater {
    protected:
      JavaEnv* env;
      QHash<QString, JNIClass*> bindings;
    public:
      Updater(JavaEnv* environment);

      JavaEnv* Env() { return env; }

      JNIClass* GetClass(QString identifier);
      QString Identify(jclass cls);
  };
}
#endif // UPDATER_H