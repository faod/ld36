#pragma once

#include <cassert>
#include <stdexcept>

namespace faod
{

	template <typename Resource, typename Ident>
	void ResourceHolderBase<Resource, Ident>::load(Ident id, const std::string& filename)
	{
		std::unique_ptr<Resource> resource(new Resource());

		if(!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load  - Failed to load " + filename);

	    insertResource(id, std::move(resource));
	}

	template <typename Resource, typename Ident>
	template <typename Parameter>
	void ResourceHolderBase<Resource, Ident>::load(Ident id, const std::string& filename, const Parameter& secondParam)
	{
		std::unique_ptr<Resource> resource(new Resource());

		if(!resource->loadFromFile(filename, secondParam))
			throw std::runtime_error("ResourceHolder::load  - Failed to load " + filename);

		
	    insertResource(id, std::move(resource));
	}


	template <typename Resource, typename Ident>
	Resource& ResourceHolderBase<Resource, Ident>::get(Ident id)
	{
		auto found = resources_.find(id);
		assert(found != resources_.end());

		return *found->second;
	}
    template<typename Resource, typename Ident>
    bool ResourceHolderBase<Resource, Ident>::isIn(Ident id) const
    {
        return resources_.count(id);
    }
	template<typename Resource, typename Ident>
	const Resource& ResourceHolderBase<Resource, Ident>::get(Ident id) const
	{
		auto found = resources_.find(id);
		assert(found != resources_.end());

		return *found->second;
	}

    template<typename Resource, typename Ident>
    void ResourceHolderBase<Resource, Ident>::insertResource(Ident id, std::unique_ptr<Resource> resource)
    {
        //Insert and check for success
        auto inserted = resources_.insert(std::make_pair(id, std::move(resource)));
        assert(inserted.second);
    }

    template<typename Resource, typename Ident>
    void ResourceHolderBase<Resource, Ident>::release(Ident id)
    {
        auto found = resources_.find(id);
        assert(found != resources_.end());

        resources_.erase(found);
    }


}
