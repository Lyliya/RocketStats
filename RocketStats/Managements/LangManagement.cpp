#include    "../RocketStats.h"

void RocketStats::ChangeLang(int id)
{
    Resource embeded_img = Resource(id, "TEXT", GetModuleHandle("RocketStats"));
    std::span<const char> embeded_res = embeded_img.GetResource();

    std::ostringstream os;
    os << embeded_res.data();
    json file = json::parse(os.str());

    rs_lang.clear();
    for (int i = 0; i < file.size(); ++i)
        rs_lang.push_back(file.at(i));
}

std::string RocketStats::GetLang(unsigned int id)
{
    return rs_lang.at(id);
}