#ifndef ASSETS_HPP
#define ASSETS_HPP

#include "base.hpp"

namespace GenEx {
    namespace Assets {
        template <class T>
        class AssetLibrary {
        public:
            AssetLibrary {

            }
        private:
            std::unordered_map<std::string, T> asset_map;
        };
    }
}

#endif // ASSETS_HPP

