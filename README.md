# VideoTransfer

Code for moving video streams between robot and base station for Husky Robotics Team

Stream video to js base station (in progress):
- must be able to run web server, if npm installed, use the following:
	- npm install http-server -g (must have root access)
	- run website in dashboard directory with `http-server dashboard`
- `make stream`
- run the stream with `./stream`
- *There is nothing that's reciving the video stream by default*

temp client and server echo process:
- `make old`
- `./server & sleep 1; ./client`
- input `close` will close both the client and server
Then the server will echo the client, < 16 chars
