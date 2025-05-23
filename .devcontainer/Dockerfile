FROM alpine:latest
RUN apk add --no-cache build-base g++ && rm -rf /var/cache/apk/*

COPY compile.sh /usr/local/bin/compile.sh
RUN source /usr/local/bin/compile.sh

WORKDIR /workspace