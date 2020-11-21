# VideoTransfer

Code for moving video streams between robot and base station for Husky Robotics Team

Stream video to website (in progress):
- must be able to run web server, if npm installed, use the following:
	- npm install http-server -g (must have root access)
	- run website in dashboard directory with `http-server dashboard`
- `make stream`
- run the stream with `./stream`
- run `http-server dashboard`, must be run after `./stream`
- on your browser go to `localhost:8081`

temp client and server echo process:
- `make old`
- `./server & sleep 1; ./client`
- input `close` will close both the client and server
Then the server will echo the client, < 16 chars
