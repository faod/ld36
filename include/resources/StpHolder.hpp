#pragma once

#include <STP/TMXLoader.hpp>

namespace faod
{
    template<typename Ident>
    class ResourceHolder<tmx::TileMap, Ident> : public ResourceHolderBase<tmx::TileMap, Ident>
    {
        public:
            void load(Ident it, const std::string& filename);
    };
    template<typename Ident>
    void ResourceHolder<tmx::TileMap, Ident>::load(Ident id, const std::string& filename)
    {
        std::unique_ptr<tmx::TileMap> resource(new tmx::TileMap(filename));

        this->insertResource(id, std::move(resource));
    }
}
