# Internet Relay Chat (IRC)

<div style="display" align="center">
<img src="./rscs/Weechat.gif" width="90%">
</div>

## About

Internet Relay Chat (IRC) is a text-based communication protocol on the Internet. It was created in 1988 and has been widely used for real-time communication ever since. IRC allows users to communicate with each other in real-time through discussion channels or private messages.

The ft_irc project consists of creating an IRC server using the C++ programming language and its network library. The server allows instant communication mainly in the form of group discussions through discussion channels, but can also be used for direct communication between two people. The most common IRC commands such as JOIN, PART, PRIVMSG, and QUIT have been implemented.

During this project, I learned how to use sockets to communicate with clients over the network. Sockets are a fundamental concept in network programming and are used to establish connections between different machines on a network.


## Prerequisites

<h2>Weechat</h2>
<div style="display" align="center">
<img src="./rscs/WeeChat.png" width="20%">
</div>
To use the server you must use WeeChat.
Here are the steps to install WeeChat on macOS using Homebrew:

1. Open Terminal on your Mac.
2. Install Homebrew by entering the following command in Terminal:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
3. Once the installation is complete, update Homebrew by entering the following command:
```bash
brew update
```
4. Install WeeChat by entering the following command:
```bash
brew install weechat
```
5. Once the installation is complete, you can launch WeeChat by entering the following command in Terminal:
```bash
weechat
```

## Getting Started

First, clone the repository:

````bash
git clone git@github.com:ltrinchini/InternetRelayChat.git && cd InternetRelayChat
````

Then, compile the program by running:
````bash
make
````

## Usage
To start the IRC server:
````bash
./ircserv <port> <password>
./ircserv 4242 mysecretpassword
````

To connect to the server with WeeChat:
1. Launch WeeChat by typing the following command:
````bash
weechat
````
2. Type the following command to add an IRC server:
````bash
/server add <server name> <server address>/<port>
/server add myserver 127.0.0.1/4242
````
3. Set password:
````bash
/set irc.server.myserver.password mysecretpassword 
````
4. Connect to the server:
````bash
/connect myserver
````

## Credit
This two-person project was done with [Louis ❤️ ](https://github.com/ljourand)
