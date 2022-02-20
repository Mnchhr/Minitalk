# Minitalk
The purpose of this project is to code a small data exchange program using UNIX signals.

### Mandatory

- Produce `server` & `client` executables
- `client` must communicate a string passed as a parameter to `server` *(referenced by its process ID)* which then displays it
- Use `SIGUSR1` & `SIGUSR2` signals **ONLY**

### Bonus

- Add reception acknowledgement system
- Support Unicode characters

## Compilation and execution

1. Compile files into `server` & `client` executables via `make server` and `make client`.
2. Run server by `./server`. It wiil print its PID in terminal.
3. Open another terminal and run a client by `./client [server PID] [message to pass]`.
