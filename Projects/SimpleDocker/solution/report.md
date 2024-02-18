# Simple Docker

## Part 1. Ready-made docker

Pulling nginx image:
* ![img](report_screens/1.1.png)

* ![img](report_screens/1.2.png)

* ![img](report_screens/1.3.png)

* ![img](report_screens/1.4.png)

* docker inspect:
  - container size: "SizeRw": 1095 byte
                    "SizeRootFs": 186729412 byte
  - list of mapped ports
                80/tcp:
                        "HostIp": "0.0.0.0",
                        "HostPort": "8080"

  - container ip: IPAddress: 172.17.0.2

* ![img](report_screens/1.6.png)

* ![img](report_screens/1.7.png)

Connection to nginx:
* ![img](report_screens/1.8.png)

* ![img](report_screens/1.9.png)

## Part 2. Operations with container

* ![img](report_screens/2.1.png)

I created nginx.conf file in Part_2 directory and add 

* ![img](report_screens/2.2.png)

Changing the nginx configurations:
* ![img](report_screens/2.4.png)

* ![img](report_screens/2.3.png)

* ![img](report_screens/2.5.png)

Saving the container as a .tar file
* ![img](report_screens/2.6.png)

* ![img](report_screens/2.7.png)

* ![img](report_screens/2.8.png)

* ![img](report_screens/2.9.png)

* ![img](report_screens/2.10.png)

* ![img](report_screens/2.11.png)

Checkcing the connection:
* ![img](report_screens/2.12.png)


## Part 3. Mini web server

* I started virtual machine, and installed next utilitues:
    - apt-get install libfcgi-dev
    - apt-get install spawn-fcgi
    - apt-get install nginx
  
* I ran web server with and without socket. All types of mini server is in the server folder 

* result:
* ![img](report_screens/3.png)

## Part 4. Your own docker

* I created Dockerfile and copied /nginx folder to the Part_4 directory and build a docker image:

* ![img](report_screens/4.1.png)


* ![img](report_screens/4.2.png)


* ![img](report_screens/4.3.png)

*  localhost:80:
* ![img](report_screens/4.png)

*  after restarting: localhost:80/status:
* ![img](report_screens/4.5.png)

## Part 5. Dockle

* dockle before correction of Dockerfile:
* ![img](report_screens/5.1.png)

* dockle after correction of Dockerfile, but I need use --accept-key NGINX_GPGKEY to ignore the NGINX_GPGKEY environment variable, because it is empty:
* ![img](report_screens/5.2.png)

## Part 6. Basic Docker Compose

* I created nginx container builder in Part 6 directory
*I wrote a docker-compose.yml file and run docker-compose build:
* ![img](report_screens/6.1.png)

* ![img](report_screens/6.2.png)

* proccess of server running
* ![img](report_screens/6.3.png)

* I got "hello, world!" in the browser page. It is a success!
* ![img](report_screens/6.4.png)