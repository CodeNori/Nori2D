#pragma once



struct FRAME_t {
    std::string name;
    uint16_t x,y,w,h;  
};

struct AnimFrameFile 
{
    std::string imgFileName;
    std::vector<FRAME_t> frames;
};

bool JsonAnimFileLoader(AnimFrameFile& affile, const char* jsoneFile);





