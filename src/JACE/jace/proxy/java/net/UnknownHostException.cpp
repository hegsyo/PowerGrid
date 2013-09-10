
#ifndef JACE_PROXY_JAVA_NET_UNKNOWNHOSTEXCEPTION_H
#include "jace/proxy/java/net/UnknownHostException.h"
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

BEGIN_NAMESPACE_4( jace, proxy, java, net )

/**
 * The Jace C++ proxy class source for java/net/UnknownHostException.
 * Please do not edit this source, as any changes you make will be overwritten.
 * For more information, please refer to the Jace Developer's Guide.
 *
 */
#ifndef VIRTUAL_INHERITANCE_IS_BROKEN
  #define UnknownHostException_INITIALIZER : ::jace::proxy::java::io::IOException( NO_OP ), ::jace::proxy::java::lang::Object( NO_OP )
#else
  #define UnknownHostException_INITIALIZER : ::jace::proxy::java::io::IOException( NO_OP )
#endif

UnknownHostException::UnknownHostException( ::jace::proxy::java::lang::String p0 ) UnknownHostException_INITIALIZER {
  ::jace::JArguments arguments;
  arguments << p0;
  jobject localRef = newObject( arguments );
  setJavaJniObject( localRef );
  JNIEnv* env = ::jace::helper::attach();
  ::jace::helper::deleteLocalRef( env, localRef );
}

UnknownHostException::UnknownHostException() UnknownHostException_INITIALIZER {
  ::jace::JArguments arguments;
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
UnknownHostException::UnknownHostException( jvalue value ) UnknownHostException_INITIALIZER {
  setJavaJniValue( value );
}

UnknownHostException::UnknownHostException( jobject object ) UnknownHostException_INITIALIZER {
  setJavaJniObject( object );
}

UnknownHostException::UnknownHostException( const UnknownHostException& object ) UnknownHostException_INITIALIZER {
  setJavaJniObject( object.getJavaJniObject() );
}

UnknownHostException::UnknownHostException( const NoOp& noOp ) UnknownHostException_INITIALIZER {
}

const JClass* UnknownHostException::staticGetJavaJniClass() throw ( JNIException ) {
  static JClassImpl javaClass( "java/net/UnknownHostException" );
  return &javaClass;
}

const JClass* UnknownHostException::getJavaJniClass() const throw ( JNIException ) {
  return UnknownHostException::staticGetJavaJniClass();
}

JEnlister< UnknownHostException> UnknownHostException::enlister;

END_NAMESPACE_4( jace, proxy, java, net )

BEGIN_NAMESPACE( jace )

#ifndef PUT_TSDS_IN_HEADER
  template <> inline ElementProxy< ::jace::proxy::java::net::UnknownHostException>::ElementProxy( jarray array, jvalue element, int index ) : 
    ::jace::proxy::java::net::UnknownHostException( element ), Object( NO_OP ), mIndex( index ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, array ) );
  }
  template <> inline ElementProxy< ::jace::proxy::java::net::UnknownHostException>::ElementProxy( const jace::ElementProxy< ::jace::proxy::java::net::UnknownHostException>& proxy ) : 
    ::jace::proxy::java::net::UnknownHostException( proxy.getJavaJniObject() ), Object( NO_OP ), mIndex( proxy.mIndex ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, proxy.parent ) );
  }
#endif
#ifndef PUT_TSDS_IN_HEADER
  template <> inline JFieldProxy< ::jace::proxy::java::net::UnknownHostException>::JFieldProxy( jfieldID fieldID_, jvalue value, jobject parent_ ) : 
    ::jace::proxy::java::net::UnknownHostException( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    if ( parent_ ) {
      parent = ::jace::helper::newGlobalRef( env, parent_ );
    }
    else {
      parent = parent_;
    }

    parentClass = 0;
  }
  template <> inline JFieldProxy< ::jace::proxy::java::net::UnknownHostException>::JFieldProxy( jfieldID fieldID_, jvalue value, jclass parentClass_ ) : 
    ::jace::proxy::java::net::UnknownHostException( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    parent = 0;
    parentClass = static_cast<jclass>( ::jace::helper::newGlobalRef( env, parentClass_ ) );
  }
  template <> inline JFieldProxy< ::jace::proxy::java::net::UnknownHostException>::JFieldProxy( const ::jace::JFieldProxy< ::jace::proxy::java::net::UnknownHostException>& object ) : 
    ::jace::proxy::java::net::UnknownHostException( object.getJavaJniValue() ), Object( NO_OP ) {

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
