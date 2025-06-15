#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem> // C++17부터 지원
namespace fs = std::filesystem;
#include <vector>
#include <set>
#include <algorithm> 
#include <cctype>    
#include <locale> 
#include <regex>
#include <algorithm>

#include "gui.h"

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
        
        if (!fs::exists(indir)) {
            err_msg("[error] 디렉터리 '"+indir+"'가 존재하지 않습니다.");
            return;
        }

        //is_empty 비활성화
        bool is_empty = true;
        
        //기능 수행
        int counter = 0; // 파일 이름을 순차적으로 지정하기 위한 카운터
        for (const auto& entry : fs::directory_iterator(indir)) {
            if (fs::is_regular_file(entry)) {
            
            //is_empty 비활성화
            is_empty = false;

            // 원본 파일의 경로와 확장자 추출
            std::string extension = entry.path().extension().string();
            
            if (extension == ext){
                // 카운터를 4자리로 포맷팅 (예: 0001, 0002, ...)
                std::ostringstream oss;
                oss << std::setw(4) << std::setfill('0') << counter;
                
                // 새 파일 이름 생성
                std::string new_filename = input_text + oss.str() + extension;

                // 새 파일 경로
                fs::path new_file_path = outdir / fs::path(new_filename);

                // 파일을 복사하여 새 이름으로 저장
                fs::copy(entry.path(), new_file_path);

                log_msg("파일 복사: "+entry.path().string()+" -> "+new_file_path.string());
                
                // 카운터 증가
                counter++;
                }
            }
        }

        if (is_empty) {
        err_msg("디렉터리 "+indir+"는 비어있습니다");
        }

        if (counter) {
        log_msg(std::to_string(counter)+"개 파일 작업 완료");
        }
        
    } catch (const std::exception& e) {
        // 예외 발생 시 에러 메시지를 출력
        std::cerr << "실패: " << e.what() << std::endl;
    }


    return;
}

void image_ext_changer(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){return;};

void image_resizer(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){return;};

void tag_formatter(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){
    // 디렉토리가 존재하는지 확인
    if (!fs::exists(indir)) {
        err_msg("[error] 디렉터리 '"+indir+"'가 존재하지 않습니다.");
        return;
    }

    int counter = 0;

    // 출력 폴더 없으면 생성
    fs::create_directories(outdir);

    // 파일 순회
    for (const auto& entry : fs::directory_iterator(indir)) {
        if (fs::is_regular_file(entry) && entry.path().extension() == ext) {
            std::ifstream input_file(entry.path());
            if (!input_file.is_open()) {
                std::cerr << "[error] 파일 열기 실패: " << entry.path() << std::endl;
                continue;
            }

            std::ostringstream oss;
            oss << input_file.rdbuf();  // 파일 내용 읽기
            std::string file_content = oss.str();

            // 임시 토큰 (임의로 유니크하게 설정)
            const std::string token = "___SPECIAL_AT___";

            // 1단계: @_@ → 임시 토큰으로 치환
            std::string temp = std::regex_replace(file_content, std::regex(R"(@_@)"), token);

            // 2단계: 나머지 단어에서 '_'를 ' '로 변경
            std::string result;
            std::regex word_regex(R"(\b[a-zA-Z0-9_]+\b)");
            std::sregex_iterator iter(temp.begin(), temp.end(), word_regex);
            std::sregex_iterator end;

            size_t last_pos = 0;
            for (; iter != end; ++iter) {
                const auto& match = *iter;
                std::string word = match.str();

                if (word == token) {
                    // 토큰은 그대로 둠 (원본 텍스트 그대로 붙임)
                    result += temp.substr(last_pos, match.position() + match.length() - last_pos);
                } else {
                    // 토큰 아닌 경우 단어 전까지 붙이고,
                    result += temp.substr(last_pos, match.position() - last_pos);

                    // _ → ' ' 변환
                    std::replace(word.begin(), word.end(), '_', ' ');
                    result += word;
                }

                last_pos = match.position() + match.length();
            }
            // 마지막 남은 부분 붙임
            result += temp.substr(last_pos);

            // 3단계: 임시 토큰 다시 @_@로 복원
            file_content = std::regex_replace(result, std::regex(token), "@_@");

            // 4단계: '(' → '\(', ')' → '\)'로 변경
            file_content = std::regex_replace(file_content, std::regex(R"(\()"), R"(\()");
            file_content = std::regex_replace(file_content, std::regex(R"(\))"), R"(\))");

            // 새 파일명 생성
            std::string new_filename = entry.path().filename().string();
            fs::path new_file_path = fs::path(outdir) / new_filename;

            // 변환된 내용 파일 쓰기
            std::ofstream output_file(new_file_path);
            if (!output_file.is_open()) {
                err_msg(std::string("[error] 출력 파일 열기 실패: ") + new_file_path.string());
                continue;
            }
            output_file << file_content;

            log_msg(std::string("완료: ") + new_file_path.string());
            counter++;
        }
    }

    if (counter) {
        log_msg(std::to_string(counter)+"개 파일 작업 완료");
        }
}

