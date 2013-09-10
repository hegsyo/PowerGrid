
#ifndef JACE_PROXY_JAVA_LANG_RUNTIMEEXCEPTION_H
#include "jace/proxy/java/lang/RuntimeException.h"
#endif

/**
 * Standard Jace headers needed to implement this class.
 *
 */
#ifndef JACE_JARGUMENTS_H
#include "jace/JArguments.h"
#endif
using jace::JArguments;

#ifndef JACE_JMETHOD_H
#include "jace/JMethod.h"
#endif
using jace::JMethod;

#ifndef JACE_JFIELD_H
#include "jace/JField.h"
#endif
using jace::JField;

#ifndef JACE_JCLASS_IMPL_H
#include "jace/JClassImpl.h"
#endif
using jace::JClassImpl;


/**
 * Headers for the classes that this class uses.
 *
 */
#ifndef JACE_TYPES_JVOID_H
#include "jace/proxy/types/JVoid.h"
#endif
#ifndef JACE_PROXY_JAVA_LANG_STRING_H
#include "jace/proxy/java/lang/String.h"
#endif
#ifndef JACE_PROXY_JAVA_LANG_THROWABLE_H
#include "jace/proxy/java/lang/Throwable.h"
#endif

BEGIN_NAMESPACE_4( jace, proxy, java, lang )

/**
 * The Jace C++ proxy class source for java/lang/RuntimeException.
 * Please do not edit this source, as any changes you make will be overwritten.
 * For more information, please refer to the Jace Developer's Guide.
 *
 */
#ifndef VIRTUAL_INHERITANCE_IS_BROKEN
  #define RuntimeException_INITIALIZER : ::jace::proxy::java::lang::Exception( NO_OP ), ::jace::proxy::java::lang::Object( NO_OP )
#else
  #define RuntimeException_INITIALIZER : ::jace::proxy::java::lang::Exception( NO_OP )
#endif

RuntimeException::RuntimeException() RuntimeException_INITIALIZER {
  ::jace::JArguments arguments;
  jobject localRef = newObject( arguments );
  setJavaJniObject( localRef );
  JNIEnv* env = ::jace::helper::attach();
  ::jace::helper::deleteLocalRef( env, localRef );
}

RuntimeException::RuntimeException( ::jace::proxy::java::lang::String p0 ) RuntimeException_INITIALIZER {
  ::jace::JArguments arguments;
  arguments << p0;
  jobject localRef = newObject( arguments );
  setJavaJniObject( localRef );
  JNIEnv* env = ::jace::helper::attach();
  ::jace::helper::deleteLocalRef( env, localRef );
}

RuntimeException::RuntimeException( ::jace::proxy::java::lang::String p0, ::jace::proxy::java::lang::Throwable p1 ) RuntimeException_INITIALIZER {
  ::jace::JArguments arguments;
  arguments << p0 << p1;
  jobject localRef = newObject( arguments );
  setJavaJniObject( localRef );
  JNIEnv* env = ::jace::helper::attach();
  ::jace::helper::deleteLocalRef( env, localRef );
}

RuntimeException::RuntimeException( ::jace::proxy::java::lang::Throwable p0 ) RuntimeException_INITIALIZER {
  ::jace::JArguments arguments;
  arguments << p0;
  jobject localRef = newObject( arguments );
  setJavaJniObject( localRef );
  JNIEnv* env = ::jace::helper::attach();
  ::jace::helper::deleteLocalRef( env, localRef );
}

/**
 * The following methods are required to integrate this class
 * with the Jace framework.
 *
 */
RuntimeException::RuntimeException( jvalue value ) RuntimeException_INITIALIZER {
  setJavaJniValue( value );
}

RuntimeException::RuntimeException( jobject object ) RuntimeException_INITIALIZER {
  setJavaJniObject( object );
}

RuntimeException::RuntimeException( const RuntimeException& object ) RuntimeException_INITIALIZER {
  setJavaJniObject( object.getJavaJniObject() );
}

RuntimeException::RuntimeException( const NoOp& noOp ) RuntimeException_INITIALIZER {
}

const JClass* RuntimeException::staticGetJavaJniClass() throw ( JNIException ) {
  static JClassImpl javaClass( "java/lang/RuntimeException" );
  return &javaClass;
}

const JClass* RuntimeException::getJavaJniClass() const throw ( JNIException ) {
  return RuntimeException::staticGetJavaJniClass();
}

JEnlister< RuntimeException> RuntimeException::enlister;

END_NAMESPACE_4( jace, proxy, java, lang )

BEGIN_NAMESPACE( jace )

#ifndef PUT_TSDS_IN_HEADER
  template <> inline ElementProxy< ::jace::proxy::java::lang::RuntimeException>::ElementProxy( jarray array, jvalue element, int index ) : 
    ::jace::proxy::java::lang::RuntimeException( element ), Object( NO_OP ), mIndex( index ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, array ) );
  }
  template <> inline ElementProxy< ::jace::proxy::java::lang::RuntimeException>::ElementProxy( const jace::ElementProxy< ::jace::proxy::java::lang::RuntimeException>& proxy ) : 
    ::jace::proxy::java::lang::RuntimeException( proxy.getJavaJniObject() ), Object( NO_OP ), mIndex( proxy.mIndex ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, proxy.parent ) );
  }
#endif
#ifndef PUT_TSDS_IN_HEADER
  template <> inline JFieldProxy< ::jace::proxy::java::lang::RuntimeException>::JFieldProxy( jfieldID fieldID_, jvalue value, jobject parent_ ) : 
    ::jace::proxy::java::lang::RuntimeException( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    if ( parent_ ) {
      parent = ::jace::helper::newGlobalRef( env, parent_ );
    }
    else {
      parent = parent_;
    }

    parentClass = 0;
  }
  template <> inline JFieldProxy< ::jace::proxy::java::lang::RuntimeException>::JFieldProxy( jfieldID fieldID_, jvalue value, jclass parentClass_ ) : 
    ::jace::proxy::java::lang::RuntimeException( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    parent = 0;
    parentClass = static_cast<jclass>( ::jace::helper::newGlobalRef( env, parentClass_ ) );
  }
  template <> inline JFieldProxy< ::jace::proxy::java::lang::RuntimeException>::JFieldProxy( const ::jace::JFieldProxy< ::jace::proxy::java::lang::RuntimeException>& object ) : 
    ::jace::proxy::java::lang::RuntimeException( object.getJavaJniValue() ), Object( NO_OP ) {

    fieldID = object.fieldID; 

    if ( object.parent ) {
      JNIEnv* env = ::jace::helper::attach();
      parent = ::jace::helper::newGlobalRef( env, object.parent );
    }
    else {
      parent = 0;
    }

    if ( object.parentClass ) {
      JNIEnv* env = ::jace::helper::attach();
      parentClass = static_cast<jclass>( ::jace::helper::newGlobalRef( env, object.parentClass ) );
    }
    else {
      parentClass = 0;
    }
  }
#endif

END_NAMESPACE( jace )
