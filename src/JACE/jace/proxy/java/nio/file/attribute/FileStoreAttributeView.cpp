
#ifndef JACE_PROXY_JAVA_NIO_FILE_ATTRIBUTE_FILESTOREATTRIBUTEVIEW_H
#include "jace/proxy/java/nio/file/attribute/FileStoreAttributeView.h"
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

BEGIN_NAMESPACE_6( jace, proxy, java, nio, file, attribute )

/**
 * The Jace C++ proxy class source for java/nio/file/attribute/FileStoreAttributeView.
 * Please do not edit this source, as any changes you make will be overwritten.
 * For more information, please refer to the Jace Developer's Guide.
 *
 */
#ifndef VIRTUAL_INHERITANCE_IS_BROKEN
  #define FileStoreAttributeView_INITIALIZER : ::jace::proxy::java::lang::Object( NO_OP )
#else
  #define FileStoreAttributeView_INITIALIZER
#endif

/**
 * The following methods are required to integrate this class
 * with the Jace framework.
 *
 */
/**
 * Special no arg constructor for interface virtual inheritance
 *
 */
FileStoreAttributeView::FileStoreAttributeView() : Object( NO_OP ) { 
}

FileStoreAttributeView::FileStoreAttributeView( jvalue value ) FileStoreAttributeView_INITIALIZER {
  setJavaJniValue( value );
}

FileStoreAttributeView::FileStoreAttributeView( jobject object ) FileStoreAttributeView_INITIALIZER {
  setJavaJniObject( object );
}

FileStoreAttributeView::FileStoreAttributeView( const FileStoreAttributeView& object ) FileStoreAttributeView_INITIALIZER {
  setJavaJniObject( object.getJavaJniObject() );
}

FileStoreAttributeView::FileStoreAttributeView( const NoOp& noOp ) FileStoreAttributeView_INITIALIZER {
}

const JClass* FileStoreAttributeView::staticGetJavaJniClass() throw ( JNIException ) {
  static JClassImpl javaClass( "java/nio/file/attribute/FileStoreAttributeView" );
  return &javaClass;
}

const JClass* FileStoreAttributeView::getJavaJniClass() const throw ( JNIException ) {
  return FileStoreAttributeView::staticGetJavaJniClass();
}

JEnlister< FileStoreAttributeView> FileStoreAttributeView::enlister;

END_NAMESPACE_6( jace, proxy, java, nio, file, attribute )

BEGIN_NAMESPACE( jace )

#ifndef PUT_TSDS_IN_HEADER
  template <> inline ElementProxy< ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView>::ElementProxy( jarray array, jvalue element, int index ) : 
    ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView( element ), Object( NO_OP ), mIndex( index ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, array ) );
  }
  template <> inline ElementProxy< ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView>::ElementProxy( const jace::ElementProxy< ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView>& proxy ) : 
    ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView( proxy.getJavaJniObject() ), Object( NO_OP ), mIndex( proxy.mIndex ) {
    JNIEnv* env = ::jace::helper::attach();
    parent = static_cast<jarray>( ::jace::helper::newGlobalRef( env, proxy.parent ) );
  }
#endif
#ifndef PUT_TSDS_IN_HEADER
  template <> inline JFieldProxy< ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView>::JFieldProxy( jfieldID fieldID_, jvalue value, jobject parent_ ) : 
    ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    if ( parent_ ) {
      parent = ::jace::helper::newGlobalRef( env, parent_ );
    }
    else {
      parent = parent_;
    }

    parentClass = 0;
  }
  template <> inline JFieldProxy< ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView>::JFieldProxy( jfieldID fieldID_, jvalue value, jclass parentClass_ ) : 
    ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView( value ), Object( NO_OP ), fieldID( fieldID_ ) {
    JNIEnv* env = ::jace::helper::attach();

    parent = 0;
    parentClass = static_cast<jclass>( ::jace::helper::newGlobalRef( env, parentClass_ ) );
  }
  template <> inline JFieldProxy< ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView>::JFieldProxy( const ::jace::JFieldProxy< ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView>& object ) : 
    ::jace::proxy::java::nio::file::attribute::FileStoreAttributeView( object.getJavaJniValue() ), Object( NO_OP ) {

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
