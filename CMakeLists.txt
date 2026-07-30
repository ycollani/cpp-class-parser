cmake_minimum_required(VERSION 3.22.1)
project(class-parser)

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


target_link_libraries(cpp-class-parser PUBLIC
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


add_executable(parsertest test/parsertest.cpp)
target_include_directories(parsertest PUBLIC "$ENV{PREFIX}/include" src/)
target_link_libraries(parsertest PUBLIC clangASTMatchers clangCrossTU clangSupport LLVM-17git
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
  clang-cpp cpp-class-parser)
