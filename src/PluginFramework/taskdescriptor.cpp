#include "taskdescriptor.h"
#include <stdexcept>

namespace plugins {
  TaskDescriptor::TaskDescriptor(QString name, QString description) :
    nm(name), desc(description) {}

  Task TaskDescriptor::create() {
    throw std::runtime_error("Cannot create Task");
  }
}