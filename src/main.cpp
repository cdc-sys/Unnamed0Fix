#include <matdash.hpp>

// defines add_hook to use minhook
#include <matdash/minhook.hpp>

// lets you use mod_main
#include <matdash/boilerplate.hpp>

// matdash::create_console
#include <matdash/console.hpp>

// gd.h includes cocos2d.h
#include <gd.h>

using namespace cocos2d;

gd::GJGameLevel* GameLevelManager_createNewLevel() {
    auto level = matdash::orig<&GameLevelManager_createNewLevel>();
    auto localLevelMgr = gd::LocalLevelManager::sharedState();
    CCObject* levelObject;
    std::vector<int> unnamedInts;
    //int total_unnameds = 0;


    if (localLevelMgr->m_pLevels != nullptr) {
        CCARRAY_FOREACH(localLevelMgr->m_pLevels, levelObject)
        {
            auto gamelevel = (gd::GJGameLevel*)levelObject;
            if (gamelevel->m_sLevelName.find("Unnamed ") != std::string::npos) {

                auto currentUnnamedInt_string = gamelevel->m_sLevelName.c_str() + 8;
                std::string checkString = currentUnnamedInt_string;
                checkString.erase(remove(checkString.begin(), checkString.end(), ' '), checkString.end());

                if (checkString.empty() != std::string::npos) {

                    std::stringstream conversionString;
                    conversionString << currentUnnamedInt_string;
                    int currentUnnamedInt;
                    conversionString >> currentUnnamedInt;
                    unnamedInts.push_back(currentUnnamedInt);

                }
            }
        }
    }


    int unnamedInt = 0;
    if (unnamedInts.size() != 0) {
        for (int i = 0; i != -1; i++) {
            if (std::find(unnamedInts.begin(), unnamedInts.end(), i) != unnamedInts.end()) {
            }
            else {
                unnamedInt = i;
                break;
            }
        }
    }


    level->m_sTempName = CCString::createWithFormat("Unnamed %i", unnamedInt)->getCString();

    return level;
}
void mod_main(HMODULE) {
    matdash::add_hook<&GameLevelManager_createNewLevel>(gd::base + 0xA0DB0);
}
