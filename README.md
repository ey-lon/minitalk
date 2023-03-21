# minitalk
A small data exchange program using UNIX signals.

## Bonus
The server acknowledges every message received by sending back a signal to the
client.

Unicode characters support!

## Usage
| `make` | to compile the *client* and the *server* (std. version). |
| `make bonus` | to compile the *client* and the *server* (bonus version). |
| `./server` | to execute the *server*. |
| `./client <server_pid> <message>` | to execute the *client* and send a message to the *server*. |
