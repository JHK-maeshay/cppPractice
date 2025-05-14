#pragma once

const std::string INDIR = "INPUT_FILE_HERE";
const std::string OUTDIR = "OUTPUT_HERE";
const std::string NAME = "ComfuUI_";

typedef struct {
    int converted;
    int dummy;
} FeatureResult;

void handle_generic_feature(
    void* feature_function,
    std::string input_text=NAME,
    std::string ext=".png",
    std::string indir=INDIR,
    std::string outdir=OUTDIR,
    bool is_queue=false
);

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

void handle_image_queue();

void handle_text_queue();

void log_msg(std::string msg);