#pragma once

#include <vector>
#include <set>

inline const std::string INDIR = "INPUT_FILE_HERE";
inline const std::string OUTDIR = "OUTPUT_HERE";
inline const std::string NAME = "ComfuUI_";

typedef struct {
    int converted;
    int dummy;
} FeatureResult;

template <typename Func>
void handle_generic_feature(
    Func feature_function,
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir,
    bool is_queue=false
){
    feature_function(input_text, ext, indir, outdir);
};

void example_feature_function(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void file_namer(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void image_ext_changer(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void image_resizer(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void tag_formatter(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void tag_modifier(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void handle_image_queue(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void handle_text_queue(
    std::string input_text,
    std::string ext,
    std::string indir,
    std::string outdir
);

void log_msg(std::string msg);

void err_msg(std::string msg);

std::vector<std::string> parseCSV(const std::string& input);

std::string joinCSV(const std::vector<std::string>& items);

std::set<std::string> vectorToSet(const std::vector<std::string>& vec);