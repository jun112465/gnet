#include "personal.h"


void file_add(PPERSON_INFO person){
    // add person on file
    FILE *fp = fopen(LIST_FILE, "ab");
    if(fp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }
    fwrite(person, sizeof(PERSON_INFO), 1, fp);
    fclose(fp);
}

void file_delete(int index){
    FILE *input_file, *output_file;
    PPERSON_INFO buffer;

    // delete record in file
    input_file = fopen(LIST_FILE, "rb");
    output_file = fopen(LIST_FILE_TMP, "wb");
    buffer = (PPERSON_INFO)malloc(sizeof(PERSON_INFO));

    // 삭제할 영역 이전까지의 데이터를 복사합니다.
    fseek(input_file, 0, SEEK_SET); // 파일 포인터를 파일의 시작으로 이동
    for(int i=0; i<index; i++){
        fread(buffer, sizeof(PERSON_INFO), 1, input_file); // 삭제할 영역 이전까지 데이터를 읽음
        fwrite(buffer, sizeof(PERSON_INFO), 1, output_file); // 출력 파일에 쓰기
    }

    // 삭제할 영역을 건너뜁니다.
    fseek(input_file, sizeof(PERSON_INFO), SEEK_CUR);

    // 나머지 파일 내용을 복사합니다.
    while (fread(buffer, sizeof(buffer), 1, input_file) > 0) {
        fwrite(buffer, sizeof(buffer), 1, output_file);
    }

    //해제
    free(buffer);

    // remove inputfile & rename outputfile;
    remove(LIST_FILE);
    rename(LIST_FILE_TMP, LIST_FILE);

    fclose(input_file);
    fclose(output_file);
}

void file_modify(int index, PPERSON_INFO person){
    FILE *fp = fopen(LIST_FILE, "r+b");

    fseek(fp, sizeof(PERSON_INFO) * index, SEEK_SET); // 파일 포인터를 파일의 시작으로 이동
    fwrite(person, sizeof(PERSON_INFO), 1, fp); // 출력 파일에 쓰기
    fclose(fp);

    // person은 현재 연결리스트에서 사용중이므로 해제할 필요없음.
    //free(person);
}