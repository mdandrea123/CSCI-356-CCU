#!/bin/bash



#########################################
#Author: Michael Dandrea
#Class: CSCI 356
#Email: mdandrea@coastal.edu
#Description: CSCI365 Lab02
#########################################

# Step 2: Create a file in users home directory called lab02
mkdir /home/$USER/lab02
# Step 3:  Change into that directory and create three files
cd /home/$USER/lab02
touch MyNotes.txt MeetingNotes.txt PublicNotes.txt
# Step 4: Shows the files were created
ls -l
# Step 5: Print a description of chmod to the screen
echo chmod allows a user to change file permissions. The available permissons are read, write and execute. The user can change the permissions for three groups: owner, group and world.
# Step 6: Change MyNotes.txt so owner can read, write, execute, but nobody else has permissions
chmod 700 MyNotes.txt
# Step 7: Change MeetingNotes.txt so the owner and the group can read and write, but nobody else has permissions
chmod 660 MeetingNotes.txt
# Step 8: Change PublicNotes.txt so the owner can write, the group can write and execute, and everyone else can read
chmod 234 PublicNotes.txt
# Step 9: Print working directory to the console
pwd
# Step 10: Print contents of direstory with permissions
ls -l
# Step 11: Move up one directory
cd ..
# Step 12: delete the folder and its contents
rm -r lab02
ls -l
echo the folder has been deleted.
