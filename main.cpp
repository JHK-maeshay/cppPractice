#include <string>
#include <iostream>

#include <windows.h>
#include <shlobj.h>

//https://github.com/ocornut/imgui
#include "gui.h"
#include "source/imgui/imgui.h"
#include "source/imgui/backends/imgui_impl_glfw.h"
#include "source/imgui/backends/imgui_impl_opengl3.h"
#include "source/imgui/misc/cpp/imgui_stdlib.h"

//https://github.com/glfw/glfw
#include "source/glfw-master/include/GLFW/glfw3.h"

// GUI 표시 함수
void Show3x2ButtonsGUI() {
    static std::string indir="";
    static std::string outdir="";
    static std::string change_name="";
    static std::string add_tag="";
    static std::string remove_tag="";

    ImGui::Begin("선택");

    if (ImGui::Button("이미지 한번에 처리", ImVec2(ImGui::GetContentRegionAvail().x, 40))) { 
        handle_generic_feature(handle_image_queue, NAME, ".png", INDIR, OUTDIR, true);
    }

    if (ImGui::Button("태그 한번에 처리", ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
        std::string _intxt_ = add_tag+"\n"+remove_tag;
        handle_generic_feature(handle_text_queue, _intxt_, ".txt", INDIR, OUTDIR, true);
    }

    static std::string labels[2][3] = {
                {    "이미지 png로 변환",
                     "이미지 리사이징",
                     "이미지 이름 변경" },
                {    "태그 형식 수정",
                     "태그 추가/제거",
                     "태그 파일 이름 변경" }
            };

    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 3; ++col) {
            std::string label = labels[row][col];

            if (ImGui::Button(label.c_str(), ImVec2(160, 60))) {
                // 위치별로 다른 기능 호출
                if (row == 0 && col == 0) {
                    handle_generic_feature(image_ext_changer, NAME, ".jpg", INDIR, OUTDIR, false);
                    handle_generic_feature(image_ext_changer, NAME, ".jpeg", INDIR, OUTDIR, false);
                    handle_generic_feature(image_ext_changer, NAME, ".webp", INDIR, OUTDIR, false);
                }
                else if (row == 0 && col == 1) {
                    handle_generic_feature(image_resizer, NAME, ".png", INDIR, OUTDIR, false);
                }
                else if (row == 0 && col == 2) {
                    handle_generic_feature(file_namer, NAME, ".png", INDIR, OUTDIR, false);
                }
                else if (row == 1 && col == 0) {
                    handle_generic_feature(tag_formatter, NAME, ".txt", INDIR, OUTDIR, false);
                }
                else if (row == 1 && col == 1) {
                    std::string _intxt_ = add_tag+"\n"+remove_tag;
                    handle_generic_feature(tag_modifier, _intxt_, ".txt", INDIR, OUTDIR, false);
                }
                else if (row == 1 && col == 2) {
                    handle_generic_feature(file_namer, NAME, ".txt", INDIR, OUTDIR, false);
                }
            }

            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("입력 폴더");
    ImGui::SameLine();
    ImGui::InputText("##InputFolder", &indir);

    ImGui::Text("출력 폴더");
    ImGui::SameLine();
    ImGui::InputText("##OutputFolder", &outdir);

    ImGui::Text("이름 변경");
    ImGui::SameLine();
    ImGui::InputText("##NewName", &change_name);

    ImGui::Text("추가 태그");
    ImGui::SameLine();
    ImGui::InputText("##AddTag", &add_tag);

    ImGui::Text("삭제 태그");
    ImGui::SameLine();
    ImGui::InputText("##RemoveTag", &remove_tag);

    ImGui::End();
}

//폰트 설정
std::string GetFontPath() {
    // Windows 폰트 디렉토리 내의 NotoSansKR-Regular.ttf 파일 경로
    std::string fontPath = "C:\\Windows\\Fonts\\NotoSansKR-Regular.ttf";
    
    // 경로가 올바른지 확인하기 위한 출력
    std::cout << "폰트 경로: " << fontPath << std::endl;

    // 폰트 경로를 반환
    return fontPath;
}

int main() {
    // 한글 출력 설정
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패!" << std::endl;
        std::cin.get();
        return -1;
    }

    // OpenGL 버전 지정
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // 창 생성
    GLFWwindow* window = glfwCreateWindow(600, 480, "ImGui Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW 창 생성 실패!" << std::endl;
        glfwTerminate();
        std::cin.get();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //한글폰트
    std::string fontPath = GetFontPath();
    if (fontPath.empty()) {
        std::cerr << "폰트 경로를 가져오는 데 실패했습니다.\n";
        return -1;
    }
    //ImFont* myFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // 새 프레임 시작
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // --- 여기서 GUI 렌더링 ---
        Show3x2ButtonsGUI();

        // 렌더링
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    
    // 종료 처리
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}