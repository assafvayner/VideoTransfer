CC = g++
CFLAGS = -g -Wall `pkg-config --cflags --libs opencv`

all : server client vid

server: server.cpp
	$(CC) -o $@ $^

client: client.cpp
	$(CC) -o $@ $^

vid: video.cpp
	$(CC) $(CFLAGS) -o $@ $^
