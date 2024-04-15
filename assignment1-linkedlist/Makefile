CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC_DIR = src
BUILD_DIR = build

# wildcard는 파일 이름 패턴을 사용하여 파일을 찾는 함수
SRCS = $(wildcard $(SRC_DIR)/*.c)
# patsubst 함수는 패턴 매칭을 사용하여 문자열을 치환
# $(patsubst pattern,replacement,text)
# SRCS 변수에 있는 모든 .c 파일의 경로를 src/에서 obj/로 변경하여 OBJS 변수에 저장합니다.
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = my_program

# compile 명령어 -c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# linking 명령어 -o
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	del /Q $(BUILD_DIR)\*.o $(TARGET)