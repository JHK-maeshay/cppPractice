#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 위에서 정의한 구조체와 함수 선언 (보통은 별도 헤더에 선언)
typedef struct {
    int converted;
    int dummy;
} FeatureResult;

typedef FeatureResult (*FeatureFunctionExt)(void (*logger)(const char*), const char* t1, const char* ext, const char* indir, const char* outdir);
typedef FeatureResult (*FeatureFunctionSimple)(void (*logger)(const char*), const char* indir, const char* outdir);
typedef FeatureResult (*FeatureFunctionTag)(void (*logger)(const char*), const char* t2, const char* t3, const char* indir, const char* outdir);

void log_message(const char* msg) {
    printf("[LOG] %s\n", msg);
}

// 샘플 기능 함수 1 (간단한 기능)
FeatureResult dummy_feature_function(void (*logger)(const char*), const char* indir, const char* outdir) {
    logger("더미 기능 실행 중...");
    FeatureResult result = {3, 0}; // 임의로 3개 파일 처리했다고 가정
    return result;
}

// 샘플 기능 함수 2 (tag_modifying 흉내)
FeatureResult dummy_tag_modifying(void (*logger)(const char*), const char* t2, const char* t3, const char* indir, const char* outdir) {
    logger("태그 변경 기능 실행 중...");
    FeatureResult result = {5, 0}; // 5개 처리한 것으로 가정
    return result;
}

// handler 함수 정의 (앞서 제공된 코드 복사)
const char* handle_generic_feature(
    void* feature_function,
    const char* description,
    const char* ext,
    bool is_queue,
    const char* indir,
    const char* outdir,
    const char* input_text[3]
) {
    int converted = 0;

    const char* t1 = NULL;
    const char* t2 = NULL;
    const char* t3 = NULL;

    if (input_text) {
        t1 = input_text[0];
        t2 = input_text[1];
        t3 = input_text[2];
    }

    FeatureResult result;

    if (ext != NULL) {
        FeatureFunctionExt func = (FeatureFunctionExt)feature_function;
        result = func(log_message, t1, ext, indir, outdir);
    } else {
        if (feature_function == (void*)dummy_tag_modifying) {
            FeatureFunctionTag func = (FeatureFunctionTag)feature_function;
            result = func(log_message, t2, t3, indir, outdir);
        } else {
            FeatureFunctionSimple func = (FeatureFunctionSimple)feature_function;
            result = func(log_message, indir, outdir);
        }
    }

    converted = result.converted;

    static char msg[256];
    if (converted && is_queue) {
        // 실제 디렉토리 삭제 생략
    }

    if (converted) {
        snprintf(msg, sizeof(msg), "%d개 파일 %s 완료", converted, description);
    } else {
        snprintf(msg, sizeof(msg), "%s할 파일 없음", description);
    }

    return msg;
}

// 간단한 CUI
int main() {
    const char* input_text[3] = {"file1.txt", "tag1", "tag2"};

    while (1) {
        int choice;
        printf("\n--- 전산 작업 도구 ---\n");
        printf("1. 기본 기능 실행\n");
        printf("2. 태그 변경 기능 실행\n");
        printf("0. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("프로그램 종료\n");
            break;
        }

        const char* message = NULL;

        switch (choice) {
            case 1:
                message = handle_generic_feature(
                    (void*)dummy_feature_function,
                    "변환",
                    NULL,      // ext 없음
                    false,     // is_queue
                    "INPUT", "OUTPUT",
                    input_text
                );
                break;
            case 2:
                message = handle_generic_feature(
                    (void*)dummy_tag_modifying,
                    "태그 수정",
                    NULL,      // ext 없음
                    true,      // is_queue
                    "INPUT", "OUTPUT",
                    input_text
                );
                break;
            default:
                printf("잘못된 선택입니다.\n");
                continue;
        }

        printf("결과: %s\n", message);
    }

    return 0;
}
