protoc --cpp_out=. message.proto
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` message.proto
mv *.h ./include
mv *.cc ./src