void tag_modifier(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){
    // log_msg(input_text); 디버깅용
    int counter = 0;

    // input_text 파싱
    std::istringstream ss(input_text);
    std::string _insert_, _delete_;
    std::getline(ss, _insert_);
    std::getline(ss, _delete_);

    std::vector<std::string> insert_tags = parseCSV(_insert_);
    std::vector<std::string> delete_tags = parseCSV(_delete_);

    // 검색용 set
    std::set<std::string> insert_tags_set = vectorToSet(insert_tags);
    std::set<std::string> delete_tags_set = vectorToSet(delete_tags);

    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(indir)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream in(entry.path());
            if (!in.is_open()) {
                err_msg("파일 열기 실패");
                continue;
            }

            std::string line;
            std::getline(in, line);
            in.close();

            std::vector<std::string> values = parseCSV(line);
            std::vector<std::string> filtered;

            // 기존 값에서 insert/delete tag 제거
            for (const auto& val : values) {
                if (
                    insert_tags_set.find(val) == insert_tags_set.end() &&
                    delete_tags_set.find(val) == delete_tags_set.end()
                ) {
                    filtered.push_back(val);
                }
            }

            // 사용자 입력 순서대로 insert_tags 맨 앞에 삽입 (역순으로 insert)
            for (auto it = insert_tags.rbegin(); it != insert_tags.rend(); ++it) {
                filtered.insert(filtered.begin(), *it);
            }

            // 출력 경로 설정
            fs::path out_path = fs::path(outdir) / entry.path().filename();
            std::ofstream out(out_path, std::ios::trunc);
            if (!out.is_open()) {
                err_msg("파일 작성 실패: " + entry.path().string());
                continue;
            }

            out << joinCSV(filtered) << std::endl;
            log_msg("완료: " + entry.path().string());

            counter++;
        }
    }

    if (counter) {
        log_msg(std::to_string(counter)+"개 파일 작업 완료");
        }
}

//공백 제거 함수
static inline void trim(std::string &s) {
    // 왼쪽 공백 제거
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    // 오른쪽 공백 제거
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

//csv를 단어로 파싱
std::vector<std::string> parseCSV(const std::string& input) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, ',')) {
        trim(item);
        result.push_back(item);
    }

    return result;
}

//단어를 csv로 조인
std::string joinCSV(const std::vector<std::string>& items) {
    std::ostringstream oss;
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << items[i];
    }
    return oss.str();
}

//vector to set
std::set<std::string> vectorToSet(const std::vector<std::string>& vec) {
    return std::set<std::string>(vec.begin(), vec.end());
}

void handle_image_queue(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){
    return;
};

void handle_text_queue(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
){
    return;
};

void log_msg(std::string msg) {
    std::cout << "[log] " << msg << std::endl;
    return;
}

void err_msg(std::string msg) {
    std::cout << "[error] " << msg << std::endl;
    return;
}