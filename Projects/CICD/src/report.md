# Basic CI/CD

## Part 1. Setting up the gitlab-runner

I started Ubuntu Server on Virtual machine:
* ![img](report_screens/1.0.png)

then I installed and rigestered gitlab-runner. I used these commands:
 - sudo apt-get install gitlab-runner
 - sudo gitlab-runner register (here put url and registration token of the project and chose shell executer)
 
## Part 2. Building

I created .gitlab-ci.yml file in the root of the project then wrote a stage to start building with a 30-day retention day artifacts
* ![img](report_screens/2.1.png)

## Part 3. Codestyle test

A stage for CI that runs a codestyle script:
* ![img](report_screens/3.1.png)

## Part 4. Integration tests

The stage that runs my integration on condition the stages build and code style test passing successfully:
* ![img](report_screens/4.1.png)

Output after successful testing:
* ![img](report_screens/4.2.png)

## Part 5. Deployment stage

I ran a second virtual machine
* ![img](report_screens/5.1.png)

I connected first and second virtual machine with a static route, then I checked a connection between them and set ssh for transfering:
 - sudo -u gitlab-runner ssh-keygen (generate ssh key)
 - ssh-copy-id convictw@10.10.0.100 (it copies my public key to the remote server's ~/.ssh/authorized_keys file, allowing me to authenticate using my private key instead of a password)

A bash script which copies the files received after the building (artifacts) into the /usr/local/bin directory of the second virtual machine using ssh and scp: 
* ![img](report_screens/5.2.png)

Added a manual stage in the gitlab-ci.yml file to run the script:
* ![img](report_screens/5.3.png)


## Part 6. Bonus. Notifications

Created bot on telegram using BotFather to get telegram bot token
* ![img](report_screens/6.0.png)

Script for running telegram bot:
* ![img](report_screens/6.1.png)

Added a new stage "notification" to the .gitlab-ci.yml file
* ![img](report_screens/6.4.png)

The final version of my pipline:
* ![img](report_screens/6.5.png)

Notification of success
* ![img](report_screens/6.2.png)

Notification of fail
* ![img](report_screens/6.3.png)
