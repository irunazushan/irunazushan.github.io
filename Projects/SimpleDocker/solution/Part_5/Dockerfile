FROM nginx:1.17.6

RUN apt-get update && apt-get install -y \
    make \
    gcc \
    libfcgi-dev \
    spawn-fcgi \
    && apt-get clean && rm -rf /var/lib/apt/lists

WORKDIR /server
COPY ./nginx /etc/nginx/
COPY ./start.sh /server/start.sh
RUN chmod +x /server/start.sh

RUN chmod u-s /usr/bin/chfn \
    && chmod u-s /bin/su \
    && chmod u-s /bin/umount \
    && chmod u-s /usr/bin/newgrp \
    && chmod u-s /bin/mount \
    && chmod u-s /usr/bin/passwd \
    && chmod u-s /usr/bin/gpasswd \
    && chmod u-s /usr/bin/chsh \
    && chmod g-s /usr/bin/chage \
    && chmod g-s /usr/bin/wall \
    && chmod g-s /sbin/unix_chkpwd \
    && chmod g-s /usr/bin/expiry

RUN chown -R nginx:nginx /server && chmod -R 755 /server && \
        chown -R nginx:nginx /var/cache/nginx && \
        chown -R nginx:nginx /var/log/nginx && \
        chown -R nginx:nginx /etc/nginx/conf.d
RUN touch /var/run/nginx.pid && \
        chown -R nginx:nginx /var/run/nginx.pid
USER nginx
COPY ./server /server/
CMD ["/server/start.sh"]
HEALTHCHECK --interval=5m --timeout=3s \
  CMD curl -f http://localhost/ || exit 1
