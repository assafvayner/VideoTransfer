CC = g++
CFLAGS = -g -Wall `pkg-config --cflags --libs opencv`

old: server client

server: server.cpp
	$(CC) -o $@ $^

client: client.cpp
	$(CC) -o $@ $^

stream: video.cpp udp_server.cpp stream.cpp
	$(CC) $(CFLAGS) -o $@ $^
