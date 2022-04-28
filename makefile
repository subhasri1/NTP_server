all:client server
client:NTP_client_main.cpp NTP_client_function.o
	g++ -o client NTP_client_main.cpp NTP_client_function.o	
NTP_client_function.o:NTP_client_function.cpp NTP_client_header.h
	g++ -c NTP_client_function.cpp
server:NTP_server_main.cpp NTP_server_function.o
	g++ -o server NTP_server_main.cpp NTP_server_function.o	
NTP_server_function.o:NTP_server_function.cpp NTP_server_header.h
	g++ -c NTP_server_function.cpp

