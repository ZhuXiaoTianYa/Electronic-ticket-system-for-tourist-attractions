all:Server Client
Client:Client.cc
	g++ -o Client Client.cc -std=c++11 -lpthread -ljsoncpp
Server:Server.cc MySQL.cc
	g++ -o Server Server.cc MySQL.cc -std=c++11 -lpthread -ljsoncpp -L/usr/lib64/mysql -L/usr/include/mysql -lmysqlclient
.PHONY:clean
clean:
	rm -f Server Client