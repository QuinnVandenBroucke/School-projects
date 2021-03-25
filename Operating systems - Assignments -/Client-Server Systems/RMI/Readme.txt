/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////	HOW TO RUN	/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


1. Extract the folder on your desktop
2. On windows, open your cmd (Command Prompt)
3. In cmd, navigate to the folder on your desktop where the class files are located (cd command)
	for ex: cd "Desktop\exCh4\Socket\bin"

4. Use the command rmiregistry.exe to set up the remote object registry
5. Repeat steps 2-3 (so open a new command window)
6. Use the command "Java RemoteDateImpl" to start the server
7. Repeat steps 2-3 (so open a new command window)
8. Use the command "Java RMIClient" to start the the client and see the output

9. To close the rmi registry again: Go to the cmd were the rmi registry is running & press 'ctrl + c'
10. To close the server again: Go to the cmd were the server is running & press 'ctrl + c'