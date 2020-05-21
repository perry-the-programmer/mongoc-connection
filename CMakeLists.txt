cmake_minimum_required(VERSION 3.10)

project(mongoeg)

find_package (mongoc-1.0 1.7 REQUIRED)

add_executable (mongoeg mongoconnection.c)
target_link_libraries (mongoeg PRIVATE mongo::mongoc_shared)
