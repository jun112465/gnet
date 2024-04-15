# 컴파일러 설정
CC := gcc
CFLAGS := -Wall -Wextra -Iinclude -g

# 소스 코드 및 헤더 파일 디렉토리
SRC_DIR := src
INCLUDE_DIR := header
BUILD_DIR := build

# 소스 코드 및 헤더 파일
SRCS := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# 실행 파일 이름
EXEC := main

# 실행 파일 빌드
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# 각각의 객체 파일 빌드
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# clean 타겟
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXEC)