CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = cotacao

SRCS = main.c veiculo.c condutor.c cotacao.c arquivo.c relatorio.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe