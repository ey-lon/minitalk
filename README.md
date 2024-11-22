# minitalk
A small data exchange program using UNIX signals.

## Bonus
The server acknowledges every message received by sending back a signal to the
client.

Unicode characters support!

## Usage
| command | info |
| ------- | ---- |
| `make` | compile the *client* and the *server* (std. version). |
| `make bonus` | compile the *client* and the *server* (bonus version). |
| `make clean` | remove temporary files. |
| `make fclean` | remove temporary and executables. |

To execute the *server*:
```shell
./server
```
To execute the *client* and send a message to the *server*:
```shell
./client <server_pid> <message>
```
