#pragma once



struct FRAME_t {
    std::string name;
    uint16_t x,y,w,h;  
};

struct AnimFrameFile 
{
    uint16_t img_w, img_h;
    std::string imgFileName;
    std::vector<FRAME_t> frames;
};

bool JsonAnimFileLoader(AnimFrameFile& affile, const char* jsoneFile);





