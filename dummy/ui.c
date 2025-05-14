#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ������ ������ ����ü�� �Լ� ���� (������ ���� ����� ����)
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

// ���� ��� �Լ� 1 (������ ���)
FeatureResult dummy_feature_function(void (*logger)(const char*), const char* indir, const char* outdir) {
    logger("���� ��� ���� ��...");
    FeatureResult result = {3, 0}; // ���Ƿ� 3�� ���� ó���ߴٰ� ����
    return result;
}

// ���� ��� �Լ� 2 (tag_modifying �䳻)
FeatureResult dummy_tag_modifying(void (*logger)(const char*), const char* t2, const char* t3, const char* indir, const char* outdir) {
    logger("�±� ���� ��� ���� ��...");
    FeatureResult result = {5, 0}; // 5�� ó���� ������ ����
    return result;
}

// handler �Լ� ���� (�ռ� ������ �ڵ� ����)
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
        // ���� ���丮 ���� ����
    }

    if (converted) {
        snprintf(msg, sizeof(msg), "%d�� ���� %s �Ϸ�", converted, description);
    } else {
        snprintf(msg, sizeof(msg), "%s�� ���� ����", description);
    }

    return msg;
}

// ������ CUI
int main() {
    const char* input_text[3] = {"file1.txt", "tag1", "tag2"};

    while (1) {
        int choice;
        printf("\n--- ���� �۾� ���� ---\n");
        printf("1. �⺻ ��� ����\n");
        printf("2. �±� ���� ��� ����\n");
        printf("0. ����\n");
        printf("����: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("���α׷� ����\n");
            break;
        }

        const char* message = NULL;

        switch (choice) {
            case 1:
                message = handle_generic_feature(
                    (void*)dummy_feature_function,
                    "��ȯ",
                    NULL,      // ext ����
                    false,     // is_queue
                    "INPUT", "OUTPUT",
                    input_text
                );
                break;
            case 2:
                message = handle_generic_feature(
                    (void*)dummy_tag_modifying,
                    "�±� ����",
                    NULL,      // ext ����
                    true,      // is_queue
                    "INPUT", "OUTPUT",
                    input_text
                );
                break;
            default:
                printf("�߸��� �����Դϴ�.\n");
                continue;
        }

        printf("���: %s\n", message);
    }

    return 0;
}
