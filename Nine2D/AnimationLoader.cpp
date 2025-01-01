#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "base\simdjson.h"
#include "AnimationLoader.h"

using namespace simdjson;


bool JsonAnimFileLoader(AnimFrameFile& affile, const char* jsoneFile)
{
	std::vector<FRAME_t>& frameArray = affile.frames;

	ondemand::parser parser;
    auto json = padded_string::load(jsoneFile);
    auto doc = parser.iterate(json);

    ondemand::object frames = doc["frames"];

    for (ondemand::field imgFile : frames) 
    {
      FRAME_t f;

      f.name = std::string(std::string_view(imgFile.unescaped_key()));

      ondemand::object imgFile_data = imgFile.value();
      ondemand::object frame_data  = imgFile_data["frame"];

      f.x = uint64_t(frame_data["x"]);
      f.y = uint64_t(frame_data["y"]);
      f.w = uint64_t(frame_data["w"]);
      f.h = uint64_t(frame_data["h"]);

      frameArray.push_back(f);
    }

    ondemand::object meta = doc["meta"];

    affile.imgFileName = std::string( std::string_view(meta["image"]) );
    affile.img_w = uint64_t( meta["size"]["w"] );
    affile.img_h = uint64_t( meta["size"]["h"] );


    return true;
}




