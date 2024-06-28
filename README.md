# Inter-Process Communication (IPC) 

This project demonstrates inter-process communication using System V message queues in C. It consists of a server and two clients (Client 1 and Client 2). The server waits for messages from both clients, prints them to the console, and then forwards the messages to the other client.

## Project Structure

- `server.c`: Implements the server that receives messages from clients and forwards them.
- `client1.c`: Implements Client 1 which sends messages to the server and receives messages from Client 2.
- `client2.c`: Implements Client 2 which sends messages to the server and receives messages from Client 1.

## Compilation and Execution

### Compile the Programs

- gcc -o server server.c -lpthread
- gcc -o client1 client1.c -lpthread
- gcc -o client2 client2.c -lpthread

## How It Works

1. The server creates a message queue and waits for messages from the clients.
2. Each client sends messages to the server.
3. The server prints the received messages and forwards them to the other client.
4. Clients have separate threads to receive and print messages forwarded by the server.

## Code Details

### `server.c`

- Initializes a message queue using `msgget`.
- Waits for messages from Client 1 (type 1) and Client 2 (type 3) using `msgrcv`.
- Prints received messages and changes the message type (2 for Client 1 and 4 for Client 2).
- Forwards the messages to the respective clients using `msgsnd`.

### `client1.c`

- Connects to the message queue created by the server.
- Uses a separate thread to receive messages of type 2.
- Reads user input and sends it to the server with message type 1.

### `client2.c`

- Connects to the message queue created by the server.
- Uses a separate thread to receive messages of type 4.
- Reads user input and sends it to the server with message type 3.

## Requirements

- A POSIX-compliant operating system (e.g., Linux).
- GCC compiler.
- Basic understanding of inter-process communication in C.
