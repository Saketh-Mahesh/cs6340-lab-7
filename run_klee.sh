#!/bin/sh

# Get folder this script is run from so we can properly map are shared volumes
FOLDER=$(cd "$(dirname "$0")"; pwd -P)

##################################################################################
### USER MODIFIABLE VARIABLES
##################################################################################

# This should point to where the KLEE folder is
# The folder should container 4 sub-folders (Part1, Part2, PasswordDemo, RegexDemo)
HOST_PATH=$FOLDER/klee

# You can name the container anything you want but we recommend you leave it to match lab guide
CONTAINER_NAME=klee_container

##################################################################################
### DO NOT MODIFY THESE VARIABLES
##################################################################################

# This is where the volume maps to in the KLEE container. It should match this or the commands
# in the lab guide won't work
CONTAINER_PATH=/home/klee/klee

# What version of KLEE we are using
KLEE_VERSION=1.4.0

# The source image
KLEE_SOURCE_IMAGE=klee/klee:$KLEE_VERSION

##################################################################################
### Run the container
##################################################################################

# Let user know what the mapping is
echo Mapping folder \'$HOST_PATH\' on your host system to \'$CONTAINER_PATH\' on the container

# We need to see if the container is created and if it's running
echo Checking status of container.

#if echo $SUDO_PW | sudo -S -p "" docker ps -a | grep -q $CONTAINER_NAME; then
#	if echo $SUDO_PW | sudo -S -p "" docker ps | grep -q $CONTAINER_NAME; then
if sudo docker ps -a | grep -q $CONTAINER_NAME; then
	if sudo docker ps | grep -q $CONTAINER_NAME; then
		echo Container already running. Attaching to existing process.
		sudo docker attach $CONTAINER_NAME
	else
		echo Container already exists but is stopped. Restarting and attaching.
		sudo docker start -ai $CONTAINER_NAME
	fi
else
	echo Container doesn\'t exist yet. Downloading \(if necessary\) and starting container for first time.
	sudo docker run -v "$HOST_PATH":$CONTAINER_PATH -ti --name=$CONTAINER_NAME --ulimit='stack=-1:-1' $KLEE_SOURCE_IMAGE
fi

#ORIGINAL COMMAND
#sudo docker run -v /home/cs6340/klee/:/home/klee/klee -ti --name=klee_container --ulimit='stack=-1:-1' klee/klee:1.4.0
