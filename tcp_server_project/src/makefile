#你的目标名字叫做 main
TARGET:=main
#CC 是代表编译器的名字
CC:=gcc
INC:=$(shell pwd)/sort

#把工程中的所有的 .c 文件名赋值给 CSRCS
CSRCS:=$(wildcard *.c)
CSRCS+=$(wildcard sort/*.c)

#把CSRCS中的文件名，变为同名的 .o 文件 赋值给 OBJS
OBJS += $(patsubst %.c,%.o,$(CSRCS))

$(TARGET):$(OBJS)
	$(CC) $^ -o $@ -I$(INC)
#cp $@ /home/gec/tftp
%.o:%.c	
	$(CC) -c $< -o $@ -I$(INC)

#伪目标
clean:	
	rm $(OBJS)
	rm $(TARGET)
#rm /home/gec/tftp/$(TARGET)