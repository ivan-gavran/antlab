## SSH-ing into machines
In order to control the TurtleBot computers from the controller computer, ssh server has to be installed and ssh key of the controlling machine added to the list of authorized keys. 
The descriptions on how to do it can be found [here](https://help.ubuntu.com/community/SSH/OpenSSH/Configuring) and [here](http://askubuntu.com/questions/4830/easiest-way-to-copy-ssh-keys-to-another-machine)

Because broadcasting is needed for multimaster_fkie, it is a good idea to [establish an ad-hoc network](http://howtoubuntu.org/how-to-create-a-wireless-ad-hoc-network-in-ubuntu) for all machines.