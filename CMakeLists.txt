cmake_minimum_required(VERSION 3.22.1)
project(class-parser) 

execute_process(COMMAND $ENV{PREFIX}/bin/llvm-config --libs  core OUTPUT_VARIABLE LLVMLIBS_RAW OUTPUT_STRIP_TRAILING_WHITESPACE)

separate_arguments(llvm_libs_list NATIVE_COMMAND "${LLVMLIBS_RAW}")


add_compile_options(-Wall -pedantic -std=c++17)

#########################

add_library (cpp-class-parser SHARED)

target_sources(cpp-class-parser
  PRIVATE
    src/ASTConsumer.cpp 
	src/FrontendAction.cpp 
	src/Visitor.cpp 
	src/ClassInformation.cpp 
	src/CompilerDatabase.cpp 
	src/utils.cpp
)


target_include_directories(cpp-class-parser PUBLIC "$ENV{PREFIX}/include")
target_link_directories(cpp-class-parser PUBLIC "$ENV{PREFIX}/lib")

#add_library(clangFrontend SHARED IMPORTED)


target_link_libraries(cpp-class-parser PRIVATE
  clangSerialization
  clangDriver
  clangTooling
  clangParse
  clangSema
  clangToolingCore
  clangAnalysis
  clangFrontend
  clangRewriteFrontend
  clangRewrite
  clangEdit
  clangAST
  clangLex
  clangBasic
  clangFrontend
  clang-cpp)
  

#########################

#find_package(LLVM REQUIRED CONFIG)

add_executable(parsertest test/parsertest.cpp)
target_include_directories(parsertest PRIVATE "$ENV{PREFIX}/include" src/)
target_link_directories(parsertest PRIVATE "$ENV{PREFIX}/lib" ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(parsertest PRIVATE cpp-class-parser ${llvm_libs_list} clang-cpp)


