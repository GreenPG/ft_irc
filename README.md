# ft_irc

A simple IRC server part of the 42 School cursus.
This project was carried out using the [IRC protocol](https://modern.ircdocs.horse/) and using [Hexchat](https://hexchat.github.io/) as reference client.
This project was made with the collaboration of Théo Larrazet (https://github.com/TenkuuOtoshi)
## Requirements
This projects was carried out according to the following rules : 
* it's written in C++98
* Only 1 poll() or equivalent must be use (select() has been chosen)
* No forking
* Input/Output operations must be non-blocking
* Communication via TCP/IP (v4 or v6)
* Mandatory features :
	* User must be able to register (set a nickname, a username and a password)
	* User must be able to join a channel, send and receive private messages using the reference client
	* All the messages sent from one client to a channel have to be forwarded to every other client that joined the channel
	* You must have channel operators and regular users 

## Usage

To compile the server:
```
make
```
To launch the server:
```
./ircserver <port> <password>
```

## Handled commands


| Commands | Description |
| -------- | -------- |
| PASS     | Use to set a 'connection password'     |
| NICK| Use to give the client a nickname or change the previous one|
| USER| Use at the beginning of a connection to specify the username and realname of a new user|
| PRIVMSG| Use to send private messages between users, as well as to send messages to channels|
|JOIN| Use to join channel|
|KICK| Use by a channel operator to request the force removal of a user from a channel|
|INVITE| Use to invite a user to a channel|
|TOPIC| Use to display or change a channel topic|
|MODE| Use to set or remove mode from a channel|
|SKILL| Use to stop the server|

## Channel Modes

| Mode | Description |
| ------ | ------ |
| i | Set/remove Invite-only channel |
| t | Set/remove the restriction of command TOPIC to the channel operator |
| k | Set/remove the channel key|
| o | Give/take channel operator privilege|
| l | Set/remove the channel user limit |

## Joking Bot
We had a joking bot to the server. To compile it, use: 
```
make bonus
```
then run it whith:
```
./bot
```
The bot will then ask you the port of the server, the password and a name for it to connect it to the server.
You can now communicates with it by sending it a private message or invite it to a channel. 
The bot only understand two command:
* !joke: the bot will tell you a joke
* !kill: it will stop the bot\


## Ressources
[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
[Modern IRC Docs](https://modern.ircdocs.horse)
[RFC 2810](https://www.rfc-editor.org/rfc/rfc2810)
[RFC 2811](https://www.rfc-editor.org/rfc/rfc2811)
[RFC 2812](https://www.rfc-editor.org/rfc/rfc2812)
[RFC 2813](https://www.rfc-editor.org/rfc/rfc2813)
