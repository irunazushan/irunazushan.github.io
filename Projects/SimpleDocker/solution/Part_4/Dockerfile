FROM ubuntu:latest
RUN apt-get update && apt-get install -y \
    make \
    gcc \
    libfcgi-dev \
    nginx \
    spawn-fcgi \
    net-tools \
    curl
WORKDIR /server/
COPY ./server /server/
COPY ./nginx /etc/nginx/
COPY ./start.sh /server/start.sh
RUN chmod +x /server/start.sh
CMD ["/server/start.sh"]