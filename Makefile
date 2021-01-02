CC = g++
CFLAGS = -g -Wall `pkg-config --cflags --libs opencv`

all: stream

old: server client

server: server.cpp
	$(CC) -o $@ $^

client: client.cpp
	$(CC) -o $@ $^

stream: stream.cpp
	$(CC) $(CFLAGS) -o $@ $^
