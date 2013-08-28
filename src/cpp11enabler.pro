#------------------------------------------------------------------------
# Copyright 2012-2013 Patrick Kramer, Vincent Wassenaar
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
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# This project file adds platform and compiler specific flags to enable
# C++11 support. If your compiler is not listed, please add the
# appropriate flags for your compiler to enable C++11 features.
#------------------------------------------------------------------------

# The platform-compiler name is the filename (without path) that the
# message below reports.
message(QMake Spec: $$QMAKESPEC)

macx-clang {
    # Clang has its own c++ library optimized for the Clang compiler (libc++).
    # We prefer using that library over the standard one (libstdc++)
    QMAKE_CXXFLAGS += -stdlib=stdc++ -std=c++11

    # We also provide a message to assert the right platform-compiler combination is detected.
    message(Compiling using Clang compiler on Mac OS X)
}
# Add additional compiler definitions here
else {
    # We have no specific information. We assume -std=c++0x works (like for GCC).
    # However, we also provide a warning that specific compiler flags are not
    # available, so that they can be added when required.
    QMAKE_CXXFLAGS += -std=c++0x
    warning(No specific compiler flags available. Please add compiler flags specific to your compiler.)
}


