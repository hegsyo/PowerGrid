#------------------------------------------------------------------------
# Copyright 2014 Patrick Kramer, Vincent Wassenaar
#
# This file is part of PowerGrid.
#
# PowerGrid is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# PowerGrid is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PowerGrid.  If not, see <http://www.gnu.org/licenses/>.
#
# Note that the files contained in this project do NOT fall under the
# terms of the GNU General Public License, but instead fall under a
# different license as mentioned below. This .pro file does fall under the
# GNU General Public License.
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# All files in the "jace" subdirectory belong to JACE.
# JACE falls under the terms of the following license:
#
# Copyright (c) 2002, Toby Reyelts
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
# Neither the name of Toby Reyelts nor the names of his contributors
# may be used to endorse or promote products derived from this software
# without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
# GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# All other files are part of the Oracle JDK.
# These files are subject to the following license:
#
# Copyright (c) 1999, 2001, Oracle and/or its affiliates
# All rights reserved.
#
# They are modified for optimization within the context of the project
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# .pro file for the JACE library.
# This subproject contains the functionality required to bridge the gap
# between Java and C++. The JACE library is used for that purpose.
# JACE has been optimized for use with PowerGrid.
#------------------------------------------------------------------------

QT          = core concurrent
TEMPLATE    = lib
TARGET      = JACE
CONFIG     += staticlib thread c++11

# JACE uses .tsd and .tsp files as C++ header files, so include those as well
QMAKE_EXT_H += .tsp .tsd

# Tell JACE we're building statically, and want to load the JVM dynamically.
DEFINES += JACE_STATIC JACE_WANT_DYNAMIC_LOAD

# In debug mode, have JACE check for null values
# and out-of-bounds array indices
CONFIG(debug, debug|release): DEFINES += JACE_CHECK_NULLS JACE_CHECK_ARRAYS

HEADERS += \
    IllegalOperationException.h \
    MappingUnavailableException.h \
    RSClass.h \
    RSClassMapper.h \
    UpdaterRunner.h \
    api/bridge/client.h \
    java/lang/object.h \
    java/lang/string.h \
    MethodHelper.h \
    api/bridge/abstractcamera.h \
    api/bridge/abstractcameralocationdata.h \
    api/bridge/abstractcentrallocationdata.h \
    api/bridge/abstractmodel.h \
    api/bridge/abstractserver.h \
    api/bridge/abstractsocketstream.h \
    api/bridge/animablenode.h \
    api/bridge/animatedobject.h \
    api/bridge/animation.h \
    api/bridge/baseinfo.h \
    api/bridge/canvas.h \
    api/bridge/detailinfo.h \
    api/bridge/entityposition.h \
    api/bridge/fileworker.h \
    api/bridge/friend.h \
    api/bridge/grandexchangeoffer.h \
    api/bridge/graphicstoolkit.h \
    api/bridge/hintarrow.h \
    api/bridge/animator.h \
    api/bridge/cameramatrix.h \
    api/bridge/chatline.h \
    api/bridge/entitydata.h \
    api/bridge/entitynode.h \
    api/bridge/grounddata.h \
    api/bridge/isaaccipher.h \
    api/bridge/interactable.h \
    api/bridge/node.h \
    api/bridge/animable.h \
    api/bridge/deque.h \
    api/bridge/boundary.h \
    api/bridge/hashtable.h \
    api/bridge/hashtableiterator.h \
    api/bridge/camera.h \
    api/bridge/detailinfonode.h \
    api/bridge/floordecoration.h \
    api/bridge/groundentity.h \
    api/bridge/groundobject.h \
    api/bridge/animatedanimableobject.h \
    api/bridge/animatedboundaryobject.h \
    api/bridge/itemnode.h \
    api/bridge/keyboard.h \
    api/bridge/mlstring.h \
    api/bridge/mouse.h \
    api/bridge/passiveanimator.h \
    api/bridge/quaternion.h \
    api/bridge/skillinfo.h \
    api/bridge/sprite.h \
    api/bridge/worldcontroller.h \
    api/bridge/interface.h \
    api/bridge/nodesub.h \
    api/bridge/stream.h \
    api/bridge/reference.h \
    api/bridge/queue.h \
    api/bridge/cache.h \
    api/bridge/floatstream.h \
    api/bridge/toolkitld.h \
    api/bridge/varpbits.h \
    api/bridge/linkedlistnode.h \
    api/bridge/linkedlist.h \
    api/bridge/modelld.h \
    api/bridge/objectcomposite.h \
    api/bridge/nodesubqueue.h \
    api/bridge/objectdefloader.h \
    api/bridge/objectdef.h

