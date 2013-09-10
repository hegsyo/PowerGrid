
#ifndef JACE_PROXY_JAVA_LANG_PACKAGE_H
#define JACE_PROXY_JAVA_LANG_PACKAGE_H

#ifndef JACE_OS_DEP_H
#include "jace/os_dep.h"
#endif

#ifndef JACE_NAMESPACE_H
#include "jace/namespace.h"
#endif

#ifndef JACE_JOBJECT_H
#include "jace/proxy/JObject.h"
#endif

#ifndef JACE_JENLISTER_H
#include "jace/JEnlister.h"
#endif

#ifndef JACE_JARRAY_H
#include "jace/JArray.h"
#endif

#ifndef JACE_JFIELD_PROXY_H
#include "jace/JFieldProxy.h"
#endif

/**
 * The super class for this class.
 *
 */
#ifndef JACE_PROXY_JAVA_LANG_OBJECT_H
#include "jace/proxy/java/lang/Object.h"
#endif

/**
 * The interfaces implemented by this class.
 *
 */
#ifndef JACE_PROXY_JAVA_LANG_REFLECT_ANNOTATEDELEMENT_H
#include "jace/proxy/java/lang/reflect/AnnotatedElement.h"
#endif

/**
 * Classes which this class is fully dependent upon.
 *
 */
#ifndef JACE_PROXY_JAVA_LANG_ANNOTATION_ANNOTATION_H
#include "jace/proxy/java/lang/annotation/Annotation.h"
#endif

/**
 * Forward declarations for the classes that this class uses.
 *
 */
BEGIN_NAMESPACE_4( jace, proxy, java, lang )
class String;
END_NAMESPACE_4( jace, proxy, java, lang )

BEGIN_NAMESPACE_3( jace, proxy, types )
class JBoolean;
END_NAMESPACE_3( jace, proxy, types )

BEGIN_NAMESPACE_4( jace, proxy, java, net )
class URL;
END_NAMESPACE_4( jace, proxy, java, net )

BEGIN_NAMESPACE_4( jace, proxy, java, lang )
class NumberFormatException;
END_NAMESPACE_4( jace, proxy, java, lang )

BEGIN_NAMESPACE_3( jace, proxy, types )
class JInt;
END_NAMESPACE_3( jace, proxy, types )

BEGIN_NAMESPACE_5( jace, proxy, java, lang, annotation )
class Annotation;
END_NAMESPACE_5( jace, proxy, java, lang, annotation )

BEGIN_NAMESPACE_4( jace, proxy, java, lang )
class Class;
END_NAMESPACE_4( jace, proxy, java, lang )

BEGIN_NAMESPACE_4( jace, proxy, java, lang )

/**
 * The Jace C++ proxy class for java/lang/Package.
 * Please do not edit this class, as any changes you make will be overwritten.
 * For more information, please refer to the Jace Developer's Guide.
 *
 */
