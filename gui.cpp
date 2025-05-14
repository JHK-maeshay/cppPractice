#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <filesystem> // C++17부터 지원
namespace fs = std::filesystem;

#include "gui.h"

void handle_generic_feature(
    void* feature_function,
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir,
    bool is_queue
){
    // feature_function 호출
     auto func = reinterpret_cast<void(*)(std::string, std::string, std::string, std::string)>(feature_function);
    func(input_text, ext, indir, outdir);
    
    return;
};

void example_feature_function(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){
    std::cout << "Input Text: " << input_text << std::endl;
    std::cout << "Extension: " << ext << std::endl;
    std::cout << "Input Directory: " << indir << std::endl;
    std::cout << "Output Directory: " << outdir << std::endl;
    log_msg("This is example!!");
    //std::cin.get();
    return;
}

void file_namer(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){
    fs::create_directories(outdir); //폴더 없으면 생성

    try {
        for (const auto& entry : fs::directory_iterator(indir)){
            if (!fs::exists(indir)) {
            std::cerr << "[error] 디렉터리 '" << indir << "'가 존재하지 않습니다." << std::endl;
            }
            bool is_empty = true;
            
            //기능 수행
            int counter = 1; // 파일 이름을 순차적으로 지정하기 위한 카운터
            for (const auto& entry : fs::directory_iterator(indir)) {
                if (fs::is_regular_file(entry)) {

                // 원본 파일의 경로와 확장자 추출
                std::string extension = entry.path().extension().string();
                
                if (extension == ext){
                    // 카운터를 4자리로 포맷팅 (예: 0001, 0002, ...)
                    std::ostringstream oss;
                    oss << std::setw(4) << std::setfill('0') << counter;
                    
                    // 새 파일 이름 생성
                    std::string new_filename = "input_text" + oss.str() + extension;

                    // 새 파일 경로
                    fs::path new_file_path = outdir / fs::path(new_filename);

                    // 파일을 복사하여 새 이름으로 저장
                    fs::copy(entry.path(), new_file_path);

                    std::cout << "파일 복사: " << entry.path() << " -> " << new_file_path << std::endl;
                    
                    // 카운터 증가
                    counter++;
                    }
                }
            }

            if (is_empty) {
            log_msg("디렉터리 "+indir+"는 비어있습니다");
            }

            if (counter) {
            log_msg(counter+"개 파일 변환 완료");
            }
        }
    } catch (const std::exception& e) {
        // 예외 발생 시 에러 메시지를 출력
        std::cerr << "실패: " << e.what() << std::endl;
    }


    return;
}

void handle_image_queue(){
    return;
}

void handle_text_queue(){
    return;
}

void log_msg(std::string msg) {
    std::cout << "[log] " << msg << std::endl;
    return;
}