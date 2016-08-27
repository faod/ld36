#pragma once

#include <resources/ResourceHolder.hpp>
#include <STP/TMXLoader.hpp>

namespace faod
{
    //ResourceHolder specialization for STP tmx maps
    template<typename Ident>
    class ResourceHolder<tmx::TileMap, Ident>
    {
        public:

        void load(Ident id, const std::string& filename);
    };

    //load implementation
    template<typename Ident>
    void ResourceHolder<tmx::TileMap, Ident>::load(Ident id, const std::string& filename)
    {
        std::unique_ptr<tmx::TileMap> resource(new tmx::TileMap(filename));
        
        insertResource(id, std::move(resource));
    }
}
