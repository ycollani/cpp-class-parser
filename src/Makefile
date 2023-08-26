# Copyright 2018 - 2023: Yorck von Collani (yorck@von-collani.de)

LLVMLIBS := $(shell $(LLVMBASE)/bin/llvm-config --libs)
LLVMINC  := $(shell $(LLVMBASE)/bin/llvm-config --cxxflags)

CXX = g++ -c -g -Wall -MMD -fPIC -I ../ $(LLVMINC)
LD  = g++ -g

LIBS =  -lclangFrontend -lclangSerialization -lclangDriver \
        -lclangTooling -lclangParse -lclangSema -lclangToolingCore  \
        -lclangAnalysis -lclangFrontend -lclangRewriteFrontend -lclangRewrite \
        -lclangEdit -lclangAST -lclangLex -lclangBasic $(LLVMLIBS) -lncurses -lz -lpthread -lboost_system -lboost_filesystem

all: ../lib/libcpp-class-parser.so

INCLUDEDIR = -I ./ -I $(LLVMBASE)/include 
LIBDIR = -L $(LLVMBASE)/lib

SRCS := ASTConsumer.cpp \
		FrontendAction.cpp \
		Visitor.cpp \
		ClassInformation.cpp \
		CompilerDatabase.cpp \
		utils.cpp 
		
DEPS := $(wildcard $(patsubst %.cpp, %.d, $(sort $(SRCS))))

ifeq (,$(findstring clean, $(MAKECMDGOALS)))
-include $(DEPS)
endif

%.o: %.cpp
	@echo "[CPP]" $<
	$(CXX) $(INCLUDEDIR) -DNDEBUG -o $@ $< 

../lib/libcpp-class-parser.so: $(sort $(patsubst %.cpp, %.o, $(SRCS)))
	@echo "[LIB]" $@
	$(LD) -shared -o $@ $(sort $(patsubst %.cpp, %.o, $(SRCS))) $(LIBS) $(LIBDIR) 
	
clean veryclean distclean:
	$(RM) -f *.o *.d

cleandepend:
	$(RM) -f *.d