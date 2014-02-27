/*
 * Copyright 2014 Patrick Kramer, Vincent Wassenaar
 *
 * This file is part of PowerGrid.
 *
 * PowerGrid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PowerGrid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PowerGrid.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RSClassMapper.h"
#include "MappingUnavailableException.h"
#include <stdexcept>
#include <QDebug>
#include <QXmlStreamReader>

#include "jace/JNIException.h"
#include "jace/JNIHelper.h"

using namespace jace;



RSClassMapper* RSClassMapper::classmapper = nullptr;

RSClassMapper* RSClassMapper::DefaultInstance() {
    if (! RSClassMapper::classmapper) {
        RSClassMapper::classmapper = new RSClassMapper();
    }
    return RSClassMapper::classmapper;
}

RSClassMapper::RSClassMapper() {}

RSClassMapper::~RSClassMapper() {
    // Upon destruction, delete all maintained RSClass references.
    for (QMap<QString,RSClass*>::Iterator it=classes.begin(); it!=classes.end();it++) {
        RSClass* rsc = it.value();
        if (rsc) {
            delete rsc;
        }
    }
}

QMap<QString, QString> RSClassMapper::getFieldMap(QString className) const {
    QMap<QString, QMap<QString, QString>>::const_iterator it = fieldMap.find(className);
    if (it == fieldMap.cend()) {
        throw MappingUnavailableException(className);
    }
    return it.value();
}

QMap<QString, int> RSClassMapper::getModifierMap(QString className) const {
    QMap<QString, QMap<QString, int>>::const_iterator it = modifiers.find(className);
    if (it == modifiers.cend()) {
        return QMap<QString, int>();
    }
    return it.value();
}

QString RSClassMapper::getRealName(QString semanticName) const {
    QMap<QString, QString>::const_iterator it = classMap.find(semanticName);
    if (it == classMap.end()) {
        throw MappingUnavailableException("class " + semanticName);
    }
    return it.value();
}

RSClass* RSClassMapper::getRSClass(QString name) {
    QMap<QString, RSClass*>::const_iterator it = classes.find(name);
    if (it == classes.cend()) {
        RSClass* rsc = new RSClass(getRealName(name).toStdString(), name, getFieldMap(name), getModifierMap(name));
        classes.insert(name, rsc);
        // We delete the references from the maps to prevent redundancy
        classMap.remove(name);
        fieldMap.remove(name);
        modifiers.remove(name);
        qDebug() << "Linked RS class:" << name;
        return rsc;
    } else {
        return it.value();
    }
}

void RSClassMapper::parseData(jbyteArray data) {
    if (data == NULL) {
        throw JNIException("Received NULL jbyteArray as map data");
    }
    if (classMap.isEmpty()) {
        JNIEnv* env = jace::helper::attach();
        // java byte array copy using Java NIO transfer
        char* bytes = static_cast<char*>(env->GetDirectBufferAddress(data));
        jlong length = env->GetDirectBufferCapacity(data);
        QByteArray byteArray (const_cast<const char*>(bytes), length);
        QXmlStreamReader reader (byteArray);
        reader.setNamespaceProcessing(false);

        QString currentClass;
        QString fieldName;
        bool readModifier = false;
        bool stop = true;
        while (!stop && !reader.atEnd()) {
            reader.readNext();
            switch (reader.tokenType()) {
            case QXmlStreamReader::NoToken:
            case QXmlStreamReader::Invalid:
                stop = true;
                break;
            case QXmlStreamReader::StartElement:
                if (reader.name() == "modifier") {
                    readModifier = true;
                } else if (currentClass.isEmpty()) {
                    currentClass = reader.name().toString();
                    classMap.insert(currentClass,
                                    reader.attributes().value("className").toString());
                    fieldMap.insert(currentClass, QMap<QString, QString>());
                    modifiers.insert(currentClass, QMap<QString, qint32>());
                } else {
                    fieldName = reader.name().toString();
                }
                break;
            case QXmlStreamReader::EndElement:
                if (readModifier) {
                    readModifier = false;
                } else if (fieldName.isEmpty()) {
                    currentClass.clear();
                } else {
                    fieldName.clear();
                }
                break;
            case QXmlStreamReader::Characters:
                if (readModifier) {
                    bool ok = true;
                    int mod = reader.text().toInt(&ok);
                    if (ok) {
                        modifiers.find(currentClass).value().insert(fieldName, mod);
                    } else {
                        qDebug() << "Cannot convert" << currentClass << fieldName << "modifier" << reader.text() << "to integer";
                    }
                } else {
                    fieldMap.find(currentClass).value()
                            .insert(fieldName, reader.name().toString());
                }
                break;
            default:
                break;
            }
        }
        if (reader.hasError()) {
            throw JNIException("Error parsing XML file: " + reader.errorString());
        }
    }
}