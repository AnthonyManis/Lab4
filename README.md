# Lab4 Mukesh Kastala Ryan Cockins Anthony Manis

Queue:
-Request queue implemented as singly-linked list.
-Add new requests to back of queue, remove from font.

Connections:
-Listening Socket:
-On program start bind a port, if it fails print an error.
-Listen for requests from clients on that port.
-Queue the requests and call a function that processes them

Server Connection
-Get a client request from the queue
-Open a new connection with the server
-Request the page
-Call function to write log entry
-Return the page to client

Log Entry:
-Format the entry
-Write it to file
