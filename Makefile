CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = cotacao

SRCS = main.c funcoes/veiculo.c funcoes/condutor.c funcoes/cotacao.c funcoes/arquivo.c funcoes/relatorio.c funcoes/utils.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe