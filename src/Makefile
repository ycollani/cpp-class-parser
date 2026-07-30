# Copyright 2018 - 2021: Yorck von Collani (yorck@von-collani.de)

LLVMLIBS := $(shell $(PREFIX)/bin/llvm-config --libs)
LLVMINC  := $(shell $(PREFIX)/bin/llvm-config --cxxflags)

CXX = g++ -c -g -Wall -MMD -fPIC -I ../ $(LLVMINC)
LD  = g++ -g

#CXX = /vol/llvm/bin/clang++ -c -g -Wall -std=c++11 -fvisibility=hidden
#LD  = /vol/llvm/bin/clang++ -std=c++14 -g -fvisibility=hidden

LIBS =  -lclangFrontend -lclangSerialization -lclangDriver \
           -lclangTooling -lclangParse -lclangSema -lclangToolingCore  \
           -lclangAnalysis -lclangFrontend -lclangRewriteFrontend -lclangRewrite \
           -lclangEdit -lclangAST -lclangLex -lclangBasic $(LLVMLIBS) -lncurses -lz -lpthread -lboost_system -lboost_filesystem

# -lLLVMSupport -lLLVMDemangle

all: ../../lib/libcpp-class-parser.so

INCLUDEDIR = -I ../ -I $(PREFIX)/include 
LIBDIR = -L $(PREFIX)/lib

#../bin/genmsg: genmsg
#	cp genmsg ../../bin/
	
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

#genmsg: $(OBJS)
#	$(LD) -o $@ $(LIBDIR) $(OBJS) $(LIBS)

../../lib/libcpp-class-parser.so: $(sort $(patsubst %.cpp, %.o, $(SRCS)))
	@echo "[LIB]" $@
	$(LD) -shared -o $@ $(sort $(patsubst %.cpp, %.o, $(SRCS))) $(LIBS) $(LIBDIR) 
	
clean veryclean distclean:
	$(RM) -f *.o *.d

cleandepend:
	$(RM) -f *.d