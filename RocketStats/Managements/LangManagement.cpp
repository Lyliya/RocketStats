#include    "../RocketStats.h"

void RocketStats::ChangeLang(int id)
{
    cvarManager->log("===== ChangeLang =====");

    Resource embeded_img = Resource(id, "TEXT", GetModuleHandle("RocketStats"));
    std::span<const char> embeded_res = embeded_img.GetResource();

    try
    {
        std::ostringstream os;
        os << embeded_res.data();
        json file = json::parse(os.str().substr(0, embeded_res.size()));

        rs_lang.clear();
        for (int i = 0; i < file.size(); ++i)
            rs_lang.push_back(file.at(i));
    }
    catch (json::parse_error& e)
    {
        cvarManager->log(("Error: " + std::string(e.what())).c_str());
    }

    cvarManager->log((std::to_string(rs_lang.size()) + " translations loaded").c_str());
    cvarManager->log("===== !ChangeLang =====");
}

std::string RocketStats::GetLang(LangStringId id)
{
    return rs_lang.at(id);
}
