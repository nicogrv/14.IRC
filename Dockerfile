FROM alpine

RUN apk update && \
    apk add build-base make valgrind

WORKDIR /app
COPY Makefile /app/Makefile

CMD ["sh", "-c", "tail -f"]