SOURCES += \
    IllegalOperationException.cpp \
    MappingUnavailableException.cpp \
    RSClass.cpp \
    RSClassMapper.cpp \
    UpdaterRunner.cpp \
    api/bridge/client.cpp \
    java/lang/object.cpp \
    java/lang/string.cpp \
    api/bridge/abstractcamera.cpp \
    api/bridge/abstractcameralocationdata.cpp \
    api/bridge/abstractcentrallocationdata.cpp \
    api/bridge/abstractmodel.cpp \
    api/bridge/abstractserver.cpp \
    api/bridge/abstractsocketstream.cpp \
    api/bridge/animablenode.cpp \
    api/bridge/animatedobject.cpp \
    api/bridge/animation.cpp \
    api/bridge/baseinfo.cpp \
    api/bridge/canvas.cpp \
    api/bridge/detailinfo.cpp \
    api/bridge/entityposition.cpp \
    api/bridge/fileworker.cpp \
    api/bridge/friend.cpp \
    api/bridge/grandexchangeoffer.cpp \
    api/bridge/graphicstoolkit.cpp \
    api/bridge/hintarrow.cpp \
    api/bridge/animator.cpp \
    api/bridge/cameramatrix.cpp \
    api/bridge/chatline.cpp \
    api/bridge/entitydata.cpp \
    api/bridge/entitynode.cpp \
    api/bridge/grounddata.cpp \
    api/bridge/isaaccipher.cpp \
    api/bridge/interactable.cpp \
    api/bridge/node.cpp \
    api/bridge/animable.cpp \
    api/bridge/deque.cpp \
    api/bridge/boundary.cpp \
    api/bridge/hashtable.cpp \
    api/bridge/hashtableiterator.cpp \
    api/bridge/camera.cpp \
    api/bridge/detailinfonode.cpp \
    api/bridge/floordecoration.cpp \
    api/bridge/groundentity.cpp \
    api/bridge/groundobject.cpp \
    api/bridge/animatedanimableobject.cpp \
    api/bridge/animatedboundaryobject.cpp \
    api/bridge/itemnode.cpp \
    api/bridge/keyboard.cpp \
    api/bridge/mlstring.cpp \
    api/bridge/mouse.cpp \
    api/bridge/passiveanimator.cpp \
    api/bridge/quaternion.cpp \
    api/bridge/skillinfo.cpp \
    api/bridge/sprite.cpp \
    api/bridge/worldcontroller.cpp \
    api/bridge/interface.cpp \
    api/bridge/nodesub.cpp \
    api/bridge/stream.cpp \
    api/bridge/reference.cpp \
    api/bridge/queue.cpp \
    api/bridge/cache.cpp \
    api/bridge/floatstream.cpp \
    api/bridge/toolkitld.cpp \
    api/bridge/varpbits.cpp \
    api/bridge/linkedlistnode.cpp \
    api/bridge/linkedlist.cpp \
    api/bridge/modelld.cpp \
    api/bridge/objectcomposite.cpp \
    api/bridge/nodesubqueue.cpp \
    api/bridge/objectdefloader.cpp \
    api/bridge/objectdef.cpp

#------------------------------------------------
# Files in this project. This contains all
# default JACE classes, as well as the
# required JNI headers.
#------------------------------------------------

HEADERS    += \
    jni.h \
    jni_md.h \
    jace/WrapperVmLoader.h \
    jace/VmLoader.h \
    jace/UnixVmLoader.h \
    jace/StaticVmLoader.h \
    jace/Peer.h \
    jace/os_dep.h \
    jace/OptionList.h \
    jace/namespace.h \
    jace/JSignature.h \
    jace/JNIHelper.h \
    jace/JNIException.h \
    jace/JMethod.h \
    jace/JFieldProxyHelper.h \
    jace/JFieldProxy.h \
    jace/JFieldHelper.h \
    jace/JField.h \
    jace/JFactory.h \
    jace/JEnlister.h \
    jace/JConstructor.h \
    jace/JClassImpl.h \
    jace/JClass.h \
    jace/javacast.h \
    jace/JArrayHelper.h \
    jace/JArray.tsd \
    jace/JArray.h \
    jace/JArguments.h \
    jace/ElementProxyHelper.h \
    jace/ElementProxy.h \
    jace/counted_ptr.h \
    jace/BaseException.h \
    jace/proxy/JValue.h \
    jace/proxy/JObject.h \
    jace/proxy/types/JVoid.h \
    jace/proxy/types/JShort.h \
    jace/proxy/types/JLong.h \
    jace/proxy/types/JInt.h \
    jace/proxy/types/JFloat.h \
    jace/proxy/types/JDouble.h \
    jace/proxy/types/JChar.h \
    jace/proxy/types/JByte.h \
    jace/proxy/types/JBoolean.h \
    jace/JMethod.tsp \
    jace/JMethod.tsd \
    jace/JField.tsp \
    jace/JField.tsd \
    jace/javacast.tsp \
    jace/javacast.tsd \
    jace/JArray.tsp \
    jace/ElementProxy.tsp \
    jace/ElementProxy.tsd

SOURCES    += \
    jace/WrapperVmLoader.cpp \
    jace/VmLoader.cpp \
    jace/UnixVmLoader.cpp \
    jace/StaticVmLoader.cpp \
    jace/Peer.cpp \
    jace/os_dep.cpp \
    jace/OptionList.cpp \
    jace/JSignature.cpp \
    jace/JNIHelper.cpp \
    jace/JNIException.cpp \
    jace/JMethod.cpp \
    jace/JFieldProxyHelper.cpp \
    jace/JFieldProxy.cpp \
    jace/JFieldHelper.cpp \
    jace/JField.cpp \
    jace/JFactory.cpp \
    jace/JEnlister.cpp \
    jace/JConstructor.cpp \
    jace/JClassImpl.cpp \
    jace/JClass.cpp \
    jace/javacast.cpp \
    jace/JArrayHelper.cpp \
    jace/JArray.cpp \
    jace/JArguments.cpp \
    jace/ElementProxyHelper.cpp \
    jace/ElementProxy.cpp \
    jace/BaseException.cpp \
    jace/proxy/JValue.cpp \
    jace/proxy/JObject.cpp \
    jace/proxy/types/JVoid.cpp \
    jace/proxy/types/JShort.cpp \
    jace/proxy/types/JLong.cpp \
    jace/proxy/types/JInt.cpp \
    jace/proxy/types/JFloat.cpp \
    jace/proxy/types/JDouble.cpp \
    jace/proxy/types/JChar.cpp \
    jace/proxy/types/JByte.cpp \
    jace/proxy/types/JBoolean.cpp \
