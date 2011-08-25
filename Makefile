#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = ws2801
TARGET_LIB = \
lib/lib$(COMPONENT_NAME).a 

TEST_TARGET = \
$(COMPONENT_NAME)_tests

#--- Inputs ----#
PROJECT_HOME_DIR = .
CPPUTEST_HOME = ../CppUTest

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

##
WARNINGFLAGS += -Wall -Werror -Wswitch-default -Wswitch-enum 
MEMLEAK_DETECTOR_NEW_MACROS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
MEMLEAK_DETECTOR_MALLOC_MACROS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

ifeq ($(CPPUTEST_USE_MEM_LEAK_DETECTION), N)
CPPUTEST_CPPFLAGS += -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED
endif

ifeq ($(ENABLE_DEBUG), Y)
CPPUTEST_CPPFLAGS += -g
endif

ifeq ($(CPPUTEST_USE_STD_CPP_LIB), N)
CPPUTEST_CPPFLAGS += -DCPPUTEST_STD_CPP_LIB_DISABLED
CPPUTEST_CXXFLAGS += -nostdinc++
endif

CPPUTEST_CPPFLAGS += $(WARNINGFLAGS)
CPPUTEST_CXXFLAGS += $(MEMLEAK_DETECTOR_NEW_MACROS)
CPPUTEST_CFLAGS += $(MEMLEAK_DETECTOR_MALLOC_MACROS)
##
#GCOVFLAGS = -fprofile-arcs -ftest-coverage

#SRC_DIRS is a list of source directories that make up the target library
#If test files are in these directories, their IMPORT_TEST_GROUPs need
#to be included in main to force them to be linked in.  By convention
#put them into an AllTests.h file in each directory
SRC_DIRS = \
src/* \

#TEST_SRC_DIRS is a list of directories including 
# - A test main (AllTests.cpp by conventin)
# - OBJ files in these directories are included in the TEST_TARGET
# - Consequently - AllTests.h containing the IMPORT_TEST_GROUPS is not needed
# - 
TEST_SRC_DIRS = \
tests \

#includes for all compiles
INCLUDE_DIRS =\
  $(CPPUTEST_HOME)/include/\
  mocks/\
  tests/\
  src/WS2801/ \

MOCKS_SRC_DIRS =\
  mocks

#Flags to pass to ld
LDFLAGS +=
LD_LIBRARIES += -lstdc++

include $(CPPUTEST_HOME)/build/ComponentMakefile