class Package : public virtual ::jace::proxy::java::lang::Object, public virtual ::jace::proxy::java::lang::reflect::AnnotatedElement {

public: 

/**
 * getName
 *
 */
::jace::proxy::java::lang::String getName();

/**
 * getSpecificationTitle
 *
 */
::jace::proxy::java::lang::String getSpecificationTitle();

/**
 * getSpecificationVersion
 *
 */
::jace::proxy::java::lang::String getSpecificationVersion();

/**
 * getSpecificationVendor
 *
 */
::jace::proxy::java::lang::String getSpecificationVendor();

/**
 * getImplementationTitle
 *
 */
::jace::proxy::java::lang::String getImplementationTitle();

/**
 * getImplementationVersion
 *
 */
::jace::proxy::java::lang::String getImplementationVersion();

/**
 * getImplementationVendor
 *
 */
::jace::proxy::java::lang::String getImplementationVendor();

/**
 * isSealed
 *
 */
::jace::proxy::types::JBoolean isSealed();

/**
 * isSealed
 *
 */
::jace::proxy::types::JBoolean isSealed( ::jace::proxy::java::net::URL p0 );

/**
 * isCompatibleWith
 *
 */
::jace::proxy::types::JBoolean isCompatibleWith( ::jace::proxy::java::lang::String p0 );

/**
 * getPackage
 *
 */
static ::jace::proxy::java::lang::Package getPackage( ::jace::proxy::java::lang::String p0 );

/**
 * getPackages
 *
 */
static ::jace::JArray< ::jace::proxy::java::lang::Package > getPackages();

/**
 * hashCode
 *
 */
::jace::proxy::types::JInt hashCode();

/**
 * toString
 *
 */
::jace::proxy::java::lang::String toString();

/**
 * getAnnotation
 *
 */
::jace::proxy::java::lang::annotation::Annotation getAnnotation( ::jace::proxy::java::lang::Class p0 );

/**
 * isAnnotationPresent
 *
 */
::jace::proxy::types::JBoolean isAnnotationPresent( ::jace::proxy::java::lang::Class p0 );

/**
 * getAnnotations
 *
 */
::jace::JArray< ::jace::proxy::java::lang::annotation::Annotation > getAnnotations();

/**
 * getDeclaredAnnotations
 *
 */
::jace::JArray< ::jace::proxy::java::lang::annotation::Annotation > getDeclaredAnnotations();

/**
 * The following methods are required to integrate this class
 * with the Jace framework.
 *
 */
Package( jvalue value );
Package( jobject object );
Package( const Package& object );
Package( const NoOp& noOp );
virtual const JClass* getJavaJniClass() const throw ( JNIException );
static const JClass* staticGetJavaJniClass() throw ( JNIException );
static JEnlister< Package> enlister;
};

END_NAMESPACE_4( jace, proxy, java, lang )

BEGIN_NAMESPACE( jace )

#ifndef PUT_TSDS_IN_HEADER
  template <> ElementProxy< ::jace::proxy::java::lang::Package>::ElementProxy( jarray array, jvalue element, int index );
  template <> ElementProxy< ::jace::proxy::java::lang::Package>::ElementProxy( const jace::ElementProxy< ::jace::proxy::java::lang::Package>& proxy );
#else
  template <> inline ElementProxy< ::jace::proxy::java::lang::Package>::ElementProxy( jarray array, jvalue element, int index ) : 
    ::jace::proxy::java::lang::Package( element ), Object( NO_OP ), mIndex( index ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, array ) );
  }
  template <> inline ElementProxy< ::jace::proxy::java::lang::Package>::ElementProxy( const jace::ElementProxy< ::jace::proxy::java::lang::Package>& proxy ) : 
    ::jace::proxy::java::lang::Package( proxy.getJavaJniObject() ), Object( NO_OP ), mIndex( proxy.mIndex ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, proxy.parent ) );
  }
#endif

#ifndef PUT_TSDS_IN_HEADER
  template <> JFieldProxy< ::jace::proxy::java::lang::Package>::JFieldProxy( jfieldID fieldID_, jvalue value, jobject parent_ );
  template <> JFieldProxy< ::jace::proxy::java::lang::Package>::JFieldProxy( jfieldID fieldID_, jvalue value, jclass parentClass_ );
  template <> JFieldProxy< ::jace::proxy::java::lang::Package>::JFieldProxy( const ::jace::JFieldProxy< ::jace::proxy::java::lang::Package>& object );
#else
  template <> inline JFieldProxy< ::jace::proxy::java::lang::Package>::JFieldProxy( jfieldID fieldID_, jvalue value, jobject parent_ ) : 
    ::jace::proxy::java::lang::Package( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    if ( parent_ ) {
      parent = ::jace::helper::newGlobalRef( env, parent_ );
    }
    else {
      parent = parent_;
    }

    parentClass = 0;
  }
  template <> inline JFieldProxy< ::jace::proxy::java::lang::Package>::JFieldProxy( jfieldID fieldID_, jvalue value, jclass parentClass_ ) : 
    ::jace::proxy::java::lang::Package( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    parent = 0;
    parentClass = static_cast<jclass>( ::jace::helper::newGlobalRef( env, parentClass_ ) );
  }
  template <> inline JFieldProxy< ::jace::proxy::java::lang::Package>::JFieldProxy( const ::jace::JFieldProxy< ::jace::proxy::java::lang::Package>& object ) : 
    ::jace::proxy::java::lang::Package( object.getJavaJniValue() ), Object( NO_OP ) {

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

#endif // #ifndef JACE_PROXY_JAVA_LANG_PACKAGE_H
