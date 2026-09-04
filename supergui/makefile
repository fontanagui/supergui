CC = gcc
SRC = codigo/*.c
OUT = game


LIBS = -lallegro -lallegro_image -lallegro_primitives -lallegro_font -lallegro_audio -lallegro_acodec -lm


.PHONY: clean


$(OUT):
	$(CC) $(SRC) -o $(OUT) $(LIBS)


clean:
	rm -f $(OUT)